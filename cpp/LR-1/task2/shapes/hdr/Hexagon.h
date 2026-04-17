#ifndef HEXAGON_H
#define HEXAGON_H

#include "../Polygon.h"

class Hexagon : public Polygon
{
    Q_OBJECT
public:
    Hexagon(double cx, double cy, double side, QObject *parent = nullptr);

    double side() const { return m_side; }
    void setSide(double s);

private:
    double m_side;
    void updateVertices();
};

#endif