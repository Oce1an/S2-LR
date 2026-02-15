#include "../mainwindow/mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPainter>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    try {
        car = new Car(200, 200);
        timer = new QTimer(this);
        setupUI();

        // Подключение сигналов и слотов
        connect(moveLeftBtn, &QPushButton::clicked, this, &MainWindow::onMoveLeft);
        connect(moveRightBtn, &QPushButton::clicked, this, &MainWindow::onMoveRight);
        connect(moveUpBtn, &QPushButton::clicked, this, &MainWindow::onMoveUp);
        connect(moveDownBtn, &QPushButton::clicked, this, &MainWindow::onMoveDown);
        connect(toggleDoorsBtn, &QPushButton::clicked, this, &MainWindow::onToggleDoors);
        connect(toggleHeadlightsBtn, &QPushButton::clicked, this, &MainWindow::onToggleHeadlights);
        connect(resetBtn, &QPushButton::clicked, this, &MainWindow::onReset);
        connect(timer, &QTimer::timeout, this, &MainWindow::onTimerTimeout);

        timer->start(50); // Обновление 20 раз в секунду
        updateDisplay();
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Error",
            QString("Failed to initialize application: %1").arg(e.what()));
    }
}

MainWindow::~MainWindow() {
    delete car;
}

void MainWindow::setupUI() {
    setWindowTitle("Car Control");
    setMinimumSize(800, 600);

    // Создание центрального виджета
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Основной вертикальный layout
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // Область рисования
    drawArea = new QLabel();
    drawArea->setMinimumSize(600, 400);
    drawArea->setStyleSheet("border: 2px solid gray; background-color: white;");
    drawArea->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(drawArea);

    // Группа для кнопок управления
    QGroupBox* controlGroup = new QGroupBox("Car Control");
    QVBoxLayout* controlLayout = new QVBoxLayout(controlGroup);

    // Кнопки перемещения
    QGroupBox* moveGroup = new QGroupBox("Movement");
    QGridLayout* moveLayout = new QGridLayout(moveGroup);

    moveUpBtn = new QPushButton("↑ Up");
    moveLeftBtn = new QPushButton("← Left");
    moveRightBtn = new QPushButton("→ Right");
    moveDownBtn = new QPushButton("↓ Down");

    moveLayout->addWidget(moveUpBtn, 0, 1);
    moveLayout->addWidget(moveLeftBtn, 1, 0);
    moveLayout->addWidget(moveRightBtn, 1, 2);
    moveLayout->addWidget(moveDownBtn, 2, 1);

    controlLayout->addWidget(moveGroup);

    // Кнопки управления дверями и фарами
    QHBoxLayout* featureLayout = new QHBoxLayout();
    toggleDoorsBtn = new QPushButton("Open/Close Doors");
    toggleHeadlightsBtn = new QPushButton("Turn On/Off Headlights");
    resetBtn = new QPushButton("Reset Position");

    featureLayout->addWidget(toggleDoorsBtn);
    featureLayout->addWidget(toggleHeadlightsBtn);
    featureLayout->addWidget(resetBtn);

    controlLayout->addLayout(featureLayout);

    // Статусная строка
    statusLabel = new QLabel("Status: Doors closed, Headlights off");
    statusLabel->setStyleSheet("font-weight: bold; color: blue;");
    controlLayout->addWidget(statusLabel);

    mainLayout->addWidget(controlGroup);

    // Установка стилей для кнопок
    QString buttonStyle = "QPushButton { padding: 8px; font-size: 14px; }";
    moveUpBtn->setStyleSheet(buttonStyle);
    moveLeftBtn->setStyleSheet(buttonStyle);
    moveRightBtn->setStyleSheet(buttonStyle);
    moveDownBtn->setStyleSheet(buttonStyle);
    toggleDoorsBtn->setStyleSheet(buttonStyle);
    toggleHeadlightsBtn->setStyleSheet(buttonStyle);
    resetBtn->setStyleSheet(buttonStyle);
}

void MainWindow::updateDisplay() {
    try {
        // Создание изображения для рисования
        QPixmap pixmap(drawArea->size());
        pixmap.fill(Qt::white);

        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);

        // Рисование автомобиля
        car->draw(painter);

        // Обновление QLabel
        drawArea->setPixmap(pixmap);

        // Обновление статуса
        QString status = "Status: ";
        status += car->areDoorsOpen() ? "Doors open, " : "Doors closed, ";
        status += car->areHeadlightsOn() ? "Headlights on" : "Headlights off";
        statusLabel->setText(status);
    }
    catch (const std::exception& e) {
        qDebug() << "Error updating display:" << e.what();
    }
}

void MainWindow::onMoveLeft() {
    try {
        car->moveLeft();
        // Проверка выхода за границы
        if (car->getX() < 0) {
            car->setPosition(0, car->getY());
            QMessageBox::information(this, "Warning",
                "Reached left border!");
        }
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Error",
            QString("Movement error: %1").arg(e.what()));
    }
}

void MainWindow::onMoveRight() {
    try {
        car->moveRight();
        // Проверка выхода за границы
        if (car->getX() > drawArea->width() - 120) {
            car->setPosition(drawArea->width() - 120, car->getY());
            QMessageBox::information(this, "Warning",
                "Reached right border!");
        }
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Error",
            QString("Movement error: %1").arg(e.what()));
    }
}

void MainWindow::onMoveUp() {
    try {
        car->moveUp();
        // Проверка выхода за границы
        if (car->getY() < 0) {
            car->setPosition(car->getX(), 0);
            QMessageBox::information(this, "Warning",
                "Reached top border!");
        }
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Error",
            QString("Movement error: %1").arg(e.what()));
    }
}

void MainWindow::onMoveDown() {
    try {
        car->moveDown();
        // Проверка выхода за границы
        if (car->getY() > drawArea->height() - 80) {
            car->setPosition(car->getX(), drawArea->height() - 80);
            QMessageBox::information(this, "Warning",
                "Reached bottom border!");
        }
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Error",
            QString("Movement error: %1").arg(e.what()));
    }
}

void MainWindow::onToggleDoors() {
    try {
        car->toggleDoors();
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Error",
            QString("Doors toggle error: %1").arg(e.what()));
    }
}

void MainWindow::onToggleHeadlights() {
    try {
        car->toggleHeadlights();
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Error",
            QString("Headlights toggle error: %1").arg(e.what()));
    }
}

void MainWindow::onReset() {
    try {
        car->setPosition(200, 200);
        car->closeDoors();
        car->turnHeadlightsOff();
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Error",
            QString("Reset error: %1").arg(e.what()));
    }
}

void MainWindow::onTimerTimeout() {
    updateDisplay();
}