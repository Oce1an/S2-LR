#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "../polygon/polygon.h"

class Rectangle : public Polygon {
protected:
    double width;
    double height;

public:
    Rectangle();
    Rectangle(const Point& center, double w, double h);

    // Переопределение виртуальных методов
    double area() const override;
    double perimeter() const override;

    // Специфические методы
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    void setWidth(double w);
    void setHeight(double h);
    void setSize(double w, double h);

    void setCenter(const Point& newCenter) override;

protected:
    void updateVertices();
};

#endif // RECTANGLE_H