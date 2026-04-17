#ifndef CIRCLE_H
#define CIRCLE_H

#include "Ellipse.h"

class Circle : public Ellipse
{
    Q_OBJECT
public:
    Circle(double cx, double cy, double radius, QObject *parent = nullptr);

    double radius() const { return radiusX(); }
    void setRadius(double r);

    void scale(double factor, const QPointF &anchor) override;
    void setRadiusX(double rx) override;
    void setRadiusY(double ry) override;
};

#endif