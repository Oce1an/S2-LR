#ifndef SHAPEANIMATOR_H
#define SHAPEANIMATOR_H

#include <QObject>
#include <QTimer>
#include <QVariantAnimation>
#include <QEasingCurve>
#include "../shapes/Shape.h"

class ShapeAnimator : public QObject
{
    Q_OBJECT
public:
    explicit ShapeAnimator(QObject *parent = nullptr);
    ~ShapeAnimator();

    void setShape(Shape *shape);
    Shape* shape() const { return m_shape; }

    void setDuration(int ms) { m_duration = ms; }
    int duration() const { return m_duration; }
    
    void setEasingCurve(const QEasingCurve &curve);
    QEasingCurve easingCurve() const;

    void startTranslate(double dx, double dy);
    void startRotate(double angleDeg, const QPointF &anchor);
    void startScale(double factor, const QPointF &anchor);

    void stop();
    bool isRunning() const;
    AnimationType currentAnimation() const { return m_currentType; }

signals:
    void started();
    void finished();
    void progressChanged(double progress);
    void step();

private slots:
    void onAnimationValueChanged(const QVariant &value);
    void onAnimationFinished();

private:
    Shape *m_shape;
    QVariantAnimation *m_animation;
    AnimationType m_currentType;
    int m_duration;
    QEasingCurve m_easingCurve;

    struct {
        double dx, dy;
        double angleDeg;
        double factor;
        QPointF anchor;
        QPointF startCenter;
        QPolygonF startVertices;
        double startAngle;

        // Промежуточные значения для пошагового применения (не статические!)
        QPointF lastAppliedTranslate;
        double lastAngle;
        double lastFactor;
    } m_animParams;

    void applyTranslateStep(double progress);
    void applyRotateStep(double progress);
    void applyScaleStep(double progress);
};

#endif