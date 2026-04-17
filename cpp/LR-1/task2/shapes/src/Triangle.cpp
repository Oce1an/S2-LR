#include "../hdr/Triangle.h"
#include <cmath>

Triangle::Triangle(double cx, double cy, double side, QObject *parent)
    : Polygon(parent), m_side(side)
{
    updateVertices();
    QPointF currentCenter = center();
    translate(cx - currentCenter.x(), cy - currentCenter.y());
}

void Triangle::updateVertices()
{
    QPolygonF poly;
    double h = m_side * sqrt(3.0) / 2.0;
    poly << QPointF(0, -2.0*h/3.0)
         << QPointF(-m_side/2.0, h/3.0)
         << QPointF( m_side/2.0, h/3.0);
    setVertices(poly);
}

void Triangle::setSide(double s)
{
    m_side = s;
    updateVertices();
}