#include "canvas.h"
#include <QPainter>
#include <QMouseEvent>

Canvas::Canvas(QWidget* parent)
    : QWidget(parent)
    , m_selectedIndex(-1)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

void Canvas::addShape(QSharedPointer<Shape> shape)
{
    if (shape) {
        m_shapes.append(shape);
        // Используем безопасное соединение
        connect(shape.data(), &Shape::shapeChanged, this, [this]() {
            update();
            });
        update();
    }
}

void Canvas::removeShape(int index)
{
    if (index >= 0 && index < m_shapes.size()) {
        // Отключаем сигналы от удаляемой фигуры
        if (m_shapes[index]) {
            m_shapes[index]->disconnect(this);
        }

        m_shapes.removeAt(index);

        // Корректно обновляем выделение
        if (m_shapes.isEmpty()) {
            m_selectedIndex = -1;
        }
        else if (m_selectedIndex >= m_shapes.size()) {
            m_selectedIndex = m_shapes.size() - 1;
        }

        emit selectionChanged(m_selectedIndex);
        update();
    }
}

void Canvas::clear()
{
    // Отключаем сигналы от всех фигур
    for (const auto& shape : m_shapes) {
        if (shape) {
            shape->disconnect(this);
        }
    }

    m_shapes.clear();
    m_selectedIndex = -1;

    emit selectionChanged(m_selectedIndex);
    update();
}

QSharedPointer<Shape> Canvas::shapeAt(int index) const
{
    if (index >= 0 && index < m_shapes.size()) {
        return m_shapes[index];
    }
    return QSharedPointer<Shape>();
}

int Canvas::shapeCount() const
{
    return m_shapes.size();
}

QSharedPointer<Shape> Canvas::selectedShape() const
{
    if (m_selectedIndex >= 0 && m_selectedIndex < m_shapes.size()) {
        return m_shapes[m_selectedIndex];
    }
    return QSharedPointer<Shape>();
}

void Canvas::setSelectedIndex(int index)
{
    int oldIndex = m_selectedIndex;

    // Добавляем проверку на пустой список
    if (m_shapes.isEmpty()) {
        m_selectedIndex = -1;
    }
    else if (index >= -1 && index < m_shapes.size()) {
        m_selectedIndex = index;
    }

    if (oldIndex != m_selectedIndex) {
        emit selectionChanged(m_selectedIndex);
        update();
    }
}

void Canvas::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Сетка
    painter.setPen(Qt::lightGray);
    for (int x = 0; x < width(); x += 20) {
        painter.drawLine(x, 0, x, height());
    }
    for (int y = 0; y < height(); y += 20) {
        painter.drawLine(0, y, width(), y);
    }

    // Рисуем фигуры с заливкой
    for (int i = 0; i < m_shapes.size(); ++i) {
        if (m_shapes[i]) {
            if (i == m_selectedIndex) {
                painter.setPen(QPen(Qt::red, 2));
                painter.setBrush(QColor(255, 200, 200));  // Светло-красная заливка для выбранной фигуры
            }
            else {
                painter.setPen(Qt::black);
                // Разные цвета для разных фигур на основе индекса
                QColor fillColor(200, 200, 255);  // Светло-синий по умолчанию
                switch (i % 5) {
                case 0: fillColor = QColor(200, 255, 200); break;  // Светло-зеленый
                case 1: fillColor = QColor(255, 255, 200); break;  // Светло-желтый
                case 2: fillColor = QColor(255, 200, 255); break;  // Светло-розовый
                case 3: fillColor = QColor(200, 255, 255); break;  // Голубой
                case 4: fillColor = QColor(255, 220, 180); break;  // Персиковый
                }
                painter.setBrush(fillColor);
            }
            m_shapes[i]->draw(painter);
        }
    }
}

void Canvas::mousePressEvent(QMouseEvent* event)
{
    // Ищем с конца, так как последние фигуры рисуются поверх
    for (int i = m_shapes.size() - 1; i >= 0; --i) {
        if (m_shapes[i] && m_shapes[i]->contains(event->pos())) {
            setSelectedIndex(i);
            break;
        }
    }
    // Если кликнули не по фигуре, снимаем выделение
    if (m_selectedIndex != -1 &&
        (!m_shapes[m_selectedIndex] || !m_shapes[m_selectedIndex]->contains(event->pos()))) {
        setSelectedIndex(-1);
    }

    QWidget::mousePressEvent(event);
}