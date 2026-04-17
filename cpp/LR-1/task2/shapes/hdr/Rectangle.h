#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "../Polygon.h"

class Rectangle : public Polygon
{
    Q_OBJECT
public:
    Rectangle(double cx, double cy, double width, double height, QObject *parent = nullptr);

    double width() const { return m_width; }
    double height() const { return m_height; }
    void setWidth(double w);
    void setHeight(double h);

private:
    double m_width, m_height;
    void updateVertices();
};

#endif