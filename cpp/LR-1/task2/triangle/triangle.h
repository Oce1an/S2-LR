#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../polygon/polygon.h"

class Triangle : public Polygon {
public:
    Triangle();
    Triangle(const Point& p1, const Point& p2, const Point& p3);

    void setPoints(const Point& p1, const Point& p2, const Point& p3);
    Point getPoint(int index) const;

    // Специфические методы
    double getSideLength(int side) const;  // 0, 1, 2 - стороны
    double getAngle(int vertex) const;     // 0, 1, 2 - углы

    // Проверка свойств
    bool isEquilateral() const;
    bool isIsosceles() const;
    bool isRight() const;
};

#endif // TRIANGLE_H