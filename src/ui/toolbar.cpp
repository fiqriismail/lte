#include "toolbar.h"
#include <QStyle>

ToolBar::ToolBar(QWidget *parent)
    : QToolBar("Main Toolbar", parent)
{
    setMovable(false);
    setFloatable(false);
    setIconSize(QSize(20, 20));
}

void ToolBar::setupActions(QAction *newAction, QAction *openAction, QAction *saveAction)
{
    newAction->setIcon(style()->standardIcon(QStyle::SP_FileIcon));
    openAction->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    saveAction->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
    addAction(newAction);
    addAction(openAction);
    addAction(saveAction);
} 