#ifndef LINENUMBERSERVICE_H
#define LINENUMBERSERVICE_H

#include <QString>
#include <QFont>
#include <QFontMetrics>
#include "../shared/interfaces/ilinenumberservice.h"

class LineNumberService : public ILineNumberService
{
public:
    LineNumberService();
    ~LineNumberService() override = default;
    
    // ILineNumberService implementation
    int getLineCount() const override;
    QString getLineNumberText(int lineNumber) const override;
    int getMaxLineNumberWidth() const override;
    void updateLineCount(const QString& text) override;
    void setFont(const QFont& font) override;
    QFont getFont() const override;

private:
    void updateMaxWidth();
    
    int m_lineCount;
    QFont m_font;
    QFontMetrics m_fontMetrics;
    int m_maxLineNumberWidth;
};

#endif // LINENUMBERSERVICE_H 