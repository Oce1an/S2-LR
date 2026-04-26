#include "trainermodel.h"
#include <QRegularExpression>

TrainerModel::TrainerModel(QObject *parent)
    : QObject(parent) {}

void TrainerModel::setText(const QString &text) {
    // Разбиваем на слова по пробельным символам
    m_words = text.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    reset();
    emit textChanged();
}

void TrainerModel::reset() {
    m_currentWord = 0;
    m_currentCharInWord = 0;
    m_active = false;
    m_wordCorrect.clear();
    m_wordCorrect.resize(m_words.size());
    m_wordCorrect.fill(false);
    m_correctCount = 0;
    m_incorrectCount = 0;
    m_elapsedAccum = 0;
    m_currentWordError = false;
}

void TrainerModel::start() {
    if (m_words.isEmpty()) return;
    m_active = true;
    m_timer.start();
    m_elapsedAccum = 0;
}

void TrainerModel::stop() {
    if (m_active) {
        m_elapsedAccum += m_timer.elapsed();
        m_active = false;
    }
}

bool TrainerModel::isActive() const { return m_active; }

bool TrainerModel::processCharacter(const QString &ch) {
    if (!m_active || m_currentWord >= m_words.size())
        return false;

    // Игнорируем пробельные и пустые строки, они обрабатываются отдельно
    if (ch.isEmpty() || ch == " ")
        return false;

    const QString &expectedWord = m_words.at(m_currentWord);
    if (m_currentCharInWord >= expectedWord.length())
        return false;

    QChar expected = expectedWord.at(m_currentCharInWord);
    bool correct = (ch.at(0) == expected);

    if (!correct)
        m_currentWordError = true;

    ++m_currentCharInWord;
    return true;
}

void TrainerModel::finishCurrentWord() {
    if (!m_active || m_currentWord >= m_words.size())
        return;

    const QString &word = m_words.at(m_currentWord);
    bool allTyped = (m_currentCharInWord == word.length());
    bool correct = allTyped && !m_currentWordError;

    m_wordCorrect[m_currentWord] = correct;
    if (correct)
        ++m_correctCount;
    else
        ++m_incorrectCount;

    emit wordCompleted(m_currentWord, correct);

    ++m_currentWord;
    m_currentCharInWord = 0;
    m_currentWordError = false;

    if (m_currentWord >= m_words.size()) {
        stop();
        emit statsUpdated();
    }
}

bool TrainerModel::hasErrorInCurrentWord() const {
    return m_currentWordError;
}

QStringList TrainerModel::words() const { return m_words; }
int TrainerModel::currentWordIndex() const { return m_currentWord; }
int TrainerModel::currentPositionInWord() const { return m_currentCharInWord; }

bool TrainerModel::isWordFinished(int wordIndex) const {
    return wordIndex < m_currentWord;
}

bool TrainerModel::isWordCorrect(int wordIndex) const {
    if (wordIndex < m_wordCorrect.size())
        return m_wordCorrect.at(wordIndex);
    return false;
}

int TrainerModel::correctWordsCount() const { return m_correctCount; }
int TrainerModel::incorrectWordsCount() const { return m_incorrectCount; }

int TrainerModel::elapsedSeconds() const {
    qint64 ms = m_elapsedAccum;
    if (m_active)
        ms += m_timer.elapsed();
    return static_cast<int>(ms / 1000);
}

int TrainerModel::wordsPerMinute() const {
    int sec = elapsedSeconds();
    if (sec == 0) return 0;
    double min = sec / 60.0;
    return static_cast<int>(m_correctCount / min);
}

bool TrainerModel::isFinished() const {
    return m_currentWord >= m_words.size();
}