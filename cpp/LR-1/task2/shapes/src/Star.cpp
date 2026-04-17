#include "../hdr/Star.h"
#include <cmath>

Star::Star(double cx, double cy, int points, double outerRadius, double innerRadius, QObject *parent)
    : Polygon(parent), m_points(points), m_outerR(outerRadius), m_innerR(innerRadius)
{
    updateVertices();
    QPointF currentCenter = center();
    translate(cx - currentCenter.x(), cy - currentCenter.y());
}

void Star::updateVertices()
{
    QPolygonF poly;
    double angleStep = M_PI / m_points;
    double angle = -M_PI_2;
    for (int i = 0; i < 2 * m_points; ++i) {
        double r = (i % 2 == 0) ? m_outerR : m_innerR;
        double x = r * cos(angle);
        double y = r * sin(angle);
        poly << QPointF(x, y);
        angle += angleStep;
    }
    setVertices(poly);
}

void Star::setOuterRadius(double r)
{
    m_outerR = r;
    updateVertices();
}

void Star::setInnerRadius(double r)
{
    m_innerR = r;
    updateVertices();
}

void Star::setPoints(int p)
{
    m_points = p;
    updateVertices();
}