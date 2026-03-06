#include "shapemanager.h"
#include <QString>

ShapeManager::ShapeManager() {}

ShapeManager::~ShapeManager() {}

void ShapeManager::addShape(std::shared_ptr<Shape> shape) {
    if (shape) {
        shapes.append(shape);
    }
}

void ShapeManager::removeShape(int index) {
    if (index >= 0 && index < shapes.size()) {
        shapes.removeAt(index);
    }
}

void ShapeManager::clearShapes() {
    shapes.clear();
}

std::shared_ptr<Shape> ShapeManager::getShape(int index) const {
    if (index >= 0 && index < shapes.size()) {
        return shapes[index];
    }
    return nullptr;
}

void ShapeManager::drawAll(QPainter& painter) const {
    for (const auto& shape : shapes) {
        shape->draw(painter);
    }
}

int ShapeManager::findShapeAtPoint(const Point& p) const {
    // »щем с конца (верхний слой)
    for (int i = shapes.size() - 1; i >= 0; --i) {
        if (shapes[i]->containsPoint(p)) {
            return i;
        }
    }
    return -1;
}

QString ShapeManager::getShapeInfo(int index) const
{
    auto shape = getShape(index);
    if (!shape) return QString();

    QString info;

    auto c = shape->getCenter();

    info += QString("Area: %1\n").arg(shape->area());
    info += QString("Perimeter: %1\n").arg(shape->perimeter());
    info += QString("Center: (%1, %2)\n").arg(c.x, 0, 'f', 1).arg(c.y, 0, 'f', 1);
    info += QString("Rotation: %1deg\n").arg(shape->getRotation() * 180.0 / M_PI, 0, 'f', 1);
    info += QString("Scale: %1").arg(shape->getScale(), 0, 'f', 2);

    return info;
}