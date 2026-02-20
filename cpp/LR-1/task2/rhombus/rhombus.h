#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "../polygon/polygon.h"

class Rhombus : public Polygon {
private:
    double diagonal1;  // Горизонтальная диагональ
    double diagonal2;  // Вертикальная диагональ

public:
    Rhombus();
    Rhombus(const Point& center, double d1, double d2);

    double area() const override;
    double perimeter() const override;

    double getDiagonal1() const { return diagonal1; }
    double getDiagonal2() const { return diagonal2; }
    void setDiagonals(double d1, double d2);

    void setCenter(const Point& newCenter) override;

private:
    void updateVertices();
    double calculateSide() const;
};

#endif // RHOMBUS_H