#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "../Polygon.h"

class Rhombus : public Polygon
{
    Q_OBJECT
public:
    Rhombus(double cx, double cy, double width, double height, QObject *parent = nullptr);

    double diagonalX() const { return m_diagX; }
    double diagonalY() const { return m_diagY; }
    void setDiagonalX(double dx);
    void setDiagonalY(double dy);

private:
    double m_diagX, m_diagY;
    void updateVertices();
};

#endif