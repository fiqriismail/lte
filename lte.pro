QT += widgets
TARGET = lte
TEMPLATE = app

QMAKE_INFO_PLIST = Info.plist

# Core application
SOURCES += src/core/main.cpp

# UI layer
SOURCES += src/ui/mainwindow.cpp \
           src/ui/toolbar.cpp \
           src/ui/linenumberwidget.cpp
HEADERS += src/ui/mainwindow.h \
           src/ui/toolbar.h \
           src/ui/linenumberwidget.h

# File operations feature
SOURCES += features/file-operations/fileservice.cpp
HEADERS += features/file-operations/fileservice.h

# Font management feature
SOURCES += features/font-management/fontservice.cpp
HEADERS += features/font-management/fontservice.h

# Line numbers feature
SOURCES += features/line-numbers/linenumberservice.cpp
HEADERS += features/line-numbers/linenumberservice.h

# Shared interfaces and types
HEADERS += shared/interfaces/ifileservice.h
HEADERS += shared/interfaces/ifontservice.h
HEADERS += shared/interfaces/ilinenumberservice.h
HEADERS += shared/types/common.h

# Include paths
INCLUDEPATH += src/ui
INCLUDEPATH += features/file-operations
INCLUDEPATH += features/font-management
INCLUDEPATH += features/line-numbers
INCLUDEPATH += shared/interfaces
INCLUDEPATH += shared/types 