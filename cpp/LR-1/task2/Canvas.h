#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QList>
#include "shapes/Shape.h"

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);

    void addShape(Shape *shape);
    void removeShape(Shape *shape);
    void clearShapes();
    QList<Shape*> shapes() const { return m_shapes; }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QList<Shape*> m_shapes;
};

#endif