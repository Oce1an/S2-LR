#include "../hdr/Rectangle.h"

Rectangle::Rectangle(double cx, double cy, double width, double height, QObject *parent)
    : Polygon(parent), m_width(width), m_height(height)
{
    updateVertices();
    QPointF currentCenter = center();
    translate(cx - currentCenter.x(), cy - currentCenter.y());
}

void Rectangle::updateVertices()
{
    QPolygonF poly;
    double halfW = m_width / 2.0;
    double halfH = m_height / 2.0;
    poly << QPointF(-halfW, -halfH)
         << QPointF( halfW, -halfH)
         << QPointF( halfW,  halfH)
         << QPointF(-halfW,  halfH);
    setVertices(poly);
}

void Rectangle::setWidth(double w)
{
    if (qFuzzyCompare(m_width, w)) return;
    m_width = w;
    updateVertices();
}

void Rectangle::setHeight(double h)
{
    if (qFuzzyCompare(m_height, h)) return;
    m_height = h;
    updateVertices();
}