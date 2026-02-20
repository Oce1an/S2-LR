#include "star.h"
#include <cmath>

Star::Star() : Polygon(), points(5), outerRadius(80), innerRadius(40) {
    updateVertices();
}

Star::Star(const Point& c, int p, double outerR, double innerR)
    : Polygon(), points(p), outerRadius(outerR), innerRadius(innerR) {
    if (points < 3) points = 5;
    center = c;
    updateVertices();
}

double Star::area() const {
    // Приблизительная площадь через триангуляцию
    double totalArea = 0;
    for (size_t i = 1; i < vertices.size() - 1; ++i) {
        totalArea += triangleArea(vertices[0], vertices[i], vertices[i + 1]);
    }
    return totalArea * scale * scale;
}

double Star::perimeter() const {
    double perim = 0;
    for (size_t i = 0; i < vertices.size(); ++i) {
        size_t next = (i + 1) % vertices.size();
        perim += vertices[i].distanceTo(vertices[next]);
    }
    return perim * scale;
}

void Star::setPoints(int p) {
    if (p >= 3) {
        points = p;
        updateVertices();
    }
}

void Star::setRadii(double outerR, double innerR) {
    outerRadius = outerR;
    innerRadius = innerR;
    updateVertices();
}

void Star::setCenter(const Point& newCenter) {
    center = newCenter;
    updateVertices();
}

void Star::updateVertices() {
    vertices.clear();

    int totalPoints = points * 2;
    for (int i = 0; i < totalPoints; ++i) {
        double angle = (i * M_PI) / points; // Угол для каждой вершины
        double r = (i % 2 == 0) ? outerRadius : innerRadius;

        double x = center.x + r * std::cos(angle);
        double y = center.y + r * std::sin(angle);
        vertices.push_back(Point(x, y));
    }

    updateTransformedVertices();
}