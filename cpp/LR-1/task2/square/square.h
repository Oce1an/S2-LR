#ifndef SQUARE_H
#define SQUARE_H

#include "../polygon/polygon.h"

//  вадрат - отдельный класс, не наследник Rectangle
class Square : public Polygon {
private:
    double side;

public:
    Square();
    Square(const Point& center, double s);

    double area() const override;
    double perimeter() const override;

    double getSide() const { return side; }
    void setSide(double s);

    void setCenter(const Point& newCenter) override;

private:
    void updateVertices();
};

#endif // SQUARE_H  