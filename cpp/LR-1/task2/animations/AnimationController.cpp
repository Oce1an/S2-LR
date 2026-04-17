#include "AnimationController.h"

AnimationController::AnimationController(QObject *parent)
    : QObject(parent)
    , m_parallelGroup(nullptr)
    , m_sequentialGroup(nullptr)
{
}

AnimationController::~AnimationController()
{
    stopAll();
    clear();
}

void AnimationController::addAnimator(ShapeAnimator *animator)
{
    if (!m_animators.contains(animator)) {
        m_animators.append(animator);
    }
}

void AnimationController::removeAnimator(ShapeAnimator *animator)
{
    m_animators.removeOne(animator);
}

void AnimationController::clear()
{
    stopAll();
    m_animators.clear();
}

void AnimationController::startAllParallel(int durationMs)
{
    stopAll();

    if (m_animators.isEmpty()) return;

    m_parallelGroup = new QParallelAnimationGroup(this);

    for (ShapeAnimator *animator : m_animators) {
        if (!animator->shape()) continue;

        // Создаём анимацию для каждого аниматора
        // Здесь нужно знать тип анимации, которую запускать
        // Для упрощения - запускаем translate на 50,50 (можно расширить)
        // В реальном приложении нужно хранить параметры для каждого
        
        // Это заглушка - в полной версии нужно передавать параметры
    }

    connect(m_parallelGroup, &QParallelAnimationGroup::finished,
            this, &AnimationController::onGroupFinished);

    m_parallelGroup->start();
}

void AnimationController::startAllSequential(int durationMs)
{
    stopAll();

    if (m_animators.isEmpty()) return;

    m_sequentialGroup = new QSequentialAnimationGroup(this);

    // Аналогично parallel, но добавляем последовательно

    connect(m_sequentialGroup, &QSequentialAnimationGroup::finished,
            this, &AnimationController::onGroupFinished);

    m_sequentialGroup->start();
}

void AnimationController::stopAll()
{
    if (m_parallelGroup) {
        m_parallelGroup->stop();
        delete m_parallelGroup;
        m_parallelGroup = nullptr;
    }
    if (m_sequentialGroup) {
        m_sequentialGroup->stop();
        delete m_sequentialGroup;
        m_sequentialGroup = nullptr;
    }
    for (ShapeAnimator *animator : m_animators) {
        animator->stop();
    }
}

void AnimationController::setDuration(int ms)
{
    for (ShapeAnimator *animator : m_animators) {
        animator->setDuration(ms);
    }
}

void AnimationController::onGroupFinished()
{
    emit allFinished();
}