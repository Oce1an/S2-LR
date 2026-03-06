#include "movingrect.h"

MovingRect::MovingRect(int startX, int startY, int w, int h)
    : x(startX), y(startY), width(w), height(h)
{
}

void MovingRect::moveLeft()
{
    x -= speed;
}

void MovingRect::moveRight()
{
    x += speed;
}

void MovingRect::moveUp()
{
    y -= speed;
}

void MovingRect::moveDown()
{
    y += speed;
}

void MovingRect::draw(QPainter& painter) const
{
    painter.drawRect(x, y, width, height);
}

void MovingRect::setPosition(int newX, int newY)
{
    x = newX;
    y = newY;
}