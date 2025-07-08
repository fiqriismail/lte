#include "linenumberwidget.h"
#include <QPainter>
#include <QScrollBar>
#include <QTextDocument>
#include <QTextBlock>
#include <QAbstractTextDocumentLayout>
#include <QStyleOption>

LineNumberWidget::LineNumberWidget(ILineNumberService *lineNumberService, QWidget *parent)
    : QWidget(parent)
    , m_lineNumberService(lineNumberService)
    , m_textEdit(nullptr)
    , m_lineHeight(0)
    , m_totalHeight(0)
{
    setFixedWidth(60); // Default width, will be updated by service
    setAttribute(Qt::WA_StaticContents);
    
    // Set background color
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor(240, 240, 240)); // Light gray background
    setPalette(pal);
    setAutoFillBackground(true);
}

void LineNumberWidget::setTextEditor(QTextEdit *textEdit)
{
    m_textEdit = textEdit;
    setupConnections();
    updateLineNumbers();
}

void LineNumberWidget::updateLineNumbers()
{
    if (!m_textEdit) return;
    
    // Update the service with current text
    QString text = m_textEdit->toPlainText();
    m_lineNumberService->updateLineCount(text);
    
    // Update widget width
    updateWidth();
    
    // Trigger repaint
    update();
}

void LineNumberWidget::updateWidth()
{
    int newWidth = m_lineNumberService->getMaxLineNumberWidth();
    if (newWidth > 0) {
        setFixedWidth(newWidth);
    }
}

void LineNumberWidget::paintEvent(QPaintEvent *event)
{
    if (!m_textEdit) return;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setFont(m_lineNumberService->getFont());

    // Match background to QTextEdit
    QColor bgColor = m_textEdit->palette().color(QPalette::Base);
    painter.fillRect(rect(), bgColor);

    // Professional UX: softer, less prominent line number color
    QColor lineNumberColor = (bgColor.lightness() < 128)
        ? QColor("#888888") // dark mode: soft gray
        : QColor("#b0b0b0"); // light mode: medium gray
    painter.setPen(lineNumberColor);

    // Draw a subtle right border
    QColor borderColor = (bgColor.lightness() < 128) ? QColor(60, 60, 60) : QColor(200, 200, 200);
    painter.setPen(borderColor);
    painter.drawLine(width() - 1, 0, width() - 1, height());
    painter.setPen(lineNumberColor);

    QTextDocument *doc = m_textEdit->document();
    QAbstractTextDocumentLayout *layout = doc->documentLayout();
    int contentsY = m_textEdit->verticalScrollBar()->value();
    int viewportHeight = m_textEdit->viewport()->height();

    QTextBlock block = doc->firstBlock();
    int blockNumber = 1;
    while (block.isValid()) {
        QRectF rect = layout->blockBoundingRect(block);
        int top = static_cast<int>(rect.translated(0, -contentsY).top());
        int bottom = static_cast<int>(rect.translated(0, -contentsY).bottom());
        if (bottom >= 0 && top <= viewportHeight) {
            QString lineNumber = m_lineNumberService->getLineNumberText(blockNumber);
            QRect textRect(0, top, width() - 5, static_cast<int>(rect.height()));
            painter.drawText(textRect, Qt::AlignRight | Qt::AlignVCenter, lineNumber);
        }
        block = block.next();
        ++blockNumber;
    }
}

void LineNumberWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}

void LineNumberWidget::onTextChanged()
{
    updateLineNumbers();
}

void LineNumberWidget::onFontChanged()
{
    updateFont();
}

void LineNumberWidget::updateFont()
{
    if (m_textEdit) {
        m_lineNumberService->setFont(m_textEdit->font());
    }
    updateLineNumbers();
}

void LineNumberWidget::setupConnections()
{
    if (!m_textEdit) return;
    connect(m_textEdit->document(), &QTextDocument::contentsChanged, this, &LineNumberWidget::onTextChanged);
    // Font changes handled manually
    if (m_textEdit->verticalScrollBar()) {
        connect(m_textEdit->verticalScrollBar(), &QScrollBar::valueChanged, this, [this]() { update(); });
    }
}

void LineNumberWidget::calculateLinePositions() {} 