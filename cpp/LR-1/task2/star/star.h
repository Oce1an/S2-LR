#ifndef STAR_H
#define STAR_H

#include "../polygon/polygon.h"

class Star : public Polygon {
private:
    int points;          // Количество лучей (5, 6, 8)
    double outerRadius;  // Внешний радиус
    double innerRadius;  // Внутренний радиус

public:
    Star();
    Star(const Point& center, int p, double outerR, double innerR);

    double area() const override;
    double perimeter() const override;

    int getPoints() const { return points; }
    double getOuterRadius() const { return outerRadius; }
    double getInnerRadius() const { return innerRadius; }

    void setPoints(int p);
    void setRadii(double outerR, double innerR);

    void setCenter(const Point& newCenter) override;

private:
    void updateVertices();
};

#endif // STAR_H