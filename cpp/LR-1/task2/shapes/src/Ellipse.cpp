#include "../hdr/Ellipse.h"
#include <cmath>

Ellipse::Ellipse(double cx, double cy, double rx, double ry, QObject *parent)
    : Shape(parent), m_rx(rx), m_ry(ry), m_center(cx, cy) {}

double Ellipse::area() const
{
    return M_PI * m_rx * m_ry;
}

double Ellipse::perimeter() const
{
    double a = m_rx, b = m_ry;
    double h = pow(a - b, 2) / pow(a + b, 2);
    return M_PI * (a + b) * (1 + 3 * h / (10 + sqrt(4 - 3 * h)));
}

QPointF Ellipse::center() const
{
    return m_center;
}

void Ellipse::translate(double dx, double dy)
{
    m_center += QPointF(dx, dy);
    emit transformed();
}

void Ellipse::rotate(double angleDeg, const QPointF &anchor)
{
    QPointF offset = m_center - anchor;
    double rad = angleDeg * M_PI / 180.0;
    m_center = anchor + QPointF(offset.x() * cos(rad) - offset.y() * sin(rad),
                                offset.x() * sin(rad) + offset.y() * cos(rad));
    emit transformed();
}

void Ellipse::scale(double factor, const QPointF &anchor)
{
    m_rx *= factor;
    m_ry *= factor;
    QPointF offset = m_center - anchor;
    m_center = anchor + offset * factor;
    emit transformed();
}

void Ellipse::draw(QPainter &painter) const
{
    painter.drawEllipse(m_center, m_rx, m_ry);
}

void Ellipse::setRadiusX(double rx)
{
    m_rx = rx;
    emit transformed();
}

void Ellipse::setRadiusY(double ry)
{
    m_ry = ry;
    emit transformed();
}

void Ellipse::applyAnimationStep(double progress)
{
    if (m_animData.type == AnimationType::None) return;
    
    if (progress <= 0.01) {
        m_originalCenter = m_center;
        m_originalRx = m_rx;
        m_originalRy = m_ry;
    }
    
    switch (m_animData.type) {
    case AnimationType::Translate: {
        double stepDx = m_animData.dx * progress;
        double stepDy = m_animData.dy * progress;
        m_center = m_originalCenter + QPointF(stepDx, stepDy);
        emit transformed();
        break;
    }
    case AnimationType::Rotate: {
        double stepAngle = m_animData.angleDeg * progress;
        QPointF offset = m_originalCenter - m_animData.anchor;
        double rad = stepAngle * M_PI / 180.0;
        m_center = m_animData.anchor + QPointF(offset.x() * cos(rad) - offset.y() * sin(rad),
                                                offset.x() * sin(rad) + offset.y() * cos(rad));
        emit transformed();
        break;
    }
    case AnimationType::Scale: {
        double stepFactor = 1.0 + (m_animData.factor - 1.0) * progress;
        m_rx = m_originalRx * stepFactor;
        m_ry = m_originalRy * stepFactor;
        QPointF offset = m_originalCenter - m_animData.anchor;
        m_center = m_animData.anchor + offset * stepFactor;
        emit transformed();
        break;
    }
    default:
        break;
    }
}