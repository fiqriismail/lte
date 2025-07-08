#include "linenumberservice.h"
#include <QTextStream>

LineNumberService::LineNumberService()
    : m_lineCount(1)
    , m_font()
    , m_fontMetrics(m_font)
    , m_maxLineNumberWidth(0)
{
    updateMaxWidth();
}

int LineNumberService::getLineCount() const
{
    return m_lineCount;
}

QString LineNumberService::getLineNumberText(int lineNumber) const
{
    if (lineNumber < 1 || lineNumber > m_lineCount) {
        return QString();
    }
    return QString::number(lineNumber);
}

int LineNumberService::getMaxLineNumberWidth() const
{
    return m_maxLineNumberWidth;
}

void LineNumberService::updateLineCount(const QString& text)
{
    if (text.isEmpty()) {
        m_lineCount = 1;
    } else {
        // Count the number of lines in the text
        m_lineCount = text.count('\n') + 1;
    }
    updateMaxWidth();
}

void LineNumberService::setFont(const QFont& font)
{
    m_font = font;
    m_fontMetrics = QFontMetrics(m_font);
    updateMaxWidth();
}

QFont LineNumberService::getFont() const
{
    return m_font;
}

void LineNumberService::updateMaxWidth()
{
    // Calculate the width needed for the largest line number
    QString maxLineNumber = QString::number(m_lineCount);
    int textWidth = m_fontMetrics.horizontalAdvance(maxLineNumber);
    
    // Add some padding for better appearance
    m_maxLineNumberWidth = textWidth + 20; // 10px padding on each side
} 