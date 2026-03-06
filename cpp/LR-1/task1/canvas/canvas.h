#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include "../car/car.h"

class Canvas : public QWidget
{
    Q_OBJECT

private:
    Car* car;

public:
    explicit Canvas(Car* car, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent*) override;
};

#endif