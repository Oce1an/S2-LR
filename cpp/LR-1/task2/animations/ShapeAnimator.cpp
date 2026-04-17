#include "ShapeAnimator.h"
#include <cmath>

ShapeAnimator::ShapeAnimator(QObject *parent)
    : QObject(parent)
    , m_shape(nullptr)
    , m_animation(nullptr)
    , m_currentType(AnimationType::None)
    , m_duration(1000)
    , m_easingCurve(QEasingCurve::Linear)
{
    // Инициализация полей структуры
    m_animParams.lastAppliedTranslate = QPointF(0,0);
    m_animParams.lastAngle = 0.0;
    m_animParams.lastFactor = 1.0;
}

ShapeAnimator::~ShapeAnimator()
{
    stop();
}

void ShapeAnimator::setShape(Shape *shape)
{
    if (m_shape) {
        disconnect(m_shape, nullptr, this, nullptr);
    }
    m_shape = shape;
    stop();
}

void ShapeAnimator::setEasingCurve(const QEasingCurve &curve)
{
    m_easingCurve = curve;
    if (m_animation) {
        m_animation->setEasingCurve(curve);
    }
}

QEasingCurve ShapeAnimator::easingCurve() const
{
    return m_easingCurve;
}

void ShapeAnimator::startTranslate(double dx, double dy)
{
    if (!m_shape) return;
    stop();

    m_currentType = AnimationType::Translate;
    m_animParams.dx = dx;
    m_animParams.dy = dy;
    m_animParams.startCenter = m_shape->center();
    m_animParams.lastAppliedTranslate = QPointF(0,0);

    m_animation = new QVariantAnimation(this);
    m_animation->setDuration(m_duration);
    m_animation->setEasingCurve(m_easingCurve);
    m_animation->setStartValue(0.0);
    m_animation->setEndValue(1.0);

    connect(m_animation, &QVariantAnimation::valueChanged,
            this, &ShapeAnimator::onAnimationValueChanged);
    connect(m_animation, &QVariantAnimation::finished,
            this, &ShapeAnimator::onAnimationFinished);

    m_animation->start(QAbstractAnimation::DeleteWhenStopped);
    emit started();
}

void ShapeAnimator::startRotate(double angleDeg, const QPointF &anchor)
{
    if (!m_shape) return;
    stop();

    m_currentType = AnimationType::Rotate;
    m_animParams.angleDeg = angleDeg;
    m_animParams.anchor = anchor;
    m_animParams.startCenter = m_shape->center();
    m_animParams.lastAngle = 0.0;

    m_animation = new QVariantAnimation(this);
    m_animation->setDuration(m_duration);
    m_animation->setEasingCurve(m_easingCurve);
    m_animation->setStartValue(0.0);
    m_animation->setEndValue(1.0);

    connect(m_animation, &QVariantAnimation::valueChanged,
            this, &ShapeAnimator::onAnimationValueChanged);
    connect(m_animation, &QVariantAnimation::finished,
            this, &ShapeAnimator::onAnimationFinished);

    m_animation->start(QAbstractAnimation::DeleteWhenStopped);
    emit started();
}

void ShapeAnimator::startScale(double factor, const QPointF &anchor)
{
    if (!m_shape) return;
    stop();

    m_currentType = AnimationType::Scale;
    m_animParams.factor = factor;
    m_animParams.anchor = anchor;
    m_animParams.startCenter = m_shape->center();
    m_animParams.lastFactor = 1.0;

    m_animation = new QVariantAnimation(this);
    m_animation->setDuration(m_duration);
    m_animation->setEasingCurve(m_easingCurve);
    m_animation->setStartValue(0.0);
    m_animation->setEndValue(1.0);

    connect(m_animation, &QVariantAnimation::valueChanged,
            this, &ShapeAnimator::onAnimationValueChanged);
    connect(m_animation, &QVariantAnimation::finished,
            this, &ShapeAnimator::onAnimationFinished);

    m_animation->start(QAbstractAnimation::DeleteWhenStopped);
    emit started();
}

void ShapeAnimator::stop()
{
    if (m_animation && m_animation->state() == QAbstractAnimation::Running) {
        m_animation->stop();
    }
    m_animation = nullptr;
    m_currentType = AnimationType::None;
}

bool ShapeAnimator::isRunning() const
{
    return m_animation && m_animation->state() == QAbstractAnimation::Running;
}

void ShapeAnimator::onAnimationValueChanged(const QVariant &value)
{
    double progress = value.toDouble();
    emit progressChanged(progress);

    if (!m_shape) return;

    switch (m_currentType) {
    case AnimationType::Translate:
        applyTranslateStep(progress);
        break;
    case AnimationType::Rotate:
        applyRotateStep(progress);
        break;
    case AnimationType::Scale:
        applyScaleStep(progress);
        break;
    default:
        break;
    }

    emit step();
}

void ShapeAnimator::onAnimationFinished()
{
    m_currentType = AnimationType::None;
    m_animation = nullptr;
    emit finished();
}

void ShapeAnimator::applyTranslateStep(double progress)
{
    if (!m_shape) return;

    double currentDx = m_animParams.dx * progress;
    double currentDy = m_animParams.dy * progress;

    double deltaX = currentDx - m_animParams.lastAppliedTranslate.x();
    double deltaY = currentDy - m_animParams.lastAppliedTranslate.y();

    m_shape->translate(deltaX, deltaY);
    m_animParams.lastAppliedTranslate = QPointF(currentDx, currentDy);

    if (progress >= 1.0) {
        m_animParams.lastAppliedTranslate = QPointF(0, 0);
    }
}

void ShapeAnimator::applyRotateStep(double progress)
{
    if (!m_shape) return;

    double currentAngle = m_animParams.angleDeg * progress;
    double deltaAngle = currentAngle - m_animParams.lastAngle;

    m_shape->rotate(deltaAngle, m_animParams.anchor);
    m_animParams.lastAngle = currentAngle;

    if (progress >= 1.0) {
        m_animParams.lastAngle = 0.0;
    }
}

void ShapeAnimator::applyScaleStep(double progress)
{
    if (!m_shape) return;

    double currentFactor = 1.0 + (m_animParams.factor - 1.0) * progress;
    double relativeFactor = currentFactor / m_animParams.lastFactor;

    m_shape->scale(relativeFactor, m_animParams.anchor);
    m_animParams.lastFactor = currentFactor;

    if (progress >= 1.0) {
        m_animParams.lastFactor = 1.0;
    }
}