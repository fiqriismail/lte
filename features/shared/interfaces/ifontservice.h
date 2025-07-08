#ifndef IFONTSERVICE_H
#define IFONTSERVICE_H

#include <QFont>
#include <QString>

class IFontService
{
public:
    virtual ~IFontService() = default;
    
    // Font management operations
    virtual QFont getDefaultFont() const = 0;
    virtual void setFontSize(int size) = 0;
    virtual int getCurrentFontSize() const = 0;
    virtual bool increaseFontSize() = 0;
    virtual bool decreaseFontSize() = 0;
    virtual bool isValidFontSize(int size) const = 0;
    
    // Font constants
    static const int MIN_FONT_SIZE = 8;
    static const int MAX_FONT_SIZE = 25;
    static const int DEFAULT_FONT_SIZE = 12;
};

#endif // IFONTSERVICE_H 