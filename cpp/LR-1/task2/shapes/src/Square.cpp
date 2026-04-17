#include "../hdr/Square.h"

Square::Square(double cx, double cy, double side, QObject *parent)
    : Polygon(parent), m_side(side)
{
    updateVertices();
    QPointF currentCenter = center();
    translate(cx - currentCenter.x(), cy - currentCenter.y());
}

void Square::updateVertices()
{
    QPolygonF poly;
    double half = m_side / 2.0;
    poly << QPointF(-half, -half)
         << QPointF( half, -half)
         << QPointF( half,  half)
         << QPointF(-half,  half);
    setVertices(poly);
}

void Square::setSide(double s)
{
    if (qFuzzyCompare(m_side, s)) return;
    m_side = s;
    updateVertices();
}