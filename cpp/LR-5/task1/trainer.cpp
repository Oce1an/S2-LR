#include "trainer.h"
#include <QStringList>

Trainer::Trainer()
    : m_pos(0), m_mistakes(0), m_correct(0)
{}

void Trainer::setText(const QString &text)
{
    m_text     = text;
    m_pos      = 0;
    m_mistakes = 0;
    m_correct  = 0;
    m_results.clear();
    m_lastError = false;  // сбрасываем флаг ошибки
}

QString Trainer::text() const { return m_text; }

void Trainer::reset()
{
    m_pos      = 0;
    m_mistakes = 0;
    m_correct  = 0;
    m_results.clear();
    m_lastError = false;  // сбрасываем флаг ошибки
}

bool Trainer::typeChar(QChar ch)
{
    if (m_pos >= m_text.length()) {
        m_lastError = false;
        return false;
    }

    bool ok = (ch == m_text.at(m_pos));

    if (ok) {
        // Верный символ — фиксируем и продвигаем курсор
        m_results.append({m_text.at(m_pos), true});
        ++m_correct;
        ++m_pos;
        m_lastError = false;  // сбрасываем флаг ошибки при правильном вводе
    } else {
        // Ошибка — увеличиваем счётчик ошибок, курсор НЕ двигаем.
        // Устанавливаем флаг ошибки для временной подсветки в UI
        ++m_mistakes;
        m_lastError = true;   // устанавливаем флаг ошибки для визуальной индикации
    }

    return ok;
}

int  Trainer::position()     const { return m_pos; }
bool Trainer::finished()     const { return m_pos >= m_text.length(); }
int  Trainer::mistakeCount() const { return m_mistakes; }
int  Trainer::correctCount() const { return m_correct; }
bool Trainer::hasLastError() const { return m_lastError; }

double Trainer::accuracy() const
{
    int total = m_correct + m_mistakes;
    if (total == 0) return 100.0;
    return 100.0 * m_correct / total;
}

int Trainer::wordCount(const QString &s) const
{
    if (s.trimmed().isEmpty()) return 0;
    return s.split(' ', Qt::SkipEmptyParts).count();
}

double Trainer::wordsPerMinute(int elapsedMs) const
{
    if (elapsedMs <= 0) return 0.0;
    QString typed   = m_text.left(m_pos);
    double  words   = wordCount(typed);
    double  minutes = elapsedMs / 60000.0;
    return words / minutes;
}

// ---- Static helpers ----

QString Trainer::languageName(Language lang)
{
    switch (lang) {
    case Language::German:     return QStringLiteral("Немецкий");
    case Language::French:     return QStringLiteral("Французский");
    case Language::Arabic:     return QStringLiteral("Арабский");
    case Language::Chinese:    return QStringLiteral("Китайский");
    case Language::Belarusian: return QStringLiteral("Белорусский");
    case Language::Hebrew:     return QStringLiteral("Иврит");
    }
    return {};
}

QStringList Trainer::sampleText(Language lang)
{
    switch (lang) {
    case Language::German:
        return {
            "Die Sonne scheint hell am blauen Himmel.",
            "Ein guter Freund ist schwer zu finden.",
            "Das Buch liegt auf dem Tisch neben der Lampe."
        };
    case Language::French:
        return {
            "Le soleil brille dans le ciel bleu.",
            "Un bon ami est difficile a trouver.",
            "Le livre est sur la table a cote de la lampe."
        };
    case Language::Arabic:
        return {
            "\u0627\u0644\u0634\u0645\u0633 \u062a\u0633\u0637\u0639 \u0641\u064a \u0627\u0644\u0633\u0645\u0627\u0621 \u0627\u0644\u0632\u0631\u0642\u0627\u0621.",
            "\u0635\u062f\u064a\u0642 \u062c\u064a\u062f \u0635\u0639\u0628 \u0627\u0644\u0625\u064a\u062c\u0627\u062f.",
            "\u0627\u0644\u0643\u062a\u0627\u0628 \u0639\u0644\u0649 \u0627\u0644\u0637\u0627\u0648\u0644\u0629."
        };
    case Language::Chinese:
        return {
            "\u592a\u9633\u5728\u84dd\u5929\u4e0a\u95ea\u8000\u3002",
            "\u597d\u670b\u53cb\u96be\u4ee5\u5bfb\u627e\u3002",
            "\u4e66\u5728\u684c\u5b50\u4e0a\u7684\u706f\u65c1\u3002"
        };
    case Language::Belarusian:
        return {
            "\u0421\u043e\u043d\u0446\u0430 \u0441\u0432\u0435\u0446\u0456\u0446\u044c \u044f\u0440\u043a\u0430 \u045e \u0441\u0456\u043d\u0456\u043c \u043d\u0435\u0431\u0435.",
            "\u0414\u043e\u0431\u0440\u044b \u0441\u0441\u044f\u0431\u0440 \u0446\u044f\u0436\u043a\u0430 \u0437\u043d\u0430\u0439\u0441\u0446\u0456.",
            "\u041a\u043d\u0456\u0433\u0430 \u043b\u0430\u0436\u044b\u0446\u044c \u043d\u0430 \u0441\u0442\u0430\u043b\u0435 \u043f\u0430\u0440\u0430\u0434 \u043b\u044e\u0441\u0442\u0440\u0430\u043c."
        };
    case Language::Hebrew:
        return {
            "\u05d4\u05e9\u05de\u05e9 \u05d6\u05d5\u05e8\u05d7\u05ea \u05d1\u05e9\u05de\u05d9\u05d9\u05dd \u05d4\u05db\u05d7\u05d5\u05dc\u05d9\u05dd.",
            "\u05d7\u05d1\u05e8 \u05d8\u05d5\u05d1 \u05e7\u05e9\u05d4 \u05dc\u05de\u05e6\u05d5\u05d0.",
            "\u05d4\u05e1\u05e4\u05e8 \u05e0\u05de\u05e6\u05d0 \u05e2\u05dc \u05d4\u05e9\u05d5\u05dc\u05d7\u05df \u05dc\u05d9\u05d3 \u05d4\u05de\u05e0\u05d5\u05e8\u05d4."
        };
    }
    return {};
}

QList<QStringList> Trainer::keyboardLayout(Language lang)
{
    switch (lang) {
    case Language::German:
        return {
            {"^","1","2","3","4","5","6","7","8","9","0","ß","´","←"},
            {"Tab","q","w","e","r","t","z","u","i","o","p","ü","+","↵"},
            {"Caps","a","s","d","f","g","h","j","k","l","ö","ä","#","↵"},
            {"Shift","<","y","x","c","v","b","n","m",",",".","-","Shift"},
            {"Strg","","Alt","Space","AltGr","","Strg"}
        };
    case Language::French:
        return {
            {"²","&","é","\"","'","(","§","è","!","ç","à",")","=","←"},
            {"Tab","a","z","e","r","t","y","u","i","o","p","^","$","↵"},
            {"Caps","q","s","d","f","g","h","j","k","l","m","ù","*","↵"},
            {"Shift","<","w","x","c","v","b","n",",",";",":","!","Shift"},
            {"Ctrl","","Alt","Space","AltGr","","Ctrl"}
        };
    case Language::Arabic:
        return {
            {"ذ","1","2","3","4","5","6","7","8","9","0","-","=","←"},
            {"Tab","ض","ص","ث","ق","ف","غ","ع","ه","خ","ح","ج","د","↵"},
            {"Caps","ش","س","ي","ب","ل","ا","ت","ن","م","ك","ط","ذ","↵"},
            {"Shift","ئ","ء","ؤ","ر","لا","ى","ة","و","ز","ظ","Shift"},
            {"Ctrl","","Alt","Space","AltGr","","Ctrl"}
        };
    case Language::Chinese:
        return {
            {"`","1","2","3","4","5","6","7","8","9","0","-","=","←"},
            {"Tab","q","w","e","r","t","y","u","i","o","p","[","]","\\","↵"},
            {"Caps","a","s","d","f","g","h","j","k","l",";","'","↵"},
            {"Shift","z","x","c","v","b","n","m",",",".","/","Shift"},
            {"Ctrl","","Alt","Space","AltGr","","Ctrl"}
        };
    case Language::Belarusian:
        return {
            {"ё","1","2","3","4","5","6","7","8","9","0","-","=","←"},
            {"Tab","й","ц","у","к","е","н","г","ш","ў","з","х","'","↵"},
            {"Caps","ф","ы","в","а","п","р","о","л","д","ж","э","↵"},
            {"Shift","\\","я","ч","с","м","і","т","ь","б","ю",".","Shift"},
            {"Ctrl","","Alt","Space","AltGr","","Ctrl"}
        };
    case Language::Hebrew:
        return {
            {"`","1","2","3","4","5","6","7","8","9","0","-","=","←"},
            {"Tab","/","'","ק","ר","א","ט","ו","ן","ם","פ","[","]","↵"},
            {"Caps","ש","ד","ג","כ","ע","י","ח","ל","ך","ף",",","↵"},
            {"Shift","ז","ס","ב","ה","נ","מ","צ","ת","ץ",".","Shift"},
            {"Ctrl","","Alt","Space","AltGr","","Ctrl"}
        };
    }
    return {};
}