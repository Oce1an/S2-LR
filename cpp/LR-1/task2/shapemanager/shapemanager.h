#ifndef SHAPEMANAGER_H
#define SHAPEMANAGER_H

#include <QObject>
#include <QList>
#include <memory>
#include "../shape/shape.h"

class ShapeManager : public QObject {
    Q_OBJECT

private:
    QList<std::shared_ptr<Shape>> shapes;

public:
    ShapeManager();
    ~ShapeManager();

    void addShape(std::shared_ptr<Shape> shape);
    void removeShape(int index);
    void clearShapes();

    std::shared_ptr<Shape> getShape(int index) const;
    int getShapeCount() const { return shapes.size(); }

    void drawAll(QPainter& painter) const;

    // Поиск фигуры по точке
    int findShapeAtPoint(const Point& p) const;

    // Информация о фигурах
    QString getShapeInfo(int index) const;
};

#endif // SHAPEMANAGER_H