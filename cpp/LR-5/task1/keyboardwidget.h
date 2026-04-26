//----------------------- keyboardwidget.h -----------------------
#ifndef KEYBOARDWIDGET_H
#define KEYBOARDWIDGET_H

#include <QWidget>
#include <QStringList>
#include <QMap>
#include <QTimer>

class KeyboardWidget : public QWidget {
    Q_OBJECT
public:
    explicit KeyboardWidget(QWidget *parent = nullptr);

    void setKeyRows(const QStringList &rows);  // задать раскладку (3 строки)
    void highlightKey(const QString &key);     // подсветить клавишу

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void recalcRects();                        // пересчитать прямоугольники клавиш

    QStringList m_keyRows;
    QVector<QVector<QString>> m_keyChars;      // символы по рядам
    QVector<QVector<QRectF>> m_keyRects;       // прямоугольники клавиш
    QString m_highlightedKey;                  // подсвеченная клавиша
    QTimer m_clearHighlightTimer;
};

#endif // KEYBOARDWIDGET_H