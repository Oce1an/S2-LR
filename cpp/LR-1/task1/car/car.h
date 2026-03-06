#ifndef CAR_H
#define CAR_H

#include "../movingrect/movingrect.h"

class Car : public MovingRect
{
public:
    static constexpr int WIDTH = 120;
    static constexpr int HEIGHT = 60;

private:
    bool doorsOpen{ false };
    bool headlightsOn{ false };

public:
    Car();
    Car(int x, int y);

    void draw(QPainter& painter) const override;

    void toggleDoors();
    void toggleHeadlights();

    void openDoors() { doorsOpen = true; }
    void closeDoors() { doorsOpen = false; }

    void turnHeadlightsOn() { headlightsOn = true; }
    void turnHeadlightsOff() { headlightsOn = false; }

    bool areDoorsOpen() const { return doorsOpen; }
    bool areHeadlightsOn() const { return headlightsOn; }
};

#endif