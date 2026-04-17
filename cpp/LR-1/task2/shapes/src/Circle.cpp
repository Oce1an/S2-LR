#include "../hdr/Circle.h"

Circle::Circle(double cx, double cy, double radius, QObject *parent)
    : Ellipse(cx, cy, radius, radius, parent) {}

void Circle::setRadius(double r)
{
    Ellipse::setRadiusX(r);
    Ellipse::setRadiusY(r);
}

void Circle::scale(double factor, const QPointF &anchor)
{
    Ellipse::scale(factor, anchor);
    double r = radiusX();
    setRadius(r);
}

void Circle::setRadiusX(double rx)
{
    Ellipse::setRadiusX(rx);
    Ellipse::setRadiusY(rx);
}

void Circle::setRadiusY(double ry)
{
    Ellipse::setRadiusY(ry);
    Ellipse::setRadiusX(ry);
}