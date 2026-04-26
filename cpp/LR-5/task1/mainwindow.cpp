#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QEvent>
#include <QKeyEvent>
#include <QInputMethodEvent>
#include <QApplication>
#include <QStringConverter>   // для setEncoding в Qt6

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_model = new TrainerModel(this);
    m_languages = languageData();

    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    // Верхняя панель
    QHBoxLayout *topLayout = new QHBoxLayout();

    m_langCombo = new QComboBox(this);
    for (auto it = m_languages.constBegin(); it != m_languages.constEnd(); ++it)
        m_langCombo->addItem(it.value().name, it.key());
    m_langCombo->setCurrentIndex(0);
    connect(m_langCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onLanguageChanged);

    m_btnLoad = new QPushButton("Загрузить файл", this);
    connect(m_btnLoad, &QPushButton::clicked, this, &MainWindow::onLoadFile);

    m_btnStartStop = new QPushButton("Старт", this);
    m_btnStartStop->setCheckable(true);
    connect(m_btnStartStop, &QPushButton::clicked, this, &MainWindow::onStartStop);

    m_timerLabel = new QLabel("00:00", this);
    m_timerLabel->setStyleSheet("font-size: 16px; font-weight: bold;");
    m_wpmLabel = new QLabel("0 WPM", this);
    m_wpmLabel->setStyleSheet("font-size: 16px; font-weight: bold;");

    topLayout->addWidget(m_langCombo);
    topLayout->addWidget(m_btnLoad);
    topLayout->addWidget(m_btnStartStop);
    topLayout->addStretch();
    topLayout->addWidget(new QLabel("Время:", this));
    topLayout->addWidget(m_timerLabel);
    topLayout->addWidget(new QLabel("Скорость:", this));
    topLayout->addWidget(m_wpmLabel);
    mainLayout->addLayout(topLayout);

    // Отображение текста
    m_textDisplay = new TextDisplay(m_model, this);
    mainLayout->addWidget(m_textDisplay, 1);

    // Виртуальная клавиатура
    m_keyboard = new KeyboardWidget(this);
    mainLayout->addWidget(m_keyboard);

    // Скрытое поле для перехвата IME (китайский и т.п.)
    m_inputLine = new QLineEdit(this);
    m_inputLine->setMaximumSize(0, 0);
    m_inputLine->setStyleSheet("border: none; background: transparent;");
    m_inputLine->installEventFilter(this);
    m_inputLine->setFocus();   // без фокуса IME не работает

    // Таймер обновления статистики
    m_statTimer = new QTimer(this);
    m_statTimer->setInterval(200);
    connect(m_statTimer, &QTimer::timeout, this, &MainWindow::updateStats);

    onLanguageChanged(0);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (obj == m_inputLine && event->type() == QEvent::InputMethod) {
        QInputMethodEvent *ime = static_cast<QInputMethodEvent*>(event);
        if (!ime->commitString().isEmpty()) {
            const QString text = ime->commitString();
            m_inputLine->clear();
            if (m_model->isActive()) {
                if (text == " ") {
                    m_model->finishCurrentWord();
                } else {
                    m_model->processCharacter(text);
                }
                m_textDisplay->update();
                if (text.length() == 1)
                    m_keyboard->highlightKey(text);
            }
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

// Обработка обычных нажатий клавиш (включая пробел)
void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (!m_model->isActive()) {
        QMainWindow::keyPressEvent(event);
        return;
    }

    const QString text = event->text();
    if (text.isEmpty()) {
        QMainWindow::keyPressEvent(event);
        return;
    }

    // Пробел завершает слово, остальные символы обрабатываются моделью
    if (text == " ") {
        m_model->finishCurrentWord();
    } else {
        m_model->processCharacter(text);
    }

    m_textDisplay->update();
    if (text.length() == 1)
        m_keyboard->highlightKey(text);

    // Не вызываем QMainWindow::keyPressEvent, чтобы избежать дублирования
}

void MainWindow::onLanguageChanged(int index) {
    QString code = m_langCombo->itemData(index).toString();
    applyLanguage(code);
}

void MainWindow::applyLanguage(const QString &langCode) {
    m_currentLangCode = langCode;
    if (!m_languages.contains(langCode)) return;

    const LanguageInfo &info = m_languages[langCode];
    m_keyboard->setKeyRows(info.keyRows);

    // Направление письма
    if (langCode == "ar" || langCode == "he") {
        QApplication::setLayoutDirection(Qt::RightToLeft);
    } else {
        QApplication::setLayoutDirection(Qt::LeftToRight);
    }

    setSampleText(info.sampleText);
    m_model->reset();
    m_textDisplay->update();
}

void MainWindow::onLoadFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть текстовый файл",
                                                    QString(), "Текст (*.txt);;Все (*)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не могу открыть файл");
        return;
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);   // Qt6
    QString content = in.readAll();
    file.close();

    setSampleText(content);
    m_model->reset();
    m_textDisplay->update();
}

void MainWindow::onStartStop() {
    if (m_model->isActive()) {
        m_model->stop();
        m_btnStartStop->setText("Старт");
        m_statTimer->stop();
    } else {
        if (m_model->words().isEmpty()) return;
        m_model->start();
        m_btnStartStop->setText("Стоп");
        m_statTimer->start();
        m_inputLine->clear();
        m_inputLine->setFocus();  // фокус для IME
    }
}

void MainWindow::updateStats() {
    if (!m_model->isActive()) return;
    int secs = m_model->elapsedSeconds();
    QTime t = QTime(0, 0).addSecs(secs);
    m_timerLabel->setText(t.toString("mm:ss"));
    m_wpmLabel->setText(QString::number(m_model->wordsPerMinute()) + " WPM");
}

void MainWindow::setSampleText(const QString &text) {
    m_model->setText(text);
}