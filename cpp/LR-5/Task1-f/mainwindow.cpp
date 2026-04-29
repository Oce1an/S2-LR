#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QFileDialog>
#include <QTextStream>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextCharFormat>
#include <QTextCursor>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_lang(Language::German)
    , m_started(false)
    , m_errorTimer(nullptr)
{
    qDebug() << "Constructor start";
    ui->setupUi(this);
    qDebug() << "setupUi done";
    
    setWindowTitle("Клавиатурный тренажёр");

    ui->langCombo->addItem(Trainer::languageName(Language::German));
    ui->langCombo->addItem(Trainer::languageName(Language::French));
    ui->langCombo->addItem(Trainer::languageName(Language::Arabic));
    ui->langCombo->addItem(Trainer::languageName(Language::Chinese));
    ui->langCombo->addItem(Trainer::languageName(Language::Belarusian));
    ui->langCombo->addItem(Trainer::languageName(Language::Hebrew));
    qDebug() << "Combo items added";

    connect(&m_timer, &QTimer::timeout, this, &MainWindow::onTimerTick);
    m_timer.setInterval(100);
    qDebug() << "Timer setup done";

    m_errorTimer = new QTimer(this);
    m_errorTimer->setSingleShot(true);
    m_errorTimer->setInterval(300);
    connect(m_errorTimer, &QTimer::timeout, this, [this]() {
        m_trainer.clearLastError();
        refreshTextDisplay();
    });
    qDebug() << "Error timer setup done";

    qDebug() << "Calling applyLanguage";
    applyLanguage(m_lang);
    qDebug() << "Constructor end";
}

MainWindow::~MainWindow()
{
    qDebug() << "Destructor";
    delete ui;
}

void MainWindow::applyLanguage(Language lang)
{
    qDebug() << "applyLanguage start" << (int)lang;
    m_lang = lang;
    QStringList samples = Trainer::sampleText(lang);
    QString text = samples.isEmpty() ? "Test" : samples.join(" ");
    qDebug() << "Sample text:" << text;

    bool rtl = (lang == Language::Arabic || lang == Language::Hebrew);
    ui->textEdit->setLayoutDirection(rtl ? Qt::RightToLeft : Qt::LeftToRight);
    qDebug() << "Text direction set";

    m_trainer.setText(text);
    qDebug() << "Trainer text set";
    
    resetState();
    qDebug() << "State reset";
    
    refreshTextDisplay();
    qDebug() << "Text display refreshed";
    
    buildKeyboard();
    qDebug() << "Keyboard built";
    
    setFocus();
    qDebug() << "applyLanguage end";
}

void MainWindow::resetState()
{
    m_started = false;
    m_timer.stop();
    if (m_errorTimer) m_errorTimer->stop();
    ui->timerLabel->setText("00:00.0");
    ui->wpmLabel->setText("0");
    ui->accuracyLabel->setText("100.0%");
}

void MainWindow::refreshTextDisplay()
{
    qDebug() << "refreshTextDisplay start";
    
    if (!ui->textEdit) {
        qDebug() << "textEdit is null!";
        return;
    }
    
    const QString &text = m_trainer.text();
    int pos = m_trainer.position();
    const auto &results = m_trainer.results();
    bool hasError = m_trainer.hasLastError();

    qDebug() << "Text length:" << text.length() << "Position:" << pos;

    ui->textEdit->clear();
    QTextCursor cursor(ui->textEdit->document());

    for (int i = 0; i < text.length(); ++i) {
        QTextCharFormat fmt;

        if (i < pos) {
            bool correct = (i < results.size()) ? results[i].correct : true;
            fmt.setForeground(correct ? QColor(0, 140, 0) : QColor(200, 0, 0));
            fmt.setBackground(Qt::transparent);
        } else if (i == pos) {
            if (hasError) {
                fmt.setBackground(QColor(255, 180, 180));
                fmt.setForeground(QColor(200, 0, 0));
            } else {
                fmt.setBackground(QColor(180, 200, 255));
                fmt.setForeground(Qt::black);
            }
        } else {
            fmt.setForeground(QColor(80, 80, 80));
            fmt.setBackground(Qt::transparent);
        }

        cursor.insertText(QString(text[i]), fmt);
    }
    qDebug() << "refreshTextDisplay end";
}

void MainWindow::buildKeyboard()
{
    qDebug() << "buildKeyboard start";
    
    QWidget *kbWidget = ui->keyboardWidget;
    if (!kbWidget) {
        qDebug() << "keyboardWidget is null!";
        return;
    }
    
    qDebug() << "keyboardWidget OK";
    
    // Удаляем старый layout
    QLayout *oldLayout = kbWidget->layout();
    if (oldLayout) {
        qDebug() << "Removing old layout";
        QLayoutItem *item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            if (QWidget *w = item->widget()) {
                w->setParent(nullptr);
                w->deleteLater();
            }
            delete item;
        }
        delete oldLayout;
    }

    qDebug() << "Creating new layout";
    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->setSpacing(4);
    vbox->setContentsMargins(2, 2, 2, 2);

    QList<QStringList> rows = Trainer::keyboardLayout(m_lang);
    qDebug() << "Got" << rows.size() << "keyboard rows";
    
    for (int rowIdx = 0; rowIdx < rows.size(); ++rowIdx) {
        const QStringList &row = rows[rowIdx];
        qDebug() << "Processing row" << rowIdx << "with" << row.size() << "keys";
        
        QHBoxLayout *hbox = new QHBoxLayout();
        hbox->setSpacing(3);
        
        for (int keyIdx = 0; keyIdx < row.size(); ++keyIdx) {
            const QString &key = row[keyIdx];
            
            if (key.isEmpty()) {
                hbox->addSpacing(10);
                continue;
            }
            
            QPushButton *btn = new QPushButton(key);
            int w = (key.contains("Space")) ? 150
                  : (key.length() > 2)      ? 55 : 36;
            btn->setFixedSize(w, 34);
            btn->setFocusPolicy(Qt::NoFocus);
            btn->setStyleSheet(
                "QPushButton {"
                "  font-size:11px;"
                "  border-radius:4px;"
                "  background:#e0e0e0;"
                "  border:1px solid #999;"
                "  padding:2px;"
                "}"
            );
            hbox->addWidget(btn);
        }
        
        hbox->addStretch();
        vbox->addLayout(hbox);
    }
    
    vbox->addStretch();
    kbWidget->setLayout(vbox);
    qDebug() << "buildKeyboard end";
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (!event) {
        QMainWindow::keyPressEvent(event);
        return;
    }
    
    // Игнорируем модификаторы
    if (event->key() == Qt::Key_Shift || 
        event->key() == Qt::Key_Control ||
        event->key() == Qt::Key_Alt ||
        event->key() == Qt::Key_Meta) {
        QMainWindow::keyPressEvent(event);
        return;
    }

    QString text = event->text();
    if (text.isEmpty()) {
        QMainWindow::keyPressEvent(event);
        return;
    }

    QChar ch = text.at(0);
    
    // Фильтруем непечатные символы
    if (!ch.isPrint() && ch != ' ') {
        QMainWindow::keyPressEvent(event);
        return;
    }
    
    if (!m_started && !m_trainer.finished()) {
        m_started = true;
        m_elapsed.restart();
        m_timer.start();
    }

    bool correct = m_trainer.typeChar(ch);
    refreshTextDisplay();
    updateStats();

    if (!correct && !m_trainer.finished()) {
        if (m_errorTimer) {
            m_errorTimer->start();
        }
    }

    if (m_trainer.finished()) {
        m_timer.stop();
        updateStats();
    }
}

void MainWindow::onTimerTick()
{
    if (!m_started) return;
    
    qint64 ms = m_elapsed.elapsed();
    int totalSec = ms / 1000;
    int min = totalSec / 60;
    int sec = totalSec % 60;
    int tenth = (ms % 1000) / 100;
    ui->timerLabel->setText(QString("%1:%2.%3")
        .arg(min,  2, 10, QChar('0'))
        .arg(sec,  2, 10, QChar('0'))
        .arg(tenth));
    updateStats();
}

void MainWindow::updateStats()
{
    qint64 ms = m_started ? m_elapsed.elapsed() : 0;
    double wpm = m_trainer.wordsPerMinute(ms);
    ui->wpmLabel->setText(QString::number(wpm, 'f', 1));
    double acc = m_trainer.accuracy();
    ui->accuracyLabel->setText(QString::number(acc, 'f', 1) + "%");
}

void MainWindow::on_langCombo_currentIndexChanged(int index)
{
    if (index >= 0 && index <= 5) {
        applyLanguage(static_cast<Language>(index));
    }
}

void MainWindow::on_openFileButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Открыть файл", "",
                                                "Text files (*.txt);;All files (*)");
    if (path.isEmpty()) return;
    
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    
    QTextStream in(&f);
    in.setEncoding(QStringConverter::Utf8);
    QString content = in.readAll().simplified();
    
    if (content.isEmpty()) {
        content = "Empty file";
    }
    
    m_trainer.setText(content);
    resetState();
    refreshTextDisplay();
    setFocus();
}

void MainWindow::on_restartButton_clicked()
{
    m_trainer.reset();
    resetState();
    refreshTextDisplay();
    setFocus();
}