#ifndef TRAINER_H
#define TRAINER_H

#include <QString>
#include <QStringList>
#include <QVector>

enum class Language { German, French, Arabic, Chinese, Belarusian, Hebrew };

struct CharResult {
    QChar ch;
    bool  correct;
};

class Trainer
{
public:
    Trainer();

    void    setText(const QString &text);
    QString text() const;
    void    reset();

    static QStringList        sampleText(Language lang);
    static QString            languageName(Language lang);
    static QList<QStringList> keyboardLayout(Language lang);

    // Возвращает true если символ верный.
    // При ошибке позиция НЕ продвигается — пользователь должен ввести
    // правильный символ, чтобы перейти дальше.
    bool   typeChar(QChar ch);
    int    position()     const;
    bool   finished()     const;

    int    mistakeCount() const;
    int    correctCount() const;
    double accuracy()     const;
    double wordsPerMinute(int elapsedMs) const;
    int    wordCount(const QString &s) const;

    // Доступ к истории результатов (для подсветки)
    const QVector<CharResult>& results() const { return m_results; }
    
    // Флаг последней ошибки для визуальной индикации
    bool   hasLastError() const;
    void   clearLastError() { m_lastError = false; }

private:
    QString             m_text;
    int                 m_pos;
    int                 m_mistakes;
    int                 m_correct;
    QVector<CharResult> m_results;
    bool                m_lastError = false;  // флаг последней ошибки
};

#endif // TRAINER_H