# Little Text Editor, a.k.a LTE

A Qt-based text editor built with Vertical Slicing Architecture.

## 🏗️ Architecture Overview

This project follows **Vertical Slicing Architecture**, organizing code by features rather than technical layers.

### Directory Structure

```
/
├── src/
│   ├── core/           # Application entry point
│   │   └── main.cpp
│   └── ui/            # User interface layer
│       ├── mainwindow.h
│       └── mainwindow.cpp
├── features/           # Feature-based organization
│   ├── shared/        # Shared components
│   │   ├── interfaces/
│   │   │   └── ifileservice.h
│   │   └── types/
│   │       └── common.h
│   ├── file-operations/  # File operations feature
│   │   ├── fileservice.h
│   │   └── fileservice.cpp
│   ├── text-editing/     # Text editing feature (future)
│   └── app-lifecycle/    # App lifecycle feature (future)
├── hello.pro           # Qt project file
├── build.sh            # Build script
├── .gitignore          # Git ignore rules
└── README.md
```

### Vertical Slices

#### 1. **File Operations Slice**
- **Location**: `features/file-operations/`
- **Components**: 
  - `FileService` - Business logic for file I/O
  - `IFileService` - Interface for dependency injection
- **Features**: Open, Save, Error handling

#### 2. **Text Editing Slice**
- **Location**: `src/ui/` (currently integrated)
- **Components**: `MainWindow` text editing methods
- **Features**: Undo, Redo, Cut, Copy, Paste

#### 3. **Application Lifecycle Slice**
- **Location**: `src/core/`
- **Components**: `main.cpp` - Application entry point
- **Features**: App initialization, dependency injection

#### 4. **Shared Components**
- **Location**: `features/shared/`
- **Components**: Interfaces, types, constants
- **Purpose**: Reusable across features

## 🚀 Building and Running

### Quick Build
```bash
# Use the build script (recommended)
./build.sh

# Run the application
open lte.app
```

### Manual Build
```bash
# Clean and build
make clean && make

# Or step by step
qmake hello.pro
make
```

## 🧪 Architecture Benefits

### ✅ **Feature-Focused**
Each slice contains everything needed for a feature (UI, business logic, data access).

### ✅ **Testable**
Services can be unit tested independently using interfaces.

### ✅ **Maintainable**
Changes to one feature don't affect others.

### ✅ **Scalable**
Easy to add new features as new vertical slices.

### ✅ **Loose Coupling**
Services are independent of UI through dependency injection.

### ✅ **Clear Responsibilities**
Each class has a single, well-defined purpose.

## 🔧 Adding New Features

To add a new feature:

1. Create a new directory in `features/`
2. Define interfaces in `features/shared/interfaces/`
3. Implement business logic in the feature directory
4. Update UI in `src/ui/` to use the new service
5. Update `lte.pro` to include new files

## 📋 Project Files

### Core Files
- `src/core/main.cpp` - Application entry point
- `src/ui/mainwindow.h/cpp` - Main window UI
- `lte.pro` - Qt project configuration

### Feature Files
- `features/file-operations/fileservice.h/cpp` - File operations
- `features/shared/interfaces/ifileservice.h` - File service interface
- `features/shared/types/common.h` - Shared constants

### Build & Configuration
- `build.sh` - Automated build script
- `.gitignore` - Git ignore rules for Qt/C++ projects
- `README.md` - Project documentation
