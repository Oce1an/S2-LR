#include "canvas.h"
#include <QPainter>

Canvas::Canvas(Car* car, QWidget* parent)
    : QWidget(parent), car(car)
{
    setMinimumSize(600, 400);
}

void Canvas::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);

    if (car)
        car->draw(painter);
}