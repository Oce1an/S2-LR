#ifndef POLYGON_H
#define POLYGON_H

#include "../shape/shape.h"
#include <vector>

// Базовый класс для всех многоугольников
class Polygon : public Shape {
protected:
    std::vector<Point> vertices;  // Вершины в локальных координатах
    std::vector<Point> transformedVertices;  // Вершины после трансформаций

public:
    Polygon();
    virtual ~Polygon();

    // Переопределение виртуальных методов
    double area() const override;
    double perimeter() const override;
    void draw(QPainter& painter) const override;
    bool containsPoint(const Point& p) const override;

    // Методы для работы с вершинами
    virtual void setVertices(const std::vector<Point>& newVertices);
    virtual std::vector<Point> getVertices() const;
    virtual std::vector<Point> getTransformedVertices() const;

    // Переопределение методов трансформации
    void setCenter(const Point& newCenter) override;
    void setRotation(double angle) override;
    void setScale(double s) override;

protected:
    void applyTransformations() override;
    void updateTransformedVertices();

    // Вспомогательные методы
    double triangleArea(const Point& a, const Point& b, const Point& c) const;
    Point computeCentroid() const;
};

#endif // POLYGON_H