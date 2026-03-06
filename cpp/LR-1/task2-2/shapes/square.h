#ifndef SQUARE_H
#define SQUARE_H

#include "rectangle.h"

class Square : public Rectangle
{
    Q_OBJECT
public:
    explicit Square(QObject* parent = nullptr);
    Square(const QPointF& topLeft, double side, QObject* parent = nullptr);
    virtual ~Square();

    QString typeName() const override;

    void setSide(double side);
    double side() const;
};

#endif // SQUARE_H