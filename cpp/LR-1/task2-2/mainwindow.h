#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QLineEdit>
#include <QSlider>
#include <QLabel>
#include <QSharedPointer>
#include "canvas.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onAddCircle();
    void onAddTriangle();
    void onAddRectangle();
    void onAddSquare();
    void onAddRhombus();
    void onAddStar();
    void onAddHexagon();
    void onAddEllipse();
    void onShapeSelected(int row);
    void onMoveShape();
    void onRotateShape();
    void onScaleShape();
    void onDeleteShape();
    void onClearAll();
    void onDurationChanged(int value);

private:
    Canvas* m_canvas;
    QListWidget* m_shapeList;
    QLineEdit* m_moveDx, * m_moveDy, * m_rotateAngle, * m_scaleFactor;
    QSlider* m_durationSlider;
    QLabel* m_durationLabel;

    void updateShapeList();
    void showWarning(const QString& message);
    bool getSelectedShape(QSharedPointer<Shape>& shape);
    QString normalizeDecimalString(const QString& input);
};

#endif // MAINWINDOW_H