#ifndef SQUARE_H
#define SQUARE_H

#include "../Polygon.h"

class Square : public Polygon
{
    Q_OBJECT
public:
    Square(double cx, double cy, double side, QObject *parent = nullptr);

    double side() const { return m_side; }
    void setSide(double s);

private:
    double m_side;
    void updateVertices();
};

#endif