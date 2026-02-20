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

QString ShapeManager::getShapeInfo(int index) const {
    auto shape = getShape(index);
    if (!shape) return QString();

    QString info;
    info += QString("Area: %1\n").arg(shape->area());
    info += QString("Perimeter: %1\n").arg(shape->perimeter());
    info += QString("Center: (%.1f, %.1f)\n").arg(shape->getCenter().x).arg(shape->getCenter().y);
    info += QString("Rotation: %.1fo\n").arg(shape->getRotation() * 180 / M_PI);
    info += QString("Scale: %.2f").arg(shape->getScale());

    return info;
}