#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../Polygon.h"

class Triangle : public Polygon
{
    Q_OBJECT
public:
    Triangle(double cx, double cy, double side, QObject *parent = nullptr);
    double side() const { return m_side; }
    void setSide(double s);
private:
    double m_side;
    void updateVertices();
};

#endif