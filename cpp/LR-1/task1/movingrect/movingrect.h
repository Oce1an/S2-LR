#ifndef MOVINGRECT_H
#define MOVINGRECT_H

#include <QPainter>
#include <QPoint>

class MovingRect {
protected:
    int x, y;           // Позиция
    int width, height;  // Размеры
    int speed;          // Скорость перемещения

public:
    MovingRect();
    MovingRect(int startX, int startY, int w, int h);
    virtual ~MovingRect();

    // Методы для перемещения
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    // Метод для отрисовки (виртуальный для переопределения)
    virtual void draw(QPainter& painter);

    // Геттеры и сеттеры
    int getX() const { return x; }
    int getY() const { return y; }
    void setPosition(int newX, int newY);
    void setSpeed(int newSpeed) { speed = newSpeed; }
};

#endif // MOVINGRECT_H