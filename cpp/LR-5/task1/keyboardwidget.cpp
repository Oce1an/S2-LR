//----------------------- keyboardwidget.cpp -----------------------
#include "keyboardwidget.h"
#include <QPainter>
#include <QFontMetrics>
#include <QRegularExpression>

KeyboardWidget::KeyboardWidget(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(180);
    m_clearHighlightTimer.setSingleShot(true);
    m_clearHighlightTimer.setInterval(300);
    connect(&m_clearHighlightTimer, &QTimer::timeout, this, [this](){
        m_highlightedKey.clear();
        update();
    });
}

void KeyboardWidget::setKeyRows(const QStringList &rows) {
    m_keyRows = rows;
    recalcRects();
    update();
}

void KeyboardWidget::highlightKey(const QString &key) {
    m_highlightedKey = key;
    update();
    m_clearHighlightTimer.start();
}

void KeyboardWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    recalcRects();
}

void KeyboardWidget::recalcRects() {
    m_keyChars.clear();
    m_keyRects.clear();
    if (m_keyRows.isEmpty()) return;

    qreal margin = 8.0;
    qreal keyWidth = 30.0;
    qreal keyHeight = 40.0;

    for (int rowIdx = 0; rowIdx < m_keyRows.size(); ++rowIdx) {
        QStringList symbols = m_keyRows[rowIdx].split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        m_keyChars.append(symbols);
        QVector<QRectF> rects;
        int count = symbols.size();
        // Равномерно распределяем клавиши по ширине
        qreal totalWidth = width() - 2 * margin;
        qreal spacing = (count > 1) ? (totalWidth - count * keyWidth) / (count - 1) : 0;
        qreal xStart = margin;
        for (int i = 0; i < count; ++i) {
            QRectF r(xStart, margin + rowIdx * (keyHeight + 10.0), keyWidth, keyHeight);
            rects.append(r);
            xStart += keyWidth + spacing;
        }
        m_keyRects.append(rects);
    }
}

void KeyboardWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setFont(QFont("Sans", 10));

    // Определяем направление текста: если язык справа-налево, меняем компоновку (араб, иврит)
    // Упростим — оставим как есть, на клавишах символы в логическом порядке.
    for (int row = 0; row < m_keyChars.size() && row < m_keyRects.size(); ++row) {
        for (int i = 0; i < m_keyChars[row].size() && i < m_keyRects[row].size(); ++i) {
            QRectF rect = m_keyRects[row][i];
            // Фон клавиши
            QColor fill = Qt::lightGray;
            if (!m_highlightedKey.isEmpty() && m_keyChars[row][i] == m_highlightedKey) {
                fill = Qt::yellow;
            }
            painter.setBrush(fill);
            painter.setPen(Qt::black);
            painter.drawRoundedRect(rect, 3, 3);

            // Текст клавиши
            painter.setPen(Qt::black);
            painter.drawText(rect, Qt::AlignCenter, m_keyChars[row][i]);
        }
    }
}