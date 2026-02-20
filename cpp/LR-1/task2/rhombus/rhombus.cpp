#include "rhombus.h"
#include <cmath>

Rhombus::Rhombus() : Polygon(), diagonal1(120), diagonal2(80) {
    updateVertices();
}

Rhombus::Rhombus(const Point& c, double d1, double d2)
    : Polygon(), diagonal1(d1), diagonal2(d2) {
    center = c;
    updateVertices();
}

double Rhombus::area() const {
    return (diagonal1 * diagonal2 / 2) * scale * scale;
}

double Rhombus::perimeter() const {
    return 4 * calculateSide() * scale;
}

void Rhombus::setDiagonals(double d1, double d2) {
    diagonal1 = d1;
    diagonal2 = d2;
    updateVertices();
}

void Rhombus::setCenter(const Point& newCenter) {
    center = newCenter;
    updateVertices();
}

void Rhombus::updateVertices() {
    vertices.clear();

    double halfD1 = diagonal1 / 2;
    double halfD2 = diagonal2 / 2;

    vertices.push_back(Point(center.x + halfD1, center.y));
    vertices.push_back(Point(center.x, center.y + halfD2));
    vertices.push_back(Point(center.x - halfD1, center.y));
    vertices.push_back(Point(center.x, center.y - halfD2));

    updateTransformedVertices();
}

double Rhombus::calculateSide() const {
    return std::sqrt((diagonal1 / 2) * (diagonal1 / 2) + (diagonal2 / 2) * (diagonal2 / 2));
}