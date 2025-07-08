#!/bin/bash

# Little Text Editor Build Script
# Vertical Slicing Architecture

echo "🏗️  Building Little Text Editor, a.k.a LTE..."
echo "📁 Project: Vertical Slicing Architecture"
echo ""

# Clean previous build
echo "🧹 Cleaning previous build..."
make clean 2>/dev/null || true

# Generate Makefile
echo "📋 Generating Makefile..."
qmake lte.pro

# Build the project
echo "🔨 Building project..."
make

if [ $? -eq 0 ]; then
    echo ""
    echo "✅ Build successful!"
    echo "🚀 To run the application:"
    echo "   open lte.app"
    echo ""
    echo "📁 Build artifacts:"
    echo "   - lte.app (macOS application bundle)"
    echo "   - Makefile (generated build configuration)"
else
    echo ""
    echo "❌ Build failed!"
    echo "🔍 Check the error messages above."
    exit 1
fi 