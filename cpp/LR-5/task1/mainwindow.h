#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTimer>
#include <QKeyEvent>               // <-- добавлено
#include "trainermodel.h"
#include "textdisplay.h"
#include "keyboardwidget.h"
#include "languagedata.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

protected:
    void keyPressEvent(QKeyEvent *event) override;   // <-- добавлено
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void onLanguageChanged(int index);
    void onLoadFile();
    void onStartStop();
    void updateStats();

private:
    void applyLanguage(const QString &langCode);
    void setSampleText(const QString &text);

    TrainerModel *m_model;
    TextDisplay *m_textDisplay;
    KeyboardWidget *m_keyboard;

    QComboBox *m_langCombo;
    QLabel *m_timerLabel;
    QLabel *m_wpmLabel;
    QPushButton *m_btnLoad;
    QPushButton *m_btnStartStop;
    QLineEdit *m_inputLine;      // скрытое поле для захвата IME

    QTimer *m_statTimer;
    QMap<QString, LanguageInfo> m_languages;
    QString m_currentLangCode;
};

#endif // MAINWINDOW_H