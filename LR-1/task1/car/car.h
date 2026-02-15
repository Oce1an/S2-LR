#ifndef CAR_H
#define CAR_H

#include "../movingrect/movingrect.h"

class Car : public MovingRect {
private:
    bool doorsOpen;     // Состояние дверей
    bool headlightsOn;  // Состояние фар

public:
    Car();
    Car(int startX, int startY);

    // Переопределение метода отрисовки
    void draw(QPainter& painter) override;

    // Новые методы для управления автомобилем
    void toggleDoors();
    void toggleHeadlights();
    void openDoors();
    void closeDoors();
    void turnHeadlightsOn();
    void turnHeadlightsOff();

    // Геттеры для состояний
    bool areDoorsOpen() const { return doorsOpen; }
    bool areHeadlightsOn() const { return headlightsOn; }
};

#endif // CAR_H