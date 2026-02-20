#ifndef POINT_H
#define POINT_H

#include <cmath>

struct Point {
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}

    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }

    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }

    Point operator*(double scalar) const {
        return Point(x * scalar, y * scalar);
    }

    Point operator/(double scalar) const {
        return Point(x / scalar, y / scalar);
    }

    double distanceTo(const Point& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    Point rotated(double angle, const Point& center = Point(0, 0)) const {
        double s = sin(angle);
        double c = cos(angle);

        // Перенос в начало координат
        double x1 = x - center.x;
        double y1 = y - center.y;

        // Поворот
        double x2 = x1 * c - y1 * s;
        double y2 = x1 * s + y1 * c;

        // Возврат обратно
        return Point(x2 + center.x, y2 + center.y);
    }
};

#endif // POINT_H