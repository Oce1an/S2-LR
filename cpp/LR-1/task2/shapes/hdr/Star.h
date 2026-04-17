#ifndef STAR_H
#define STAR_H

#include "../Polygon.h"

class Star : public Polygon
{
    Q_OBJECT
public:
    Star(double cx, double cy, int points, double outerRadius, double innerRadius, QObject *parent = nullptr);

    int points() const { return m_points; }
    double outerRadius() const { return m_outerR; }
    double innerRadius() const { return m_innerR; }
    void setOuterRadius(double r);
    void setInnerRadius(double r);
    void setPoints(int p);

private:
    int m_points;
    double m_outerR;
    double m_innerR;
    void updateVertices();
};

#endif