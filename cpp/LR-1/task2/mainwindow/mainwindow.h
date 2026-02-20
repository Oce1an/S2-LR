#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <memory>
#include "../shapemanager/shapemanager.h"

QT_BEGIN_NAMESPACE
class QPushButton;
class QComboBox;
class QSpinBox;
class QDoubleSpinBox;
class QLabel;
class QGroupBox;
class QListWidget;
class QTextEdit;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    std::unique_ptr<ShapeManager> shapeManager;
    QTimer* animationTimer;
    QLabel* canvasLabel;
    QListWidget* shapesList;
    QTextEdit* infoDisplay;

    // Текущая выбранная фигура
    int selectedShapeIndex;
    Point lastMousePos;
    bool isDragging;

    // UI элементы
    void setupUI();
    void updateCanvas();
    void updateShapesList();
    void updateInfoDisplay();

protected:
    // Объявление eventFilter
    bool eventFilter(QObject* obj, QEvent* event) override;

private slots:
    // Создание фигур
    void onCreateTriangle();
    void onCreateCircle();
    void onCreateRectangle();
    void onCreateSquare();
    void onCreateRhombus();
    void onCreateHexagon();
    void onCreateStar();
    void onCreateEllipse();

    // Управление фигурами
    void onShapeSelected(int index);
    void onDeleteShape();
    void onClearAll();

    // Трансформации
    void onMoveShape();
    void onRotateShape();
    void onScaleShape();
    void onStartAnimation();

    // События мыши
    void onCanvasMousePress(QMouseEvent* event);
    void onCanvasMouseMove(QMouseEvent* event);
    void onCanvasMouseRelease(QMouseEvent* event);

    // Таймер анимации
    void onAnimationTimer();

    // Обработка сигналов от фигур
    void onShapeAnimationStarted();
    void onShapeAnimationStep();
    void onShapeAnimationFinished();

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
};

#endif // MAINWINDOW_H