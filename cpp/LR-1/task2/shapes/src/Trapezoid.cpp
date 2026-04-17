#include "../hdr/Trapezoid.h"

Trapezoid::Trapezoid(double cx, double cy, double topWidth, double bottomWidth, double height, QObject *parent)
    : Polygon(parent), m_topWidth(topWidth), m_bottomWidth(bottomWidth), m_height(height)
{
    updateVertices();
    QPointF currentCenter = center();
    translate(cx - currentCenter.x(), cy - currentCenter.y());
}

void Trapezoid::updateVertices()
{
    QPolygonF poly;
    double halfTop = m_topWidth / 2.0;
    double halfBottom = m_bottomWidth / 2.0;
    double halfH = m_height / 2.0;
    poly << QPointF(-halfTop, -halfH);
    poly << QPointF( halfTop, -halfH);
    poly << QPointF( halfBottom,  halfH);
    poly << QPointF(-halfBottom,  halfH);
    setVertices(poly);
}

void Trapezoid::setTopWidth(double w)
{
    if (qFuzzyCompare(m_topWidth, w))
        return;
    m_topWidth = w;
    updateVertices();
}

void Trapezoid::setBottomWidth(double w)
{
    if (qFuzzyCompare(m_bottomWidth, w))
        return;
    m_bottomWidth = w;
    updateVertices();
}

void Trapezoid::setHeight(double h)
{
    if (qFuzzyCompare(m_height, h))
        return;
    m_height = h;
    updateVertices();
}