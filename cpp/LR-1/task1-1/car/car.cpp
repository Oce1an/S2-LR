#include "car.h"
#include <QPainter>

Car::Car(int x, int y)
    : MovingRect(x, y, 140, 70),
    doorsOpen(false),
    headlightsOn(false)
{
}

void Car::toggleDoors()
{
    doorsOpen = !doorsOpen;
}

void Car::toggleHeadlights()
{
    headlightsOn = !headlightsOn;
}


void Car::draw(QPainter& painter) const
{
    painter.setRenderHint(QPainter::Antialiasing);

    // Кузов
    painter.setBrush(Qt::gray);
    painter.setPen(Qt::black);
    painter.drawRect(x, y, width, height);

    // Крыша
    painter.drawRect(x, y - 18, 140, 20);

    // Колёса
    painter.setBrush(Qt::black);
    painter.drawEllipse(x + 13, y + height - 12, 24, 24);
    painter.drawEllipse(x + 58, y + height - 12, 24, 24);
    painter.drawEllipse(x + width - 37, y + height - 12, 24, 24);

    // Диски
    painter.setBrush(Qt::white);
    painter.drawEllipse(x + 19, y + height - 6, 12, 12);
    painter.drawEllipse(x + 64, y + height - 6, 12, 12);
    painter.drawEllipse(x + width - 31, y + height - 6, 12, 12);

    // Двери
    painter.setBrush(Qt::lightGray);

    if (doorsOpen)
    {
        painter.drawRect(x + 14, y + 15, 24, 38);
        painter.drawRect(x + width - 38, y + 15, 24, 38);
    }
    else
    {
        painter.drawRect(x + 22, y + 15, 24, 38);
        painter.drawRect(x + width - 46, y + 15, 24, 38);
    }

    // Фары
    if (headlightsOn)
        painter.setBrush(Qt::yellow);
    else
        painter.setBrush(Qt::darkGray);

    painter.drawRect(x - 6, y + 30, 12, 12);
    painter.drawRect(x + width - 6, y + 30, 12, 12);

    // Окна
    painter.setBrush(Qt::white);
    painter.setOpacity(0.8);

    painter.drawRect(x + 21, y - 14, 30, 12);
    painter.drawRect(x + 90, y - 14, 30, 12);

    painter.setOpacity(1.0);
}