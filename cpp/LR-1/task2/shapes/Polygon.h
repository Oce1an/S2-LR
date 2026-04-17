#ifndef POLYGON_H
#define POLYGON_H

#include "Shape.h"
#include <QPolygonF>

class Polygon : public Shape
{
    Q_OBJECT
public:
    explicit Polygon(QObject *parent = nullptr);
    virtual ~Polygon() = default;

    double area() const override;
    double perimeter() const override;
    QPointF center() const override;

    void translate(double dx, double dy) override;
    void rotate(double angleDeg, const QPointF &anchor) override;
    void scale(double factor, const QPointF &anchor) override;

    void draw(QPainter &painter) const override;

    const QPolygonF& vertices() const { return m_vertices; }
    void setVertices(const QPolygonF &verts);

protected:
    QPolygonF m_vertices;

    void applyAnimationStep(double progress) override;

private:
    QPolygonF m_originalVertices;
};

#endif