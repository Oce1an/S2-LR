#ifndef MOVINGRECT_H
#define MOVINGRECT_H

#include <QPainter>

class MovingRect
{
protected:
    int x{};
    int y{};
    int width{};
    int height{};
    int speed{ 5 };

public:
    MovingRect() = default;
    MovingRect(int startX, int startY, int w, int h);

    virtual ~MovingRect() = default;

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    virtual void draw(QPainter& painter) const;

    int getX() const { return x; }
    int getY() const { return y; }

    void setPosition(int newX, int newY);

    void setSpeed(int newSpeed) { speed = newSpeed; }
};

#endif