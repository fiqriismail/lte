QT += widgets
TARGET = lte
TEMPLATE = app

QMAKE_INFO_PLIST = Info.plist

# Core application
SOURCES += src/core/main.cpp

# UI layer
SOURCES += src/ui/mainwindow.cpp \
           src/ui/toolbar.cpp
HEADERS += src/ui/mainwindow.h \
           src/ui/toolbar.h

# File operations feature
SOURCES += features/file-operations/fileservice.cpp
HEADERS += features/file-operations/fileservice.h

# Shared interfaces and types
HEADERS += features/shared/interfaces/ifileservice.h
HEADERS += features/shared/types/common.h

# Include paths
INCLUDEPATH += src/ui
INCLUDEPATH += features/file-operations
INCLUDEPATH += features/shared/interfaces
INCLUDEPATH += features/shared/types 