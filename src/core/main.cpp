#include <QApplication>
#include "../ui/mainwindow.h"
#include "../../features/file-operations/fileservice.h"
#include "../../features/font-management/fontservice.h"
#include "../../features/line-numbers/linenumberservice.h"
#include "../../features/shared/types/common.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Set application name for menu bar
    app.setApplicationName(AppConstants::APP_NAME);
    app.setApplicationVersion(AppConstants::APP_VERSION);
    
    // Create services with dependency injection
    FileService *fileService = new FileService(&app);
    FontService *fontService = new FontService();
    LineNumberService *lineNumberService = new LineNumberService();
    
    // Create main window with injected dependencies
    MainWindow window(fileService, fontService, lineNumberService);
    window.show();
    
    return app.exec();
} 