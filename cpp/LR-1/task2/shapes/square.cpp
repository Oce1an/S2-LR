#include "square.h"
#include <stdexcept>

Square::Square(QObject* parent) : Rectangle(QPointF(0, 0), 100, 100, parent) {}
Square::Square(const QPointF& topLeft, double side, QObject* parent)
    : Rectangle(topLeft, side, side, parent)
{
    if (side <= 0)
        throw std::invalid_argument("Side must be positive");
}
Square::~Square() {}

QString Square::typeName() const { return "Square"; }

void Square::setSide(double side)
{
    if (side <= 0)
        throw std::invalid_argument("Side must be positive");
    setRect(topLeft(), side, side);
}

double Square::side() const { return width(); }