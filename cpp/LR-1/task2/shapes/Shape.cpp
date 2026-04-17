#include "Shape.h"
#include <cmath>

Shape::Shape(QObject *parent) : QObject(parent) {}

void Shape::moveCenter(double dx, double dy)
{
	translate(dx, dy);
}

void Shape::setAnimationValue(double value)
{
	if (qFuzzyCompare(m_anumProgress, value)
		return;
	m_animProgress = value;
	applyAnimationStep(value);
	emit animationValueChanged();
	emit transformed();
}