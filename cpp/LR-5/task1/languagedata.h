//----------------------- languagedata.h -----------------------
#ifndef LANGUAGEDATA_H
#define LANGUAGEDATA_H

#include <QString>
#include <QStringList>
#include <QMap>
#include <QVector>

struct LanguageInfo {
    QString name;           // отображаемое имя (рус.)
    QString locale;         // код языка (для Qt)
    QStringList keyRows;    // 3 строки символов виртуальной клавиатуры
    QString sampleText;     // текст для тренировки по умолчанию
};

// Данные для шести языков
inline QMap<QString, LanguageInfo> languageData() {
    QMap<QString, LanguageInfo> map;

    // Немецкий
    map["de"] = { "Немецкий", "de_DE",
                  {"^ 1 2 3 4 5 6 7 8 9 0 ß ´",    // добавлены пробелы для наглядности
                   "q w e r t z u i o p ü +",
                   "a s d f g h j k l ö ä #",
                   "< y x c v b n m , . -"},
                  "Über den grünen Wiesen fliegen bunte Schmetterlinge. Der Fuchs jagt den Hasen." };

    // Французский
    map["fr"] = { "Французский", "fr_FR",
                  {"& é \" ' ( - è _ ç à ) =",
                   "a z e r t y u i o p ^ $",
                   "q s d f g h j k l m ù *",
                   "< w x c v b n , ; : !"},
                  "Les enfants jouent dans le jardin pendant que le chien dort. La vie est belle à Paris."
                };

    // Арабский (раскладка для IBM арабская 102; символы в логическом порядке)
    map["ar"] = { "Арабский", "ar_SA",
                  {"ذ 1 2 3 4 5 6 7 8 9 0 - =",
                   "ض ص ث ق ف غ ع ه خ ح ج د",
                   "ش س ي ب ل ا ت ن م ك ط",
                   "ئ ء ؤ ر ﻻ ى ة و ز ظ"},
                  "السلام عليكم ورحمة الله وبركاته. هذه جملة تجريبية للتدريب على لوحة المفاتيح."
                };

    // Китайский (символы стандартной QWERTY с иероглифами в тексте; клавиши показывают пиньинь/англ.)
    map["zh"] = { "Китайский", "zh_CN",
                  {"` 1 2 3 4 5 6 7 8 9 0 - =",
                   "q w e r t y u i o p [ ]",
                   "a s d f g h j k l ; '",
                   "z x c v b n m , . /"},
                  "你好世界，这是一段中文测试文本。欢迎大家使用键盘练习软件。学习中文很有趣。"
                };

    // Белорусский (кириллица)
    map["be"] = { "Белорусский", "be_BY",
                  {"ё 1 2 3 4 5 6 7 8 9 0 - =",
                   "й ц у к е н г ш ў з х '",
                   "ф ы в а п р о л д ж э",
                   "я ч с м і т ь б ю ."},
                  "Беларуская мова – адна з найпрыгажэйшых моў. У лесе спяваюць птушкі, квітнеюць кветкі."
                };

    // Иврит
    map["he"] = { "Иврит", "he_IL",
                  {"` 1 2 3 4 5 6 7 8 9 0 - =",
                   "/ ' ק ר א ט ו ן ם פ ] [",
                   "ש ד ג כ ע י ח ל ך ף ,",
                   "ז ס ב ה נ מ צ ת ץ ."},
                  "שלום עולם, זהו משפט לדוגמה לאימון הקלדה בעברית. הכלב רץ בגינה."
                };

    return map;
}

#endif // LANGUAGEDATA_H