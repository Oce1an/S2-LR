#include "triangle.h"
#include <cmath>
#include <algorithm>

Triangle::Triangle() {
    // Равносторонний треугольник по умолчанию
    Point p1(100, 100);
    Point p2(200, 100);
    Point p3(150, 100 + 50 * std::sqrt(3));
    setPoints(p1, p2, p3);
    center = computeCentroid();
}

Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3) {
    setPoints(p1, p2, p3);
    center = computeCentroid();
}

void Triangle::setPoints(const Point& p1, const Point& p2, const Point& p3) {
    vertices.clear();
    vertices.push_back(p1);
    vertices.push_back(p2);
    vertices.push_back(p3);
    center = computeCentroid();
    updateTransformedVertices();
}

Point Triangle::getPoint(int index) const {
    if (index >= 0 && index < 3) {
        return transformedVertices[index];
    }
    return Point();
}

double Triangle::getSideLength(int side) const {
    if (side < 0 || side >= 3) return 0;

    int i1 = side;
    int i2 = (side + 1) % 3;
    return vertices[i1].distanceTo(vertices[i2]);
}

double Triangle::getAngle(int vertex) const {
    if (vertex < 0 || vertex >= 3) return 0;

    int prev = (vertex + 2) % 3;
    int next = (vertex + 1) % 3;

    Point v1 = vertices[prev] - vertices[vertex];
    Point v2 = vertices[next] - vertices[vertex];

    double dot = v1.x * v2.x + v1.y * v2.y;
    double len1 = std::sqrt(v1.x * v1.x + v1.y * v1.y);
    double len2 = std::sqrt(v2.x * v2.x + v2.y * v2.y);

    return std::acos(dot / (len1 * len2));
}

bool Triangle::isEquilateral() const {
    double s1 = getSideLength(0);
    double s2 = getSideLength(1);
    double s3 = getSideLength(2);

    const double eps = 1e-6;
    return (std::abs(s1 - s2) < eps && std::abs(s2 - s3) < eps);
}

bool Triangle::isIsosceles() const {
    double s1 = getSideLength(0);
    double s2 = getSideLength(1);
    double s3 = getSideLength(2);

    const double eps = 1e-6;
    return (std::abs(s1 - s2) < eps ||
        std::abs(s2 - s3) < eps ||
        std::abs(s3 - s1) < eps);
}

bool Triangle::isRight() const {
    double s1 = getSideLength(0);
    double s2 = getSideLength(1);
    double s3 = getSideLength(2);

    // Проверка теоремы Пифагора
    double sides[3] = { s1, s2, s3 };
    std::sort(sides, sides + 3);

    const double eps = 1e-6;
    return std::abs(sides[2] * sides[2] - (sides[0] * sides[0] + sides[1] * sides[1])) < eps;
}