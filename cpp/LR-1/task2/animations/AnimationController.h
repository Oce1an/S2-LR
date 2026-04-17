#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include <QObject>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>
#include "ShapeAnimator.h"

class AnimationController : public QObject
{
    Q_OBJECT
public:
    explicit AnimationController(QObject *parent = nullptr);
    ~AnimationController();

    // Добавить аниматор
    void addAnimator(ShapeAnimator *animator);
    void removeAnimator(ShapeAnimator *animator);
    void clear();

    // Запуск всех анимаций параллельно
    void startAllParallel(int durationMs = -1);

    // Запуск всех анимаций последовательно
    void startAllSequential(int durationMs = -1);

    // Остановка всех
    void stopAll();

    // Настройка длительности для всех
    void setDuration(int ms);

signals:
    void allFinished();

private slots:
    void onGroupFinished();

private:
    QList<ShapeAnimator*> m_animators;
    QParallelAnimationGroup *m_parallelGroup;
    QSequentialAnimationGroup *m_sequentialGroup;
};

#endif // ANIMATIONCONTROLLER_H