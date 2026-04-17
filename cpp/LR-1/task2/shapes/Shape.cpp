#include "Shape.h"
#include <cmath>

Shape::Shape(QObject *parent) : QObject(parent) {}

void Shape::moveCenter(double dx, double dy)
{
    translate(dx, dy);
}

void Shape::setAnimationValue(double value)
{
    if (qFuzzyCompare(m_animProgress, value))
        return;
    m_animProgress = value;
    applyAnimationStep(value);
    emit animationValueChanged();
    emit transformed();
}

void Shape::animateTranslate(double dx, double dy, int durationMs)
{
    if (m_animation && m_animation->state() == QAbstractAnimation::Running)
        m_animation->stop();
    
    m_animData.type = AnimationType::Translate;
    m_animData.dx = dx;
    m_animData.dy = dy;
    
    m_animation = new QVariantAnimation(this);
    m_animation->setDuration(durationMs);
    m_animation->setStartValue(0.0);
    m_animation->setEndValue(1.0);
    
    connect(m_animation, &QVariantAnimation::valueChanged, this, [this](const QVariant &val){
        setAnimationValue(val.toDouble());
    });
    
    connect(m_animation, &QVariantAnimation::finished, this, [this](){
        emit animationFinished();
        m_animData.type = AnimationType::None;
    });
    
    m_animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void Shape::animateRotate(double angleDeg, const QPointF &anchor, int durationMs)
{
    if (m_animation && m_animation->state() == QAbstractAnimation::Running)
        m_animation->stop();
    
    m_animData.type = AnimationType::Rotate;
    m_animData.angleDeg = angleDeg;
    m_animData.anchor = anchor;
    
    m_animation = new QVariantAnimation(this);
    m_animation->setDuration(durationMs);
    m_animation->setStartValue(0.0);
    m_animation->setEndValue(1.0);
    
    connect(m_animation, &QVariantAnimation::valueChanged, this, [this](const QVariant &val){
        setAnimationValue(val.toDouble());
    });
    
    connect(m_animation, &QVariantAnimation::finished, this, [this](){
        emit animationFinished();
        m_animData.type = AnimationType::None;
    });
    
    m_animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void Shape::animateScale(double factor, const QPointF &anchor, int durationMs)
{
    if (m_animation && m_animation->state() == QAbstractAnimation::Running)
        m_animation->stop();
    
    m_animData.type = AnimationType::Scale;
    m_animData.factor = factor;
    m_animData.anchor = anchor;
    
    m_animation = new QVariantAnimation(this);
    m_animation->setDuration(durationMs);
    m_animation->setStartValue(0.0);
    m_animation->setEndValue(1.0);
    
    connect(m_animation, &QVariantAnimation::valueChanged, this, [this](const QVariant &val){
        setAnimationValue(val.toDouble());
    });
    
    connect(m_animation, &QVariantAnimation::finished, this, [this](){
        emit animationFinished();
        m_animData.type = AnimationType::None;
    });
    
    m_animation->start(QAbstractAnimation::DeleteWhenStopped);
}