#include "shape.h"

Shape::Shape()
    : center(0, 0)
    , rotationAngle(0)
    , scale(1.0)
    , color(Qt::blue)
    , pen(Qt::black, 2)
    , animationTimer(nullptr)
    , targetPosition(0, 0)
    , targetRotation(0)
    , targetScale(1.0)
    , animationSteps(0)
    , currentStep(0)
    , isAnimating(false) {

    pen.setCosmetic(true);
}

Shape::~Shape() {
    if (animationTimer) {
        animationTimer->stop();
        delete animationTimer;
    }
}

void Shape::setCenter(const Point& newCenter) {
    center = newCenter;
}

void Shape::setRotation(double angle) {
    rotationAngle = angle;
}

void Shape::setScale(double s) {
    scale = s;
}

void Shape::moveTo(const Point& target, int durationMs) {
    targetPosition = target;
    animationSteps = durationMs / 20; // 50 FPS
    currentStep = 0;
    isAnimating = true;

    if (!animationTimer) {
        animationTimer = new QTimer(this);
        connect(animationTimer, &QTimer::timeout, this, &Shape::onAnimationTimer);
    }

    animationTimer->start(20); // 50 FPS
    emit animationStarted();
}

void Shape::rotateTo(double angle, int durationMs) {
    targetRotation = angle;
    animationSteps = durationMs / 20;
    currentStep = 0;
    isAnimating = true;

    if (!animationTimer) {
        animationTimer = new QTimer(this);
        connect(animationTimer, &QTimer::timeout, this, &Shape::onAnimationTimer);
    }

    animationTimer->start(20);
    emit animationStarted();
}

void Shape::scaleTo(double s, int durationMs) {
    targetScale = s;
    animationSteps = durationMs / 20;
    currentStep = 0;
    isAnimating = true;

    if (!animationTimer) {
        animationTimer = new QTimer(this);
        connect(animationTimer, &QTimer::timeout, this, &Shape::onAnimationTimer);
    }

    animationTimer->start(20);
    emit animationStarted();
}

void Shape::transformTo(const Point& target, double angle, double s, int durationMs) {
    targetPosition = target;
    targetRotation = angle;
    targetScale = s;
    animationSteps = durationMs / 20;
    currentStep = 0;
    isAnimating = true;

    if (!animationTimer) {
        animationTimer = new QTimer(this);
        connect(animationTimer, &QTimer::timeout, this, &Shape::onAnimationTimer);
    }

    animationTimer->start(20);
    emit animationStarted();
}

void Shape::stopAnimation() {
    if (animationTimer) {
        animationTimer->stop();
    }
    isAnimating = false;
    emit animationFinished();
}

void Shape::onAnimationTimer() {
    if (currentStep < animationSteps) {
        currentStep++;

        // Линейная интерполяция
        double t = static_cast<double>(currentStep) / animationSteps;

        // Для позиции
        Point delta = targetPosition - center;
        center = center + delta * t;

        // Для поворота
        double angleDelta = targetRotation - rotationAngle;
        rotationAngle += angleDelta * t;

        // Для масштаба
        double scaleDelta = targetScale - scale;
        scale += scaleDelta * t;

        applyTransformations();
        emit animationStep();
    }
    else {
        // Завершение анимации
        center = targetPosition;
        rotationAngle = targetRotation;
        scale = targetScale;
        applyTransformations();

        animationTimer->stop();
        isAnimating = false;
        emit animationFinished();
    }
}