#ifndef COMMON_H
#define COMMON_H

#include <QString>

namespace AppConstants
{
    const QString APP_NAME = "Little Text Editor";
    const QString APP_VERSION = "1.0.0";
    const int DEFAULT_WINDOW_WIDTH = 600;
    const int DEFAULT_WINDOW_HEIGHT = 400;
    const QString FILE_FILTER = "Text Files (*.txt);;All Files (*)";
}

namespace FileOperations
{
    const QString OPEN_DIALOG_TITLE = "Open Text File";
    const QString SAVE_DIALOG_TITLE = "Save Text File";
    const QString ERROR_DIALOG_TITLE = "Error";
}

#endif // COMMON_H 