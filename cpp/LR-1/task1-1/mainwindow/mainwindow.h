#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "../car/car.h"
#include "../canvas/canvas.h"

class QPushButton;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Car car;
    Canvas* canvas;
    QTimer timer;

    QLabel* statusLabel;

    QPushButton* leftBtn;
    QPushButton* rightBtn;
    QPushButton* upBtn;
    QPushButton* downBtn;

    QPushButton* doorBtn;
    QPushButton* lightsBtn;
    QPushButton* resetBtn;

    void updateStatus();

private slots:
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void toggleDoors();
    void toggleLights();
    void reset();

public:
    explicit MainWindow(QWidget* parent = nullptr);
};

#endif