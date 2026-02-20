#include "square.h"

Square::Square() : Polygon(), side(80) {
    updateVertices();
}

Square::Square(const Point& c, double s) : Polygon(), side(s) {
    center = c;
    updateVertices();
}

double Square::area() const {
    return side * side * scale * scale;
}

double Square::perimeter() const {
    return 4 * side * scale;
}

void Square::setSide(double s) {
    side = s;
    updateVertices();
}

void Square::setCenter(const Point& newCenter) {
    center = newCenter;
    updateVertices();
}

void Square::updateVertices() {
    vertices.clear();

    double half = side / 2;

    vertices.push_back(Point(center.x - half, center.y - half));
    vertices.push_back(Point(center.x + half, center.y - half));
    vertices.push_back(Point(center.x + half, center.y + half));
    vertices.push_back(Point(center.x - half, center.y + half));

    updateTransformedVertices();
}