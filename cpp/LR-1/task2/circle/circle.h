#ifndef CIRCLE_H
#define CIRCLE_H

#include "../shape/shape.h"

class Circle : public Shape {
private:
    double radius;

public:
    Circle();
    Circle(const Point& center, double r);

    // Переопределение виртуальных методов
    double area() const override;
    double perimeter() const override;
    void draw(QPainter& painter) const override;
    bool containsPoint(const Point& p) const override;

    // Специфические методы
    double getRadius() const { return radius; }
    void setRadius(double r);

    void setCenter(const Point& newCenter) override;
};

#endif // CIRCLE_H