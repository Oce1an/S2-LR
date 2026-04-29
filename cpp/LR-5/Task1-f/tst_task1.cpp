#include <QtTest/QtTest>
#include "trainer.h"

class TestTask1 : public QObject
{
    Q_OBJECT

private slots:

    // ===== setText / reset =====

    void setText_basic()
    {
        Trainer t;
        t.setText("hello");
        QCOMPARE(t.text(), QString("hello"));
        QCOMPARE(t.position(), 0);
        QVERIFY(!t.finished());
    }

    void reset_clearsState()
    {
        Trainer t;
        t.setText("ab");
        t.typeChar('a');
        t.reset();
        QCOMPARE(t.position(), 0);
        QCOMPARE(t.mistakeCount(), 0);
        QCOMPARE(t.correctCount(), 0);
    }

    // ===== typeChar =====

    void typeChar_correct()
    {
        Trainer t;
        t.setText("abc");
        QVERIFY(t.typeChar('a'));
        QCOMPARE(t.position(), 1);
        QCOMPARE(t.correctCount(), 1);
        QCOMPARE(t.mistakeCount(), 0);
    }

    void typeChar_wrong_doesNotAdvance()
    {
        // При ошибке позиция НЕ должна продвигаться
        Trainer t;
        t.setText("abc");
        QVERIFY(!t.typeChar('x'));
        QCOMPARE(t.mistakeCount(), 1);
        QCOMPARE(t.correctCount(), 0);
        QCOMPARE(t.position(), 0); // позиция не изменилась
    }

    void typeChar_wrong_thenCorrect_advances()
    {
        // После ошибки верный символ продвигает курсор
        Trainer t;
        t.setText("abc");
        QVERIFY(!t.typeChar('x')); // ошибка
        QVERIFY(t.typeChar('a'));  // верно
        QCOMPARE(t.position(), 1);
        QCOMPARE(t.mistakeCount(), 1);
        QCOMPARE(t.correctCount(), 1);
    }

    void typeChar_finishes()
    {
        Trainer t;
        t.setText("a");
        t.typeChar('a');
        QVERIFY(t.finished());
    }

    void typeChar_pastEnd_returnsFalse()
    {
        Trainer t;
        t.setText("a");
        t.typeChar('a');
        bool result = t.typeChar('a');
        QVERIFY(!result);
        QCOMPARE(t.position(), 1);
    }

    // ===== accuracy =====

    void accuracy_allCorrect()
    {
        Trainer t;
        t.setText("hi");
        t.typeChar('h');
        t.typeChar('i');
        QCOMPARE(t.accuracy(), 100.0);
    }

    void accuracy_withMistakes()
    {
        Trainer t;
        t.setText("ab");
        t.typeChar('x'); // ошибка на 'a'
        t.typeChar('a'); // верно
        // correctCount=1, mistakes=1 → accuracy=50%
        double acc = t.accuracy();
        QCOMPARE(acc, 50.0);
    }

    void accuracy_empty()
    {
        Trainer t;
        t.setText("x");
        QCOMPARE(t.accuracy(), 100.0);
    }

    // ===== wordCount =====

    void wordCount_single()
    {
        Trainer t;
        QCOMPARE(t.wordCount("hello"), 1);
    }

    void wordCount_multiple()
    {
        Trainer t;
        QCOMPARE(t.wordCount("one two three"), 3);
    }

    void wordCount_empty()
    {
        Trainer t;
        QCOMPARE(t.wordCount(""), 0);
    }

    void wordCount_extraSpaces()
    {
        Trainer t;
        QCOMPARE(t.wordCount("  a  b  "), 2);
    }

    // ===== WPM =====

    void wpm_zero_elapsed()
    {
        Trainer t;
        t.setText("hello world");
        t.typeChar('h');
        QCOMPARE(t.wordsPerMinute(0), 0.0);
    }

    void wpm_oneWord_oneMinute()
    {
        Trainer t;
        t.setText("hello world");
        for (QChar c : QString("hello "))
            t.typeChar(c);
        double wpm = t.wordsPerMinute(60000);
        QVERIFY(qAbs(wpm - 1.0) < 0.01);
    }

    // ===== Language names =====

    void languageName_allValid()
    {
        QVERIFY(!Trainer::languageName(Language::German).isEmpty());
        QVERIFY(!Trainer::languageName(Language::French).isEmpty());
        QVERIFY(!Trainer::languageName(Language::Arabic).isEmpty());
        QVERIFY(!Trainer::languageName(Language::Chinese).isEmpty());
        QVERIFY(!Trainer::languageName(Language::Belarusian).isEmpty());
        QVERIFY(!Trainer::languageName(Language::Hebrew).isEmpty());
    }

    // ===== Sample text =====

    void sampleText_notEmpty()
    {
        for (int i = 0; i < 6; ++i) {
            Language l = static_cast<Language>(i);
            QVERIFY(!Trainer::sampleText(l).isEmpty());
        }
    }

    // ===== Keyboard layout =====

    void keyboardLayout_hasRows()
    {
        for (int i = 0; i < 6; ++i) {
            Language l = static_cast<Language>(i);
            auto layout = Trainer::keyboardLayout(l);
            QVERIFY(layout.size() >= 4);
        }
    }
};

QTEST_APPLESS_MAIN(TestTask1)
#include "tst_task1.moc"
