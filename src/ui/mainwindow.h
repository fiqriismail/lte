#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMenuBar>
#include <QAction>
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

private:
    void setupUI();
    void setupFileMenu();
    void setupEditMenu();
    void setupToolBar();
    void connectSignals();
    bool maybeSave();

    QTextEdit *m_textEdit;
    QMenuBar *m_menuBar;
    ToolBar *m_toolBar;
    IFileService *m_fileService;
    QString m_currentFilePath;
    
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
};

#endif // MAINWINDOW_H 