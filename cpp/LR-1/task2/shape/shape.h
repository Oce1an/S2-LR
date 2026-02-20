#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QObject>
#include <QTimer>
#include "../point/point.h"

// Базовый абстрактный класс для всех фигур
class Shape : public QObject {
    Q_OBJECT

protected:
    Point center;           // Центр масс
    double rotationAngle;   // Угол поворота в радианах
    double scale;           // Масштаб
    QColor color;           // Цвет заливки
    QPen pen;               // Перо для контура

    // Для анимации
    QTimer* animationTimer;
    Point targetPosition;
    double targetRotation;
    double targetScale;
    int animationSteps;
    int currentStep;
    bool isAnimating;

public:
    Shape();
    virtual ~Shape();

    // Чисто виртуальные методы
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void draw(QPainter& painter) const = 0;
    virtual bool containsPoint(const Point& p) const = 0;

    // Виртуальные методы с реализацией по умолчанию
    virtual Point getCenter() const { return center; }
    virtual void setCenter(const Point& newCenter);

    virtual double getRotation() const { return rotationAngle; }
    virtual void setRotation(double angle);

    virtual double getScale() const { return scale; }
    virtual void setScale(double s);

    virtual QColor getColor() const { return color; }
    virtual void setColor(const QColor& newColor) { color = newColor; }

    virtual QPen getPen() const { return pen; }
    virtual void setPen(const QPen& newPen) { pen = newPen; }

    // Методы для плавных преобразований
    void moveTo(const Point& target, int durationMs = 1000);
    void rotateTo(double angle, int durationMs = 1000);
    void scaleTo(double s, int durationMs = 1000);
    void transformTo(const Point& target, double angle, double s, int durationMs = 1000);
    void stopAnimation();

signals:
    void animationStarted();
    void animationStep();  // Генерируется на каждом шаге анимации
    void animationFinished();

protected slots:
    virtual void onAnimationTimer();

protected:
    // Вспомогательные методы для потомков
    virtual void applyTransformations() {}
};

#endif // SHAPE_H