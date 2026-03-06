#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QList>
#include <QSharedPointer>
#include "shapes/shape.h"

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget* parent = nullptr);

    void addShape(QSharedPointer<Shape> shape);
    void removeShape(int index);
    void clear();
    QSharedPointer<Shape> shapeAt(int index) const;
    int shapeCount() const;
    QSharedPointer<Shape> selectedShape() const;
    int selectedIndex() const { return m_selectedIndex; }
    void setSelectedIndex(int index);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    QList<QSharedPointer<Shape>> m_shapes;
    int m_selectedIndex;
};

#endif // CANVAS_H