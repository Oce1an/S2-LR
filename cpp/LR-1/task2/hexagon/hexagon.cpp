#include "hexagon.h"
#include <cmath>

Hexagon::Hexagon() : Polygon(), radius(60) {
    updateVertices();
}

Hexagon::Hexagon(const Point& c, double r) : Polygon(), radius(r) {
    center = c;
    updateVertices();
}

double Hexagon::area() const {
    return (3 * std::sqrt(3) / 2) * radius * radius * scale * scale;
}

double Hexagon::perimeter() const {
    return 6 * radius * scale;
}

void Hexagon::setRadius(double r) {
    radius = r;
    updateVertices();
}

void Hexagon::setCenter(const Point& newCenter) {
    center = newCenter;
    updateVertices();
}

void Hexagon::updateVertices() {
    vertices.clear();

    for (int i = 0; i < 6; ++i) {
        double angle = i * M_PI / 3; // 60 градусов
        double x = center.x + radius * std::cos(angle);
        double y = center.y + radius * std::sin(angle);
        vertices.push_back(Point(x, y));
    }

    updateTransformedVertices();
}