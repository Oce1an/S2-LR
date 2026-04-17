#ifndef SHAPE_H
#define SHAPE_H

#include <QObject>
#include <QPointF>
#include <QPainter>
#include <QVariantAnimation>

// Типы анимации (вынесены наружу для доступа из производных классов)
enum class AnimationType {
    None,
    Translate,
    Rotate,
    Scale
};

// Абстрактный класс "Фигура"
class Shape : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double animationValue READ animationValue WRITE setAnimationValue NOTIFY animationValueChanged)
    
public:
    explicit Shape(QObject *parent = nullptr);
    virtual ~Shape() = default;

    // Геометрические характеристики
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual QPointF center() const = 0;

    // Мгновенные преобразования
    virtual void translate(double dx, double dy) = 0;
    virtual void rotate(double angleDeg, const QPointF &anchor) = 0;
    virtual void scale(double factor, const QPointF &anchor) = 0;

    // Перемещение центра масс (сдвиг всей фигуры)
    void moveCenter(double dx, double dy);

    // Анимированные преобразования
    void animateTranslate(double dx, double dy, int durationMs);
    void animateRotate(double angleDeg, const QPointF &anchor, int durationMs);
    void animateScale(double factor, const QPointF &anchor, int durationMs);

    // Рисование
    virtual void draw(QPainter &painter) const = 0;

    // Свойство для анимации (0.0 -> 1.0)
    double animationValue() const { return m_animProgress; }
    void setAnimationValue(double value);

signals:
    void transformed();              // Испускается при любом изменении фигуры
    void animationFinished();        // Испускается при завершении анимации
    void animationValueChanged();    // Для Q_PROPERTY

protected:
    // Метод, вызываемый на каждом шаге анимации (должен быть переопределён)
    virtual void applyAnimationStep(double progress) = 0;

    // Данные текущей анимации
    struct {
        AnimationType type = AnimationType::None;
        double dx = 0.0;
        double dy = 0.0;
        double angleDeg = 0.0;
        double factor = 1.0;
        QPointF anchor;
    } m_animData;

    double m_animProgress = 0.0;
    QVariantAnimation *m_animation = nullptr;
};

#endif // SHAPE_H