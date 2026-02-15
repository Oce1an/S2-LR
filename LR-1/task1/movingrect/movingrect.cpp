#include "../movingrect/movingrect.h"

MovingRect::MovingRect() : x(0), y(0), width(50), height(30), speed(5) {}

MovingRect::MovingRect(int startX, int startY, int w, int h)
    : x(startX), y(startY), width(w), height(h), speed(5) {
}

MovingRect::~MovingRect() {}

void MovingRect::moveLeft() {
    x -= speed;
}

void MovingRect::moveRight() {
    x += speed;
}

void MovingRect::moveUp() {
    y -= speed;
}

void MovingRect::moveDown() {
    y += speed;
}

void MovingRect::draw(QPainter& painter) {
    painter.drawRect(x, y, width, height);
}

void MovingRect::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}