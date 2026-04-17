#include "Canvas.h"
#include <QPainter>

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
    setPalette(QPalette(Qt::white));
    setFixedSize(800, 600);
}

void Canvas::addShape(Shape *shape)
{
    m_shapes.append(shape);
    connect(shape, &Shape::transformed, this, static_cast<void(Canvas::*)()>(&Canvas::update));
    update();
}

void Canvas::removeShape(Shape *shape)
{
    m_shapes.removeOne(shape);
    disconnect(shape, &Shape::transformed, this, nullptr);
    update();
}

void Canvas::clearShapes()
{
    for (Shape *s : m_shapes)
        disconnect(s, &Shape::transformed, this, nullptr);
    m_shapes.clear();
    update();
}

void Canvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    for (Shape *shape : m_shapes) {
        painter.save();
        shape->draw(painter);
        painter.restore();
    }
}