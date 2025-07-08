#ifndef LINENUMBERWIDGET_H
#define LINENUMBERWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include "shared/interfaces/ilinenumberservice.h"

class LineNumberWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LineNumberWidget(ILineNumberService *lineNumberService, QWidget *parent = nullptr);
    ~LineNumberWidget() = default;

    // Set the text editor to sync with
    void setTextEditor(QTextEdit *textEdit);
    
    // Update the line numbers display
    void updateLineNumbers();
    
    // Set the widget width based on the service
    void updateWidth();
    
    // Public method to update font (called from MainWindow)
    void updateFont();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onTextChanged();
    void onFontChanged();

private:
    void setupConnections();
    void calculateLinePositions();
    
    ILineNumberService *m_lineNumberService;
    QTextEdit *m_textEdit;
    QList<int> m_linePositions; // Y positions of each line
    int m_lineHeight;
    int m_totalHeight;
};

#endif // LINENUMBERWIDGET_H 