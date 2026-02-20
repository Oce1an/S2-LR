#ifndef CUSTOMSHAPE_H
#define CUSTOMSHAPE_H

#include "../shape/shape.h"

// Ёллипс - фигура, не основанна€ на предыдущих
class Ellipse : public Shape {
private:
    double radiusX;
    double radiusY;

public:
    Ellipse();
    Ellipse(const Point& center, double rx, double ry);

    double area() const override;
    double perimeter() const override;
    void draw(QPainter& painter) const override;
    bool containsPoint(const Point& p) const override;

    double getRadiusX() const { return radiusX; }
    double getRadiusY() const { return radiusY; }
    void setRadii(double rx, double ry);

    void setCenter(const Point& newCenter) override;
};

#endif // CUSTOMSHAPE_H