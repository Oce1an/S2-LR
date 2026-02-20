#ifndef HEXAGON_H
#define HEXAGON_H

#include "../polygon/polygon.h"

class Hexagon : public Polygon {
private:
    double radius;  // Радиус описанной окружности

public:
    Hexagon();
    Hexagon(const Point& center, double r);

    double area() const override;
    double perimeter() const override;

    double getRadius() const { return radius; }
    void setRadius(double r);

    void setCenter(const Point& newCenter) override;

private:
    void updateVertices();
};

#endif // HEXAGON_H