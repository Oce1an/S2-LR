#include "../car/car.h"

Car::Car() : MovingRect(100, 100, 120, 60), doorsOpen(false), headlightsOn(false) {}

Car::Car(int startX, int startY) : MovingRect(startX, startY, 120, 60),
doorsOpen(false), headlightsOn(false) {
}

void Car::draw(QPainter& painter) {
    // Сохраняем текущие настройки пера и кисти
    QPen pen = painter.pen();
    QBrush brush = painter.brush();

    // Рисуем кузов автомобиля (основной прямоугольник)
    painter.setBrush(Qt::blue);
    painter.setPen(Qt::black);
    painter.drawRect(x, y, width, height);

    // Рисуем крышу
    painter.drawRect(x + 30, y - 20, 60, 20);

    // Рисуем колеса
    painter.setBrush(Qt::black);
    painter.drawEllipse(x + 15, y + 45, 20, 20);
    painter.drawEllipse(x + 85, y + 45, 20, 20);

    // Рисуем диски колес
    painter.setBrush(Qt::gray);
    painter.drawEllipse(x + 20, y + 50, 10, 10);
    painter.drawEllipse(x + 90, y + 50, 10, 10);

    // Рисуем двери (открываются или закрыты)
    painter.setBrush(doorsOpen ? Qt::white : Qt::lightGray);
    painter.setPen(Qt::darkGray);

    if (doorsOpen) {
        // Открытые двери (рисуем под углом)
        painter.drawRect(x + 20, y + 10, 20, 40);  // Левая дверь
        painter.drawRect(x + 70, y + 10, 20, 40);  // Правая дверь
    }
    else {
        // Закрытые двери
        painter.drawRect(x + 20, y + 10, 20, 40);  // Левая дверь
        painter.drawRect(x + 70, y + 10, 20, 40);  // Правая дверь
        // Ручки дверей
        painter.setBrush(Qt::black);
        painter.drawRect(x + 35, y + 30, 5, 5);
        painter.drawRect(x + 85, y + 30, 5, 5);
    }

    // Рисуем фары (включены или выключены)
    if (headlightsOn) {
        painter.setBrush(Qt::yellow);
        painter.setPen(Qt::yellow);
        // Свет фар
        painter.setOpacity(0.3);
        painter.drawEllipse(x - 15, y + 15, 25, 20);
        painter.setOpacity(1.0);

        // Включенные фары
        painter.setBrush(Qt::yellow);
        painter.setPen(Qt::black);
    }
    else {
        // Выключенные фары
        painter.setBrush(Qt::gray);
        painter.setPen(Qt::black);
    }

    // Рисуем фары
    painter.drawEllipse(x - 5, y + 15, 10, 10);
    painter.drawEllipse(x + width - 5, y + 15, 10, 10);

    // Окна
    painter.setBrush(Qt::lightGray);
    painter.setOpacity(0.7);
    painter.drawRect(x + 40, y - 15, 15, 10);
    painter.drawRect(x + 65, y - 15, 15, 10);
    painter.setOpacity(1.0);

    // Восстанавливаем настройки
    painter.setBrush(brush);
    painter.setPen(pen);
}

void Car::toggleDoors() {
    doorsOpen = !doorsOpen;
}

void Car::toggleHeadlights() {
    headlightsOn = !headlightsOn;
}

void Car::openDoors() {
    doorsOpen = true;
}

void Car::closeDoors() {
    doorsOpen = false;
}

void Car::turnHeadlightsOn() {
    headlightsOn = true;
}

void Car::turnHeadlightsOff() {
    headlightsOn = false;
}