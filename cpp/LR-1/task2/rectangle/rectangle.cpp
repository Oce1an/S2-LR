#include "rectangle.h"

Rectangle::Rectangle() : Polygon(), width(100), height(60) {
    updateVertices();
}

Rectangle::Rectangle(const Point& c, double w, double h)
    : Polygon(), width(w), height(h) {
    center = c;
    updateVertices();
}

double Rectangle::area() const {
    return width * height * scale * scale;
}

double Rectangle::perimeter() const {
    return 2 * (width + height) * scale;
}

void Rectangle::setWidth(double w) {
    width = w;
    updateVertices();
}

void Rectangle::setHeight(double h) {
    height = h;
    updateVertices();
}

void Rectangle::setSize(double w, double h) {
    width = w;
    height = h;
    updateVertices();
}

void Rectangle::setCenter(const Point& newCenter) {
    center = newCenter;
    updateVertices();
}

void Rectangle::updateVertices() {
    vertices.clear();

    double halfW = width / 2;
    double halfH = height / 2;

    vertices.push_back(Point(center.x - halfW, center.y - halfH));
    vertices.push_back(Point(center.x + halfW, center.y - halfH));
    vertices.push_back(Point(center.x + halfW, center.y + halfH));
    vertices.push_back(Point(center.x - halfW, center.y + halfH));

    updateTransformedVertices();
}