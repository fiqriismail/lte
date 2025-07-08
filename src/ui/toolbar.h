#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QAction>
#include <QWidget>

class ToolBar : public QToolBar {
    Q_OBJECT
public:
    ToolBar(QWidget *parent = nullptr);
    void setupActions(QAction *newAction, QAction *openAction, QAction *saveAction);
};

#endif // TOOLBAR_H 