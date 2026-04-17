#include "Polygon.h"
#include <QLineF>
#include <cmath>

Polygon::Polygon(QObject *parent) : Shape(parent) {}

double Polygon::area() const
{
    if (m_vertices.size() < 3) return 0.0;
    double area = 0.0;
    int n = m_vertices.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += m_vertices[i].x() * m_vertices[j].y() - m_vertices[j].x() * m_vertices[i].y();
    }
    return std::abs(area) * 0.5;
}

double Polygon::perimeter() const
{
    double perim = 0.0;
    for (int i = 0; i < m_vertices.size(); ++i) {
        int j = (i + 1) % m_vertices.size();
        perim += QLineF(m_vertices[i], m_vertices[j]).length();
    }
    return perim;
}

QPointF Polygon::center() const
{
    QPointF sum(0,0);
    for (const QPointF &p : m_vertices)
        sum += p;
    return sum / m_vertices.size();
}

void Polygon::translate(double dx, double dy)
{
    m_vertices.translate(dx, dy);
    emit transformed();
}

void Polygon::rotate(double angleDeg, const QPointF &anchor)
{
    double rad = angleDeg * M_PI / 180.0;
    QPointF offset;
    for (QPointF &p : m_vertices) {
        offset = p - anchor;
        p = anchor + QPointF(offset.x() * cos(rad) - offset.y() * sin(rad),
                             offset.x() * sin(rad) + offset.y() * cos(rad));
    }
    emit transformed();
}

void Polygon::scale(double factor, const QPointF &anchor)
{
    for (QPointF &p : m_vertices) {
        QPointF offset = p - anchor;
        p = anchor + offset * factor;
    }
    emit transformed();
}

void Polygon::draw(QPainter &painter) const
{
    painter.drawPolygon(m_vertices);
}

void Polygon::setVertices(const QPolygonF &verts)
{
    m_vertices = verts;
    emit transformed();
}

void Polygon::applyAnimationStep(double progress)
{
    if (m_animData.type == AnimationType::None) return;
    
    if (progress <= 0.01 || m_originalVertices.isEmpty()) {
        m_originalVertices = m_vertices;
    }
    
    switch (m_animData.type) {
    case AnimationType::Translate: {
        double stepDx = m_animData.dx * progress;
        double stepDy = m_animData.dy * progress;
        m_vertices = m_originalVertices;
        translate(stepDx, stepDy);
        break;
    }
    case AnimationType::Rotate: {
        double stepAngle = m_animData.angleDeg * progress;
        m_vertices = m_originalVertices;
        rotate(stepAngle, m_animData.anchor);
        break;
    }
    case AnimationType::Scale: {
        double stepFactor = 1.0 + (m_animData.factor - 1.0) * progress;
        m_vertices = m_originalVertices;
        scale(stepFactor, m_animData.anchor);
        break;
    }
    default:
        break;
    }
}