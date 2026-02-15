#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include "../car/car.h"

QT_BEGIN_NAMESPACE
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QGroupBox;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    Car* car;
    QTimer* timer;
    QLabel* drawArea;
    QLabel* statusLabel;

    // Кнопки управления
    QPushButton* moveLeftBtn;
    QPushButton* moveRightBtn;
    QPushButton* moveUpBtn;
    QPushButton* moveDownBtn;
    QPushButton* toggleDoorsBtn;
    QPushButton* toggleHeadlightsBtn;
    QPushButton* resetBtn;

    void setupUI();
    void updateDisplay();

private slots:
    void onMoveLeft();
    void onMoveRight();
    void onMoveUp();
    void onMoveDown();
    void onToggleDoors();
    void onToggleHeadlights();
    void onReset();
    void onTimerTimeout();

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
};

#endif // MAINWINDOW_H