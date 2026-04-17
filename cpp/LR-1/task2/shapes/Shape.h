#ifndef SHAPE_H
#define SHAPE_H

class Shape : public QObject
{
	Q_OBJECT
	Q_PROPERTY(double animationValue READ animationValue WRITE setAnimationValue NOTIFY animationValueChanged)

public:
	explicit Shape(QObject* parent = nullptr);
	virtual ~Shape() = default;

	virtual double area() const = 0;
	virtual double perimeter() const = 0;
	virtual QPointF center() const = 0;

	virtual void translate(double dx, double dy) = 0;
	virtual void rotate(double angleDeg, const QPointF& anchor) = 0;
	virtual void scale(double factor, const QPointF& anchor) = 0;

	virtual void moveCenter(double dx, double dy);

	void animateTranslate(double dx, double dy, int duration);
	void animateRotate(double angleDeg, const QPointF& anchor, int durationMs);
	void animateScale(double factor, const QPointF& anchor, int durationMs);
	 
	virtual void draw(QPainter &painter) const = 0;

	double animationValue() const { return m_animProgress; }
	void setAnimationValue(double value);

signals:
	void transformed();
	void animationFinished();
	void animationValueChanged();

protected:
	virtual void applyAnimationStep(double progress) = 0;

	struct
	{
		enum Type {None, Translate, Rotate, Scale};
		double dx, dy;
		double angleDeg;
		double factor;
		QPointF anchor;
		double startValue;

	} m_animData;

	double m_animProgress = 0.0;
	QVariantAnimation = *m_animation = nullptr;
};

#endif