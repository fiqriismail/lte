#include "fontservice.h"
#include <QFontDatabase>

FontService::FontService(QObject *parent)
    : QObject(parent)
    , m_currentFontSize(DEFAULT_FONT_SIZE)
{
    initializeDefaultFont();
}

FontService::~FontService()
{
    // Qt will handle cleanup
}

void FontService::initializeDefaultFont()
{
    m_defaultFont = QFont("SF Mono", DEFAULT_FONT_SIZE);
    m_defaultFont.setStyleHint(QFont::Monospace);
}

QFont FontService::getDefaultFont() const
{
    return m_defaultFont;
}

void FontService::setFontSize(int size)
{
    if (isValidFontSize(size)) {
        m_currentFontSize = size;
    }
}

int FontService::getCurrentFontSize() const
{
    return m_currentFontSize;
}

bool FontService::increaseFontSize()
{
    if (m_currentFontSize < MAX_FONT_SIZE) {
        m_currentFontSize++;
        return true;
    }
    return false;
}

bool FontService::decreaseFontSize()
{
    if (m_currentFontSize > MIN_FONT_SIZE) {
        m_currentFontSize--;
        return true;
    }
    return false;
}

bool FontService::isValidFontSize(int size) const
{
    return size >= MIN_FONT_SIZE && size <= MAX_FONT_SIZE;
} 