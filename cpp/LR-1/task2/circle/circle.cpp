#include "circle.h"
#include <cmath>

Circle::Circle() : Shape(), radius(50) {}

Circle::Circle(const Point& c, double r) : Shape(), radius(r) {
    center = c;
}

double Circle::area() const {
    return M_PI * radius * radius * scale * scale;
}

double Circle::perimeter() const {
    return 2 * M_PI * radius * scale;
}

void Circle::draw(QPainter& painter) const {
    painter.setPen(pen);
    painter.setBrush(color);

    int r = static_cast<int>(radius * scale);
    painter.drawEllipse(QPointF(center.x, center.y), r, r);
}

bool Circle::containsPoint(const Point& p) const {
    return center.distanceTo(p) <= radius * scale;
}

void Circle::setRadius(double r) {
    radius = r;
}

void Circle::setCenter(const Point& newCenter) {
    center = newCenter;
}