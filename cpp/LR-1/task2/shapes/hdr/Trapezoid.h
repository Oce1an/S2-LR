#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "../Polygon.h"

class Trapezoid : public Polygon
{
    Q_OBJECT
public:
    Trapezoid(double cx, double cy, double topWidth, double bottomWidth, double height, QObject *parent = nullptr);

    double topWidth() const { return m_topWidth; }
    double bottomWidth() const { return m_bottomWidth; }
    double height() const { return m_height; }
    void setTopWidth(double w);
    void setBottomWidth(double w);
    void setHeight(double h);

private:
    double m_topWidth;
    double m_bottomWidth;
    double m_height;
    void updateVertices();
};

#endif