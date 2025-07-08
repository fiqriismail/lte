#include "mainwindow.h"
#include "toolbar.h"
#include "linenumberwidget.h"
#include "../../features/shared/types/common.h"
#include <QApplication>
#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QStandardPaths>

MainWindow::MainWindow(IFileService *fileService, IFontService *fontService, ILineNumberService *lineNumberService, QWidget *parent)
    : QMainWindow(parent)
    , m_textEdit(nullptr)
    , m_menuBar(nullptr)
    , m_toolBar(nullptr)
    , m_lineNumberWidget(nullptr)
    , m_centralWidget(nullptr)
    , m_fileService(fileService)
    , m_fontService(fontService)
    , m_lineNumberService(lineNumberService)
    , m_currentFilePath("")
    , m_newAction(nullptr)
    , m_openAction(nullptr)
    , m_saveAction(nullptr)
    , m_saveAsAction(nullptr)
    , m_quitAction(nullptr)
    , m_undoAction(nullptr)
    , m_redoAction(nullptr)
    , m_cutAction(nullptr)
    , m_copyAction(nullptr)
    , m_pasteAction(nullptr)
    , m_zoomInAction(nullptr)
    , m_zoomOutAction(nullptr)
{
    setupUI();
    setupFileMenu();
    setupEditMenu();
    setupToolBar();
    setupFontManagement();
    connectSignals();
    
    setWindowTitle(AppConstants::APP_NAME);
    resize(AppConstants::DEFAULT_WINDOW_WIDTH, AppConstants::DEFAULT_WINDOW_HEIGHT);
}

MainWindow::~MainWindow()
{
    // Qt will handle cleanup of child widgets
}

void MainWindow::setupUI()
{
    // Create central widget with horizontal layout
    m_centralWidget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(m_centralWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    
    // Create line number widget
    m_lineNumberWidget = new LineNumberWidget(m_lineNumberService, m_centralWidget);
    
    // Create text edit
    m_textEdit = new QTextEdit(m_centralWidget);
    
    // Add widgets to layout
    layout->addWidget(m_lineNumberWidget);
    layout->addWidget(m_textEdit);
    
    // Set the central widget
    setCentralWidget(m_centralWidget);
    
    // Connect line number widget to text editor
    m_lineNumberWidget->setTextEditor(m_textEdit);
    
    // Menu bar setup
    m_menuBar = menuBar();
}

void MainWindow::setupFileMenu()
{
    QMenu *fileMenu = m_menuBar->addMenu("&File");
    
    // File menu actions
    m_newAction = new QAction("&New", this);
    m_newAction->setShortcut(QKeySequence::New);
    fileMenu->addAction(m_newAction);

    m_openAction = new QAction("&Open...", this);
    m_openAction->setShortcut(QKeySequence::Open);
    fileMenu->addAction(m_openAction);
    
    m_saveAction = new QAction("&Save", this);
    m_saveAction->setShortcut(QKeySequence::Save);
    fileMenu->addAction(m_saveAction);

    m_saveAsAction = new QAction("Save &As...", this);
    m_saveAsAction->setShortcut(QKeySequence::SaveAs);
    fileMenu->addAction(m_saveAsAction);
    
    fileMenu->addSeparator();
    
    m_quitAction = new QAction("&Quit", this);
    m_quitAction->setShortcut(QKeySequence::Quit);
    fileMenu->addAction(m_quitAction);
}

void MainWindow::setupEditMenu()
{
    QMenu *editMenu = m_menuBar->addMenu("&Edit");
    
    // Edit menu actions
    m_undoAction = new QAction("&Undo", this);
    m_undoAction->setShortcut(QKeySequence::Undo);
    editMenu->addAction(m_undoAction);
    
    m_redoAction = new QAction("&Redo", this);
    m_redoAction->setShortcut(QKeySequence::Redo);
    editMenu->addAction(m_redoAction);
    
    editMenu->addSeparator();
    
    m_cutAction = new QAction("Cu&t", this);
    m_cutAction->setShortcut(QKeySequence::Cut);
    editMenu->addAction(m_cutAction);
    
    m_copyAction = new QAction("&Copy", this);
    m_copyAction->setShortcut(QKeySequence::Copy);
    editMenu->addAction(m_copyAction);
    
    m_pasteAction = new QAction("&Paste", this);
    m_pasteAction->setShortcut(QKeySequence::Paste);
    editMenu->addAction(m_pasteAction);
    
    editMenu->addSeparator();
    
    // Font management actions
    m_zoomInAction = new QAction("Zoom &In", this);
    m_zoomInAction->setShortcut(QKeySequence::ZoomIn);
    editMenu->addAction(m_zoomInAction);
    
    m_zoomOutAction = new QAction("Zoom &Out", this);
    m_zoomOutAction->setShortcut(QKeySequence::ZoomOut);
    editMenu->addAction(m_zoomOutAction);
}

void MainWindow::setupToolBar()
{
    m_toolBar = new ToolBar(this);
    m_toolBar->setupActions(m_newAction, m_openAction, m_saveAction);
    addToolBar(m_toolBar);
}

void MainWindow::setupFontManagement()
{
    // Apply the default font from the font service
    applyCurrentFont();
}

void MainWindow::connectSignals()
{
    // File operation connections
    connect(m_newAction, &QAction::triggered, this, &MainWindow::newFile);
    connect(m_openAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(m_saveAction, &QAction::triggered, this, &MainWindow::saveFile);
    connect(m_saveAsAction, &QAction::triggered, this, &MainWindow::saveAsFile);
    connect(m_quitAction, &QAction::triggered, this, &MainWindow::quitApplication);
    
    // Text editing connections
    connect(m_undoAction, &QAction::triggered, this, &MainWindow::undoText);
    connect(m_redoAction, &QAction::triggered, this, &MainWindow::redoText);
    connect(m_cutAction, &QAction::triggered, this, &MainWindow::cutText);
    connect(m_copyAction, &QAction::triggered, this, &MainWindow::copyText);
    connect(m_pasteAction, &QAction::triggered, this, &MainWindow::pasteText);
    
    // Font management connections
    connect(m_zoomInAction, &QAction::triggered, this, &MainWindow::increaseFontSize);
    connect(m_zoomOutAction, &QAction::triggered, this, &MainWindow::decreaseFontSize);
}

void MainWindow::newFile()
{
    if (!maybeSave())
        return;
    m_textEdit->clear();
    m_currentFilePath.clear();
    m_textEdit->document()->setModified(false);
    setWindowTitle(AppConstants::APP_NAME + " - Untitled");
}

bool MainWindow::maybeSave()
{
    if (!m_textEdit->document()->isModified())
        return true;
    QMessageBox::StandardButton ret = QMessageBox::warning(this, AppConstants::APP_NAME,
        "The document has been modified.\nDo you want to save your changes?",
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    if (ret == QMessageBox::Save) {
        saveFile();
        return !m_textEdit->document()->isModified();
    } else if (ret == QMessageBox::Cancel) {
        return false;
    }
    return true;
}

// File Operations Slice
void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, FileOperations::OPEN_DIALOG_TITLE, "", AppConstants::FILE_FILTER);
    if (!fileName.isEmpty()) {
        QString content = m_fileService->openFile(fileName);
        if (!content.isNull()) {
            m_textEdit->setPlainText(content);
            m_currentFilePath = fileName;
            setWindowTitle(AppConstants::APP_NAME + " - " + QFileInfo(fileName).fileName());
        } else {
            QMessageBox::warning(this, FileOperations::ERROR_DIALOG_TITLE, m_fileService->getLastError());
        }
    }
}

void MainWindow::saveFile()
{
    QString fileName = m_currentFilePath;
    if (fileName.isEmpty()) {
        QString defaultDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
        fileName = QFileDialog::getSaveFileName(this, FileOperations::SAVE_DIALOG_TITLE, defaultDir, AppConstants::FILE_FILTER);
        if (fileName.isEmpty()) return;
    }
    QString content = m_textEdit->toPlainText();
    if (!m_fileService->saveFile(fileName, content)) {
        QMessageBox::warning(this, FileOperations::ERROR_DIALOG_TITLE, m_fileService->getLastError());
    } else {
        m_currentFilePath = fileName;
        setWindowTitle(AppConstants::APP_NAME + " - " + QFileInfo(fileName).fileName());
    }
}

void MainWindow::saveAsFile()
{
    QString defaultDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString fileName = QFileDialog::getSaveFileName(this, FileOperations::SAVE_DIALOG_TITLE, defaultDir, AppConstants::FILE_FILTER);
    if (fileName.isEmpty()) return;
    QString content = m_textEdit->toPlainText();
    if (!m_fileService->saveFile(fileName, content)) {
        QMessageBox::warning(this, FileOperations::ERROR_DIALOG_TITLE, m_fileService->getLastError());
    } else {
        m_currentFilePath = fileName;
        setWindowTitle(AppConstants::APP_NAME + " - " + QFileInfo(fileName).fileName());
    }
}

void MainWindow::quitApplication()
{
    QApplication::quit();
}

// Text Editing Operations Slice
void MainWindow::undoText()
{
    m_textEdit->undo();
}

void MainWindow::redoText()
{
    m_textEdit->redo();
}

void MainWindow::cutText()
{
    m_textEdit->cut();
}

void MainWindow::copyText()
{
    m_textEdit->copy();
}

void MainWindow::pasteText()
{
    m_textEdit->paste();
}

// Font Management Operations Slice
void MainWindow::increaseFontSize()
{
    if (m_fontService->increaseFontSize()) {
        applyCurrentFont();
    }
}

void MainWindow::decreaseFontSize()
{
    if (m_fontService->decreaseFontSize()) {
        applyCurrentFont();
    }
}

void MainWindow::applyCurrentFont()
{
    QFont currentFont = m_fontService->getDefaultFont();
    currentFont.setPointSize(m_fontService->getCurrentFontSize());
    m_textEdit->setFont(currentFont);
    
    // Update line number widget font
    if (m_lineNumberWidget) {
        m_lineNumberWidget->updateFont();
    }
} 