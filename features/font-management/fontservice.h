#ifndef FONTSERVICE_H
#define FONTSERVICE_H

#include <QObject>
#include <QFont>
#include "../shared/interfaces/ifontservice.h"

class FontService : public QObject, public IFontService
{
    Q_OBJECT

public:
    FontService(QObject *parent = nullptr);
    ~FontService() override;

    // IFontService implementation
    QFont getDefaultFont() const override;
    void setFontSize(int size) override;
    int getCurrentFontSize() const override;
    bool increaseFontSize() override;
    bool decreaseFontSize() override;
    bool isValidFontSize(int size) const override;

private:
    QFont m_defaultFont;
    int m_currentFontSize;
    
    void initializeDefaultFont();
};

#endif // FONTSERVICE_H 