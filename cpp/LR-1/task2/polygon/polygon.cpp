#include "polygon.h"
#include <QPolygonF>
#include <limits>

Polygon::Polygon() : Shape() {}

Polygon::~Polygon() {}

double Polygon::area() const {
    if (vertices.size() < 3) return 0;

    // Триангуляция через разбиение на треугольники от первой вершины
    double totalArea = 0;
    for (size_t i = 1; i < vertices.size() - 1; ++i) {
        totalArea += triangleArea(vertices[0], vertices[i], vertices[i + 1]);
    }
    return totalArea;
}

double Polygon::perimeter() const {
    if (vertices.size() < 2) return 0;

    double perim = 0;
    for (size_t i = 0; i < vertices.size(); ++i) {
        size_t next = (i + 1) % vertices.size();
        perim += vertices[i].distanceTo(vertices[next]);
    }
    return perim;
}

void Polygon::draw(QPainter& painter) const {
    if (transformedVertices.size() < 3) return;

    QPolygonF polygon;
    for (const auto& v : transformedVertices) {
        polygon << QPointF(v.x, v.y);
    }

    painter.setPen(pen);
    painter.setBrush(color);
    painter.drawPolygon(polygon);
}

bool Polygon::containsPoint(const Point& p) const {
    if (transformedVertices.size() < 3) return false;

    // Алгоритм проверки точки в многоугольнике (ray casting)
    bool inside = false;
    size_t n = transformedVertices.size();

    for (size_t i = 0, j = n - 1; i < n; j = i++) {
        const Point& vi = transformedVertices[i];
        const Point& vj = transformedVertices[j];

        if (((vi.y > p.y) != (vj.y > p.y)) &&
            (p.x < (vj.x - vi.x) * (p.y - vi.y) / (vj.y - vi.y) + vi.x)) {
            inside = !inside;
        }
    }

    return inside;
}

void Polygon::setVertices(const std::vector<Point>& newVertices) {
    vertices = newVertices;
    updateTransformedVertices();
}

std::vector<Point> Polygon::getVertices() const {
    return vertices;
}

std::vector<Point> Polygon::getTransformedVertices() const {
    return transformedVertices;
}

void Polygon::setCenter(const Point& newCenter) {
    Point oldCenter = center;
    center = newCenter;

    // Сдвигаем все вершины
    Point delta = center - oldCenter;
    for (auto& v : vertices) {
        v = v + delta;
    }

    updateTransformedVertices();
}

void Polygon::setRotation(double angle) {
    rotationAngle = angle;
    updateTransformedVertices();
}

void Polygon::setScale(double s) {
    scale = s;
    updateTransformedVertices();
}

void Polygon::applyTransformations() {
    updateTransformedVertices();
}

void Polygon::updateTransformedVertices() {
    transformedVertices.clear();

    for (const auto& v : vertices) {
        // Масштабирование относительно центра
        Point scaled = (v - center) * scale + center;

        // Поворот относительно центра
        Point rotated = scaled.rotated(rotationAngle, center);

        transformedVertices.push_back(rotated);
    }
}

double Polygon::triangleArea(const Point& a, const Point& b, const Point& c) const {
    return 0.5 * std::abs((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y));
}

Point Polygon::computeCentroid() const {
    if (vertices.empty()) return Point(0, 0);

    Point centroid;
    for (const auto& v : vertices) {
        centroid = centroid + v;
    }
    return centroid / vertices.size();
}