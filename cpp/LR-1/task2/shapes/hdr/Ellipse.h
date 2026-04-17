#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "../Shape.h"
#include <QRectF>

class Ellipse : public Shape
{
    Q_OBJECT
public:
    Ellipse(double cx, double cy, double rx, double ry, QObject *parent = nullptr);

    double area() const override;
    double perimeter() const override;
    QPointF center() const override;

    void translate(double dx, double dy) override;
    void rotate(double angleDeg, const QPointF &anchor) override;
    void scale(double factor, const QPointF &anchor) override;

    void draw(QPainter &painter) const override;

    double radiusX() const { return m_rx; }
    double radiusY() const { return m_ry; }
    virtual void setRadiusX(double rx);
    virtual void setRadiusY(double ry);

protected:
    void applyAnimationStep(double progress) override;

private:
    double m_rx, m_ry;
    QPointF m_center;

    QPointF m_originalCenter;
    double m_originalRx;
    double m_originalRy;
};

#endif