#ifndef TRAINERMODEL_H
#define TRAINERMODEL_H

#include <QObject>
#include <QStringList>
#include <QElapsedTimer>
#include <QTime>
#include <QVector>

class TrainerModel : public QObject {
    Q_OBJECT
public:
    explicit TrainerModel(QObject *parent = nullptr);

    void setText(const QString &text);
    void reset();
    void start();
    void stop();
    bool isActive() const;

    // Обработка одного видимого символа. Возвращает true, если символ принят.
    bool processCharacter(const QString &ch);
    // Завершить текущее слово (вызывается по пробелу или принудительно)
    void finishCurrentWord();
    // Была ли ошибка в текущем (ещё не завершённом) слове
    bool hasErrorInCurrentWord() const;

    // Доступ к данным
    QStringList words() const;
    int currentWordIndex() const;
    int currentPositionInWord() const;
    bool isWordFinished(int wordIndex) const;
    bool isWordCorrect(int wordIndex) const;

    // Статистика
    int correctWordsCount() const;
    int incorrectWordsCount() const;
    int elapsedSeconds() const;
    int wordsPerMinute() const;
    bool isFinished() const;

signals:
    void textChanged();
    void statsUpdated();
    void wordCompleted(int index, bool correct);

private:
    QStringList m_words;
    int m_currentWord = 0;
    int m_currentCharInWord = 0;
    bool m_active = false;
    bool m_currentWordError = false;

    QVector<bool> m_wordCorrect;
    int m_correctCount = 0;
    int m_incorrectCount = 0;

    QElapsedTimer m_timer;
    int m_elapsedAccum = 0;  // накопленное время при паузе
};

#endif // TRAINERMODEL_H