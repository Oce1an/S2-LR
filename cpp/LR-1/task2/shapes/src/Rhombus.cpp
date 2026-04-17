#include "../hdr/Rhombus.h"

Rhombus::Rhombus(double cx, double cy, double width, double height, QObject *parent)
    : Polygon(parent), m_diagX(width), m_diagY(height)
{
    updateVertices();
    QPointF currentCenter = center();
    translate(cx - currentCenter.x(), cy - currentCenter.y());
}

void Rhombus::updateVertices()
{
    QPolygonF poly;
    double halfX = m_diagX / 2.0;
    double halfY = m_diagY / 2.0;
    poly << QPointF( halfX, 0.0);
    poly << QPointF( 0.0,  halfY);
    poly << QPointF(-halfX, 0.0);
    poly << QPointF( 0.0, -halfY);
    setVertices(poly);
}

void Rhombus::setDiagonalX(double dx)
{
    if (qFuzzyCompare(m_diagX, dx))
        return;
    m_diagX = dx;
    updateVertices();
}

void Rhombus::setDiagonalY(double dy)
{
    if (qFuzzyCompare(m_diagY, dy))
        return;
    m_diagY = dy;
    updateVertices();
}