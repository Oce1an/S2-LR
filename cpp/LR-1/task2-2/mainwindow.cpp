#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QMessageBox>
#include "shapes/circle.h"
#include "shapes/triangle.h"
#include "shapes/rectangle.h"
#include "shapes/square.h"
#include "shapes/rhombus.h"
#include "shapes/star.h"
#include "shapes/hexagon.h"
#include "shapes/ellipse.h"
#include "animations/rotateanimation.h"
#include "animations/moveanimation.h"
#include "animations/scaleanimation.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    QWidget* central = new QWidget(this);
    setCentralWidget(central);
    QHBoxLayout* mainLayout = new QHBoxLayout(central);

    // Левая панель: список фигур
    QVBoxLayout* leftLayout = new QVBoxLayout();
    m_shapeList = new QListWidget(this);
    m_shapeList->setMaximumWidth(200);
    connect(m_shapeList, &QListWidget::currentRowChanged, this, &MainWindow::onShapeSelected);
    leftLayout->addWidget(new QLabel("Shapes:"));
    leftLayout->addWidget(m_shapeList);

    QPushButton* deleteBtn = new QPushButton("Delete", this);
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::onDeleteShape);
    leftLayout->addWidget(deleteBtn);
    leftLayout->addStretch();
    mainLayout->addLayout(leftLayout);

    QPushButton* clearBtn = new QPushButton("Clear All", this);
    connect(clearBtn, &QPushButton::clicked, this, &MainWindow::onClearAll);
    leftLayout->addWidget(clearBtn);

    // Правая часть: холст и панели управления
    QVBoxLayout* rightLayout = new QVBoxLayout();

    // Холст
    m_canvas = new Canvas(this);
    m_canvas->setMinimumSize(600, 400);
    m_canvas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rightLayout->addWidget(m_canvas, 1);

    // Панель создания фигур
    QGroupBox* createGroup = new QGroupBox("Create Shape", this);
    QHBoxLayout* createLayout = new QHBoxLayout(createGroup);
    QPushButton* btnCircle = new QPushButton("Circle", this);
    QPushButton* btnTriangle = new QPushButton("Triangle", this);
    QPushButton* btnRectangle = new QPushButton("Rectangle", this);
    QPushButton* btnSquare = new QPushButton("Square", this);
    QPushButton* btnRhombus = new QPushButton("Rhombus", this);
    QPushButton* btnStar = new QPushButton("Star", this);
    QPushButton* btnHexagon = new QPushButton("Hexagon", this);
    QPushButton* btnEllipse = new QPushButton("Ellipse", this);

    connect(btnCircle, &QPushButton::clicked, this, &MainWindow::onAddCircle);
    connect(btnTriangle, &QPushButton::clicked, this, &MainWindow::onAddTriangle);
    connect(btnRectangle, &QPushButton::clicked, this, &MainWindow::onAddRectangle);
    connect(btnSquare, &QPushButton::clicked, this, &MainWindow::onAddSquare);
    connect(btnRhombus, &QPushButton::clicked, this, &MainWindow::onAddRhombus);
    connect(btnStar, &QPushButton::clicked, this, &MainWindow::onAddStar);
    connect(btnHexagon, &QPushButton::clicked, this, &MainWindow::onAddHexagon);
    connect(btnEllipse, &QPushButton::clicked, this, &MainWindow::onAddEllipse);

    createLayout->addWidget(btnCircle);
    createLayout->addWidget(btnTriangle);
    createLayout->addWidget(btnRectangle);
    createLayout->addWidget(btnSquare);
    createLayout->addWidget(btnRhombus);
    createLayout->addWidget(btnStar);
    createLayout->addWidget(btnHexagon);
    createLayout->addWidget(btnEllipse);
    rightLayout->addWidget(createGroup);

    // Панель управления выбранной фигурой
    QGroupBox* controlGroup = new QGroupBox("Shape Control", this);
    QFormLayout* controlLayout = new QFormLayout(controlGroup);
    QDoubleValidator* doubleValidator = new QDoubleValidator(this);
    doubleValidator->setNotation(QDoubleValidator::StandardNotation);
    doubleValidator->setLocale(QLocale::C);  // Используем C locale для точки

    m_moveDx = new QLineEdit(this);
    m_moveDy = new QLineEdit(this);
    m_moveDx->setValidator(doubleValidator);
    m_moveDy->setValidator(doubleValidator);
    m_moveDx->setText("0");
    m_moveDy->setText("0");
    QPushButton* btnMove = new QPushButton("Move", this);
    connect(btnMove, &QPushButton::clicked, this, &MainWindow::onMoveShape);

    m_rotateAngle = new QLineEdit(this);
    m_rotateAngle->setValidator(doubleValidator);
    m_rotateAngle->setText("0");
    QPushButton* btnRotate = new QPushButton("Rotate", this);
    connect(btnRotate, &QPushButton::clicked, this, &MainWindow::onRotateShape);

    m_scaleFactor = new QLineEdit(this);
    m_scaleFactor->setValidator(doubleValidator);
    m_scaleFactor->setText("1.0");
    QPushButton* btnScale = new QPushButton("Scale", this);
    connect(btnScale, &QPushButton::clicked, this, &MainWindow::onScaleShape);

    // Заменяем QSpinBox на QSlider
    m_durationSlider = new QSlider(Qt::Horizontal, this);
    m_durationSlider->setRange(100, 5000);
    m_durationSlider->setValue(1000);
    m_durationSlider->setTickInterval(100);
    m_durationSlider->setTickPosition(QSlider::TicksBelow);

    m_durationLabel = new QLabel("1000 ms", this);
    connect(m_durationSlider, &QSlider::valueChanged, this, &MainWindow::onDurationChanged);

    QHBoxLayout* durationLayout = new QHBoxLayout();
    durationLayout->addWidget(m_durationSlider);
    durationLayout->addWidget(m_durationLabel);

    controlLayout->addRow("dx:", m_moveDx);
    controlLayout->addRow("dy:", m_moveDy);
    controlLayout->addRow("", btnMove);
    controlLayout->addRow("Angle (deg):", m_rotateAngle);
    controlLayout->addRow("", btnRotate);
    controlLayout->addRow("Scale:", m_scaleFactor);
    controlLayout->addRow("", btnScale);
    controlLayout->addRow("Duration:", durationLayout);  // Добавляем горизонтальный layout
}

MainWindow::~MainWindow()
{
}

void MainWindow::onDurationChanged(int value)
{
    m_durationLabel->setText(QString("%1 ms").arg(value));
}

void MainWindow::onAddCircle()
{
    try {
        auto circle = QSharedPointer<Circle>::create(QPointF(200, 200), 50);
        // Используем static_cast для выбора правильной перегрузки update()
        connect(circle.data(), &Shape::shapeChanged, m_canvas, static_cast<void (QWidget::*)()>(&QWidget::update));
        m_canvas->addShape(circle);
        updateShapeList();
    }
    catch (const std::exception& e) {
        showWarning(e.what());
    }
}

void MainWindow::onAddTriangle()
{
    try {
        auto triangle = QSharedPointer<Triangle>::create(QPointF(100, 100), QPointF(200, 100), QPointF(150, 200));
        connect(triangle.data(), &Shape::shapeChanged, m_canvas, static_cast<void (QWidget::*)()>(&QWidget::update));
        m_canvas->addShape(triangle);
        updateShapeList();
    }
    catch (const std::exception& e) {
        showWarning(e.what());
    }
}

void MainWindow::onAddRectangle()
{
    try {
        auto rect = QSharedPointer<Rectangle>::create(QPointF(150, 150), 120, 80);
        connect(rect.data(), &Shape::shapeChanged, m_canvas, static_cast<void (QWidget::*)()>(&QWidget::update));
        m_canvas->addShape(rect);
        updateShapeList();
    }
    catch (const std::exception& e) {
        showWarning(e.what());
    }
}
    
void MainWindow::onAddSquare()
{
    try {
        auto square = QSharedPointer<Square>::create(QPointF(200, 200), 100);
        connect(square.data(), &Shape::shapeChanged, m_canvas, static_cast<void (QWidget::*)()>(&QWidget::update));
        m_canvas->addShape(square);
        updateShapeList();
    }
    catch (const std::exception& e) {
        showWarning(e.what());
    }
}

void MainWindow::onAddRhombus()
{
    try {
        auto rhombus = QSharedPointer<Rhombus>::create(QPointF(300, 300), 150, 80, 30);
        connect(rhombus.data(), &Shape::shapeChanged, m_canvas, static_cast<void (QWidget::*)()>(&QWidget::update));
        m_canvas->addShape(rhombus);
        updateShapeList();
    }
    catch (const std::exception& e) {
        showWarning(e.what());
    }
}

void MainWindow::onAddStar()
{
    try {
        auto star = QSharedPointer<Star>::create(QPointF(400, 200), 80, 40, 5, 0);
        connect(star.data(), &Shape::shapeChanged, m_canvas, static_cast<void (QWidget::*)()>(&QWidget::update));
        m_canvas->addShape(star);
        updateShapeList();
    }
    catch (const std::exception& e) {
        showWarning(e.what());
    }
}

void MainWindow::onAddHexagon()
{
    try {
        auto hex = QSharedPointer<Hexagon>::create(QPointF(500, 300), 70, 15);
        connect(hex.data(), &Shape::shapeChanged, m_canvas, static_cast<void (QWidget::*)()>(&QWidget::update));
        m_canvas->addShape(hex);
        updateShapeList();
    }
    catch (const std::exception& e) {
        showWarning(e.what());
    }
}

void MainWindow::onAddEllipse()
{
    try {
        auto ellipse = QSharedPointer<Ellipse>::create(QPointF(350, 400), 100, 50, 45);
        connect(ellipse.data(), &Shape::shapeChanged, m_canvas, static_cast<void (QWidget::*)()>(&QWidget::update));
        m_canvas->addShape(ellipse);
        updateShapeList();
    }
    catch (const std::exception& e) {
        showWarning(e.what());
    }
}

void MainWindow::onShapeSelected(int row)
{
    m_canvas->setSelectedIndex(row);
}

void MainWindow::onMoveShape()
{
    QSharedPointer<Shape> shape;
    if (!getSelectedShape(shape)) return;

    if (!shape) {
        showWarning("No shape selected");
        return;
    }

    bool ok1, ok2;
    // Заменяем запятую на точку для десятичного разделителя
    QString dxText = m_moveDx->text().replace(',', '.');
    QString dyText = m_moveDy->text().replace(',', '.');

    double dx = dxText.toDouble(&ok1);
    double dy = dyText.toDouble(&ok2);
    if (!ok1 || !ok2) {
        showWarning("Enter valid numbers for dx and dy");
        return;
    }

    MoveAnimation* anim = new MoveAnimation(shape.data(), dx, dy, m_durationSlider->value(), this);
    anim->start();
}

void MainWindow::onRotateShape()
{
    QSharedPointer<Shape> shape;
    if (!getSelectedShape(shape)) return;

    if (!shape) {
        showWarning("No shape selected");
        return;
    }

    bool ok;
    QString angleText = m_rotateAngle->text().replace(',', '.');
    double angle = angleText.toDouble(&ok);
    if (!ok) {
        showWarning("Enter a valid angle");
        return;
    }

    RotateAnimation* anim = new RotateAnimation(shape.data(), angle, shape->centerOfMass(), m_durationSlider->value(), this);
    anim->start();
}

void MainWindow::onScaleShape()
{
    QSharedPointer<Shape> shape;
    if (!getSelectedShape(shape)) return;

    if (!shape) {
        showWarning("No shape selected");
        return;
    }

    bool ok;
    QString factorText = normalizeDecimalString(m_scaleFactor->text());
    double factor = factorText.toDouble(&ok);
    if (!ok || factor <= 0) {
        showWarning("Enter a positive scale factor (e.g., 0.5 or 2.0)");
        return;
    }

    ScaleAnimation* anim = new ScaleAnimation(shape.data(), factor, shape->centerOfMass(), m_durationSlider->value(), this);
    anim->start();
}

void MainWindow::onDeleteShape()
{
    int row = m_canvas->selectedIndex();
    if (row >= 0) {
        m_canvas->removeShape(row);
        updateShapeList();

        // Если после удаления фигур не осталось, сбрасываем выделение в списке
        if (m_canvas->shapeCount() == 0) {
            m_shapeList->clearSelection();
        }
        else {
            // Иначе выделяем последнюю фигуру в списке
            m_shapeList->setCurrentRow(m_canvas->selectedIndex());
        }
    }
    // В конструкторе MainWindow после кнопки Delete:
}

void MainWindow::updateShapeList()
{
    m_shapeList->clear();
    for (int i = 0; i < m_canvas->shapeCount(); ++i) {
        auto shape = m_canvas->shapeAt(i);
        if (shape) {
            m_shapeList->addItem(QString("%1").arg(shape->typeName()));
        }
    }

    // Если фигур нет, сбрасываем выделение
    if (m_canvas->shapeCount() == 0) {
        m_canvas->setSelectedIndex(-1);
    }
}

void MainWindow::showWarning(const QString& message)
{
    QMessageBox::warning(this, "Error", message);
}

bool MainWindow::getSelectedShape(QSharedPointer<Shape>& shape)
{
    shape = m_canvas->selectedShape();
    if (!shape) {
        // Убираем предупреждение, если список пуст - это нормальная ситуация
        if (m_canvas->shapeCount() > 0) {
            showWarning("Select a shape from the list");
        }
        return false;
    }
    return true;
}
void MainWindow::onClearAll()
{
    m_canvas->clear();
    updateShapeList();
    m_shapeList->clearSelection();
}

// Добавьте этот метод в mainwindow.cpp
QString MainWindow::normalizeDecimalString(const QString& input)
{
    QString result = input.trimmed();
    // Заменяем запятую на точку
    result.replace(',', '.');
    // Удаляем лишние точки
    QStringList parts = result.split('.');
    if (parts.size() > 2) {
        // Если несколько точек, оставляем только первую
        result = parts[0] + "." + parts.mid(1).join("");
    }
    return result;
}