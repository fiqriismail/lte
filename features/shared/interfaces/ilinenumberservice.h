#ifndef ILINENUMBERSERVICE_H
#define ILINENUMBERSERVICE_H

#include <QString>

class ILineNumberService
{
public:
    virtual ~ILineNumberService() = default;
    
    // Get the current line count
    virtual int getLineCount() const = 0;
    
    // Get the line number text for a specific line (1-based)
    virtual QString getLineNumberText(int lineNumber) const = 0;
    
    // Get the maximum line number width in pixels for the current font
    virtual int getMaxLineNumberWidth() const = 0;
    
    // Update line count based on text content
    virtual void updateLineCount(const QString& text) = 0;
    
    // Set the font for line number rendering
    virtual void setFont(const QFont& font) = 0;
    
    // Get the current font
    virtual QFont getFont() const = 0;
};

#endif // ILINENUMBERSERVICE_H 