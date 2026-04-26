//----------------------- textdisplay.cpp -----------------------
#include "textdisplay.h"
#include <QPainter>
#include <QFontMetrics>

TextDisplay::TextDisplay(TrainerModel *model, QWidget *parent)
    : QWidget(parent), m_model(model)
{
    setMinimumHeight(200);
    setFont(QFont("Sans", 18));
    setFocusPolicy(Qt::NoFocus); // фокус не принимаем, ввод через скрытое поле
}

void TextDisplay::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setFont(font());

    const QStringList words = m_model->words();
    if (words.isEmpty()) return;

    int curWordIdx = m_model->currentWordIndex();
    int curPosInWord = m_model->currentPositionInWord();

    QFontMetrics fm = painter.fontMetrics();
    int lineHeight = fm.height();
    int margin = 10;
    int x = margin, y = margin;

    for (int w = 0; w < words.size(); ++w) {
        const QString &word = words.at(w);
        // Определяем цвет слова
        QColor wordColor = Qt::black;

        if (w < curWordIdx) {
            // Пройденное слово
            wordColor = m_model->isWordCorrect(w) ? Qt::darkGreen : Qt::red;
        } else if (w == curWordIdx) {
            // Текущее слово: отрисовываем посимвольно
            // Введённая часть: зелёный/красный, оставшаяся — чёрный.
            int typedLen = qMin(curPosInWord, word.length());
            // Вычисляем ширину уже набранной части
            QString typedPart = word.left(typedLen);
            int typedWidth = fm.horizontalAdvance(typedPart);

            // Рисуем набранную часть. Если были ошибки, модель нам не говорит пока, используем предположение:
            // в текущей реализации ошибка слова определяется по флагу m_currentWordError.
            // Чтобы получить его, добавим метод в модель hasErrorInCurrentWord().
            // Пока просто отрисуем typedPart всё одним цветом, без детальной разбивки.
            QColor typedColor = m_model->hasErrorInCurrentWord() ? Qt::red : Qt::darkGreen;
            painter.setPen(typedColor);
            painter.drawText(x, y, typedPart);
            x += typedWidth;

            // Оставшаяся часть слова (ещё не введённая)
            QString rest = word.mid(typedLen);
            painter.setPen(Qt::black);
            painter.drawText(x, y, rest);
            x += fm.horizontalAdvance(rest);

            // Пробел после слова
            painter.setPen(Qt::black);
            painter.drawText(x, y, " ");
            x += fm.horizontalAdvance(" ");
        } else {
            // Будущие слова — серый
            wordColor = Qt::gray;
            painter.setPen(wordColor);
            painter.drawText(x, y, word + " ");
            x += fm.horizontalAdvance(word + " ");
        }

        // Перенос строки, если слово не помещается
        if (x > width() - margin * 2 && w < words.size() - 1) {
            x = margin;
            y += lineHeight;
        }
    }
}