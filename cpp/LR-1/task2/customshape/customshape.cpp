#include "customshape.h"
#include <cmath>

Ellipse::Ellipse() : Shape(), radiusX(80), radiusY(50) {}

Ellipse::Ellipse(const Point& c, double rx, double ry)
    : Shape(), radiusX(rx), radiusY(ry) {
    center = c;
}

double Ellipse::area() const {
    return M_PI * radiusX * radiusY * scale * scale;
}

double Ellipse::perimeter() const {
    // Приближенная формула Рамануджана
    double a = radiusX * scale;
    double b = radiusY * scale;
    double h = std::pow((a - b) / (a + b), 2);
    return M_PI * (a + b) * (1 + (3 * h) / (10 + std::sqrt(4 - 3 * h)));
}

void Ellipse::draw(QPainter& painter) const {
    painter.setPen(pen);
    painter.setBrush(color);

    painter.save();
    painter.translate(center.x, center.y);
    painter.rotate(rotationAngle * 180 / M_PI);
    painter.scale(scale, scale);

    painter.drawEllipse(QPointF(0, 0), radiusX, radiusY);
    painter.restore();
}

bool Ellipse::containsPoint(const Point& p) const {
    // Преобразование точки в локальные координаты эллипса
    Point local = p - center;

    // Обратный поворот
    double cosA = std::cos(rotationAngle);
    double sinA = std::sin(rotationAngle);
    double x = local.x * cosA + local.y * sinA;
    double y = -local.x * sinA + local.y * cosA;

    // Проверка в масштабированных координатах
    x /= (radiusX * scale);
    y /= (radiusY * scale);

    return (x * x + y * y <= 1.0);
}

void Ellipse::setRadii(double rx, double ry) {
    radiusX = rx;
    radiusY = ry;
}

void Ellipse::setCenter(const Point& newCenter) {
    center = newCenter;
}