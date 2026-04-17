#include "../hdr/Hexagon.h"
#include <cmath>

Hexagon::Hexagon(double cx, double cy, double side, QObject *parent)
    : Polygon(parent), m_side(side)
{
    updateVertices();
    QPointF currentCenter = center();
    translate(cx - currentCenter.x(), cy - currentCenter.y());
}

void Hexagon::updateVertices()
{
    QPolygonF poly;
    double angleStep = 2.0 * M_PI / 6.0;
    double startAngle = -M_PI_2;
    for (int i = 0; i < 6; ++i) {
        double angle = startAngle + i * angleStep;
        double x = m_side * cos(angle);
        double y = m_side * sin(angle);
        poly << QPointF(x, y);
    }
    setVertices(poly);
}

void Hexagon::setSide(double s)
{
    if (qFuzzyCompare(m_side, s))
        return;
    m_side = s;
    updateVertices();
}