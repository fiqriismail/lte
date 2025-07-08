#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMenuBar>
#include <QAction>
#include <QFont>
#include "toolbar.h"
#include "../../features/shared/interfaces/ifileservice.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(IFileService *fileService, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // File operations
    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();
    void quitApplication();

    // Text editing operations
    void undoText();
    void redoText();
    void cutText();
    void copyText();
    void pasteText();

    // Font management operations
    void increaseFontSize();
    void decreaseFontSize();

private:
    void setupUI();
    void setupFileMenu();
    void setupEditMenu();
    void setupToolBar();
    void setupFontManagement();
    void connectSignals();
    bool maybeSave();
    void setFontSize(int size);

    QTextEdit *m_textEdit;
    QMenuBar *m_menuBar;
    ToolBar *m_toolBar;
    IFileService *m_fileService;
    QString m_currentFilePath;
    
    // Font management
    QFont m_defaultFont;
    int m_currentFontSize;
    static const int MIN_FONT_SIZE = 8;
    static const int MAX_FONT_SIZE = 25;
    static const int DEFAULT_FONT_SIZE = 12;
    
    // File menu actions
    QAction *m_newAction;
    QAction *m_openAction;
    QAction *m_saveAction;
    QAction *m_saveAsAction;
    QAction *m_quitAction;
    
    // Edit menu actions
    QAction *m_undoAction;
    QAction *m_redoAction;
    QAction *m_cutAction;
    QAction *m_copyAction;
    QAction *m_pasteAction;
    
    // Font management actions
    QAction *m_zoomInAction;
    QAction *m_zoomOutAction;
};

#endif // MAINWINDOW_H 