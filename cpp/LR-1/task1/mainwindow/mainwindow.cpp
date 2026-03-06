#include "mainwindow.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), car(200, 200)
{
    QWidget* central = new QWidget;
    setCentralWidget(central);

    QVBoxLayout* mainLayout = new QVBoxLayout(central);

    canvas = new Canvas(&car);
    mainLayout->addWidget(canvas);

    QGridLayout* moveLayout = new QGridLayout;

    upBtn = new QPushButton("UP");
    leftBtn = new QPushButton("LEFT");
    rightBtn = new QPushButton("RIGHT");
    downBtn = new QPushButton("DOWN");

    moveLayout->addWidget(upBtn, 0, 1);
    moveLayout->addWidget(leftBtn, 1, 0);
    moveLayout->addWidget(rightBtn, 1, 2);
    moveLayout->addWidget(downBtn, 2, 1);

    mainLayout->addLayout(moveLayout);

    doorBtn = new QPushButton("Toggle Doors");
    lightsBtn = new QPushButton("Toggle Lights");
    resetBtn = new QPushButton("Reset Position");

    mainLayout->addWidget(doorBtn);
    mainLayout->addWidget(lightsBtn);
    mainLayout->addWidget(resetBtn);

    statusLabel = new QLabel;
    mainLayout->addWidget(statusLabel);

    connect(leftBtn, &QPushButton::clicked, this, &MainWindow::moveLeft);
    connect(rightBtn, &QPushButton::clicked, this, &MainWindow::moveRight);
    connect(upBtn, &QPushButton::clicked, this, &MainWindow::moveUp);
    connect(downBtn, &QPushButton::clicked, this, &MainWindow::moveDown);

    connect(doorBtn, &QPushButton::clicked, this, &MainWindow::toggleDoors);
    connect(lightsBtn, &QPushButton::clicked, this, &MainWindow::toggleLights);
    connect(resetBtn, &QPushButton::clicked, this, &MainWindow::reset);

    // исправленный connect
    connect(&timer, &QTimer::timeout, this, [this]() {
        canvas->update();
        });

    timer.start(16);

    updateStatus();
}

void MainWindow::updateStatus()
{
    QString status = "Doors: ";
    status += car.areDoorsOpen() ? "Open" : "Closed";
    status += " | Lights: ";
    status += car.areHeadlightsOn() ? "On" : "Off";

    statusLabel->setText(status);
}

void MainWindow::moveLeft()
{
    car.moveLeft();
    canvas->update();
    updateStatus();
}

void MainWindow::moveRight()
{
    car.moveRight();
    canvas->update();
    updateStatus();
}

void MainWindow::moveUp()
{
    car.moveUp();
    canvas->update();
    updateStatus();
}

void MainWindow::moveDown()
{
    car.moveDown();
    canvas->update();
    updateStatus();
}

void MainWindow::toggleDoors()
{
    car.toggleDoors();
    canvas->update();
    updateStatus();
}

void MainWindow::toggleLights()
{
    car.toggleHeadlights();
    canvas->update();
    updateStatus();
}

void MainWindow::reset()
{
    car.setPosition(200, 200);
    car.closeDoors();
    car.turnHeadlightsOff();

    canvas->update();
    updateStatus();
}