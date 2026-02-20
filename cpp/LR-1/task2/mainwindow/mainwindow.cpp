#include "mainwindow.h"
#include "../triangle/triangle.h"
#include "../circle/circle.h"
#include "../rectangle/rectangle.h"
#include "../square/square.h"
#include "../rhombus/rhombus.h"
#include "../hexagon/hexagon.h"
#include "../star/star.h"
#include "../customshape/customshape.h"

#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QListWidget>
#include <QTextEdit>
#include <QMouseEvent>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , shapeManager(std::make_unique<ShapeManager>())
    , animationTimer(new QTimer(this))
    , selectedShapeIndex(-1)
    , isDragging(false) {

    setupUI();

    animationTimer->setInterval(20); // 50 FPS
    connect(animationTimer, &QTimer::timeout, this, &MainWindow::onAnimationTimer);
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    setWindowTitle("Geometric Shapes");
    setMinimumSize(1000, 700);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    // Левая панель - канва для рисования
    QGroupBox* canvasGroup = new QGroupBox("Canvas");
    QVBoxLayout* canvasLayout = new QVBoxLayout(canvasGroup);

    canvasLabel = new QLabel();
    canvasLabel->setMinimumSize(600, 500);
    canvasLabel->setStyleSheet("border: 2px solid black; background-color: white;");
    canvasLabel->setAlignment(Qt::AlignCenter);
    canvasLabel->setMouseTracking(true);
    canvasLayout->addWidget(canvasLabel);

    mainLayout->addWidget(canvasGroup, 2);

    // Правая панель - управление
    QGroupBox* controlGroup = new QGroupBox("Controls");
    QVBoxLayout* controlLayout = new QVBoxLayout(controlGroup);
    controlGroup->setFixedWidth(350);

    // Секция создания фигур
    QGroupBox* createGroup = new QGroupBox("Create Shape");
    QGridLayout* createLayout = new QGridLayout(createGroup);

    QPushButton* createTriangleBtn = new QPushButton("Triangle");
    QPushButton* createCircleBtn = new QPushButton("Circle");
    QPushButton* createRectangleBtn = new QPushButton("Rectangle");
    QPushButton* createSquareBtn = new QPushButton("Square");
    QPushButton* createRhombusBtn = new QPushButton("Rhombus");
    QPushButton* createHexagonBtn = new QPushButton("Hexagon");
    QPushButton* createStarBtn = new QPushButton("Star");
    QPushButton* createEllipseBtn = new QPushButton("Ellipse");

    createLayout->addWidget(createTriangleBtn, 0, 0);
    createLayout->addWidget(createCircleBtn, 0, 1);
    createLayout->addWidget(createRectangleBtn, 1, 0);
    createLayout->addWidget(createSquareBtn, 1, 1);
    createLayout->addWidget(createRhombusBtn, 2, 0);
    createLayout->addWidget(createHexagonBtn, 2, 1);
    createLayout->addWidget(createStarBtn, 3, 0);
    createLayout->addWidget(createEllipseBtn, 3, 1);

    connect(createTriangleBtn, &QPushButton::clicked, this, &MainWindow::onCreateTriangle);
    connect(createCircleBtn, &QPushButton::clicked, this, &MainWindow::onCreateCircle);
    connect(createRectangleBtn, &QPushButton::clicked, this, &MainWindow::onCreateRectangle);
    connect(createSquareBtn, &QPushButton::clicked, this, &MainWindow::onCreateSquare);
    connect(createRhombusBtn, &QPushButton::clicked, this, &MainWindow::onCreateRhombus);
    connect(createHexagonBtn, &QPushButton::clicked, this, &MainWindow::onCreateHexagon);
    connect(createStarBtn, &QPushButton::clicked, this, &MainWindow::onCreateStar);
    connect(createEllipseBtn, &QPushButton::clicked, this, &MainWindow::onCreateEllipse);

    controlLayout->addWidget(createGroup);

    // Список фигур
    QGroupBox* listGroup = new QGroupBox("Shapes List");
    QVBoxLayout* listLayout = new QVBoxLayout(listGroup);

    shapesList = new QListWidget();
    shapesList->setMaximumHeight(150);
    listLayout->addWidget(shapesList);

    QHBoxLayout* listButtonsLayout = new QHBoxLayout();
    QPushButton* deleteBtn = new QPushButton("Delete Selected");
    QPushButton* clearBtn = new QPushButton("Clear All");
    listButtonsLayout->addWidget(deleteBtn);
    listButtonsLayout->addWidget(clearBtn);
    listLayout->addLayout(listButtonsLayout);

    connect(shapesList, &QListWidget::currentRowChanged, this, &MainWindow::onShapeSelected);
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::onDeleteShape);
    connect(clearBtn, &QPushButton::clicked, this, &MainWindow::onClearAll);

    controlLayout->addWidget(listGroup);

    // Секция трансформаций
    QGroupBox* transformGroup = new QGroupBox("Transformations");
    QVBoxLayout* transformLayout = new QVBoxLayout(transformGroup);

    // Перемещение
    QHBoxLayout* moveLayout = new QHBoxLayout();
    moveLayout->addWidget(new QLabel("Move to:"));
    QSpinBox* moveX = new QSpinBox();
    moveX->setRange(-1000, 1000);
    moveX->setValue(300);
    QSpinBox* moveY = new QSpinBox();
    moveY->setRange(-1000, 1000);
    moveY->setValue(250);
    moveLayout->addWidget(moveX);
    moveLayout->addWidget(moveY);
    QPushButton* moveBtn = new QPushButton("Move");
    moveLayout->addWidget(moveBtn);
    transformLayout->addLayout(moveLayout);

    // Поворот
    QHBoxLayout* rotateLayout = new QHBoxLayout();
    rotateLayout->addWidget(new QLabel("Rotate:"));
    QDoubleSpinBox* rotateAngle = new QDoubleSpinBox();
    rotateAngle->setRange(-360, 360);
    rotateAngle->setValue(45);
    rotateAngle->setSuffix("o");
    rotateLayout->addWidget(rotateAngle);
    QPushButton* rotateBtn = new QPushButton("Rotate");
    rotateLayout->addWidget(rotateBtn);
    transformLayout->addLayout(rotateLayout);

    // Масштабирование
    QHBoxLayout* scaleLayout = new QHBoxLayout();
    scaleLayout->addWidget(new QLabel("Scale:"));
    QDoubleSpinBox* scaleFactor = new QDoubleSpinBox();
    scaleFactor->setRange(0.1, 5.0);
    scaleFactor->setValue(1.5);
    scaleFactor->setSingleStep(0.1);
    scaleLayout->addWidget(scaleFactor);
    QPushButton* scaleBtn = new QPushButton("Scale");
    scaleLayout->addWidget(scaleBtn);
    transformLayout->addLayout(scaleLayout);

    // Анимация
    QHBoxLayout* animLayout = new QHBoxLayout();
    QPushButton* startAnimBtn = new QPushButton("Start Animation");
    animLayout->addWidget(startAnimBtn);
    transformLayout->addLayout(animLayout);

    controlLayout->addWidget(transformGroup);

    // Информация о фигуре
    QGroupBox* infoGroup = new QGroupBox("Shape Info");
    QVBoxLayout* infoLayout = new QVBoxLayout(infoGroup);

    infoDisplay = new QTextEdit();
    infoDisplay->setReadOnly(true);
    infoDisplay->setMaximumHeight(150);
    infoLayout->addWidget(infoDisplay);

    controlLayout->addWidget(infoGroup);
    controlLayout->addStretch();

    mainLayout->addWidget(controlGroup);

    // Подключение сигналов для трансформаций
    connect(moveBtn, &QPushButton::clicked, [this, moveX, moveY]() {
        onMoveShape();
        // Здесь нужно передать значения из spinbox'ов
        });

    connect(rotateBtn, &QPushButton::clicked, [this, rotateAngle]() {
        onRotateShape();
        });

    connect(scaleBtn, &QPushButton::clicked, [this, scaleFactor]() {
        onScaleShape();
        });

    connect(startAnimBtn, &QPushButton::clicked, this, &MainWindow::onStartAnimation);

    // Обработка событий мыши
    canvasLabel->installEventFilter(this);
}

void MainWindow::onCreateTriangle() {
    auto triangle = std::make_shared<Triangle>();
    triangle->setColor(QColor(255, 200, 200));
    shapeManager->addShape(triangle);
    updateShapesList();
    updateCanvas();
}

void MainWindow::onCreateCircle() {
    auto circle = std::make_shared<Circle>(Point(300, 250), 50);
    circle->setColor(QColor(200, 255, 200));
    shapeManager->addShape(circle);
    updateShapesList();
    updateCanvas();
}

void MainWindow::onCreateRectangle() {
    auto rect = std::make_shared<Rectangle>(Point(300, 250), 100, 60);
    rect->setColor(QColor(200, 200, 255));
    shapeManager->addShape(rect);
    updateShapesList();
    updateCanvas();
}

void MainWindow::onCreateSquare() {
    auto square = std::make_shared<Square>(Point(300, 250), 80);
    square->setColor(QColor(255, 255, 200));
    shapeManager->addShape(square);
    updateShapesList();
    updateCanvas();
}

void MainWindow::onCreateRhombus() {
    auto rhombus = std::make_shared<Rhombus>(Point(300, 250), 120, 80);
    rhombus->setColor(QColor(255, 200, 255));
    shapeManager->addShape(rhombus);
    updateShapesList();
    updateCanvas();
}

void MainWindow::onCreateHexagon() {
    auto hexagon = std::make_shared<Hexagon>(Point(300, 250), 60);
    hexagon->setColor(QColor(200, 255, 255));
    shapeManager->addShape(hexagon);
    updateShapesList();
    updateCanvas();
}

void MainWindow::onCreateStar() {
    auto star = std::make_shared<Star>(Point(300, 250), 5, 80, 40);
    star->setColor(QColor(255, 200, 150));
    shapeManager->addShape(star);
    updateShapesList();
    updateCanvas();
}

void MainWindow::onCreateEllipse() {
    auto ellipse = std::make_shared<Ellipse>(Point(300, 250), 80, 50);
    ellipse->setColor(QColor(200, 150, 255));
    shapeManager->addShape(ellipse);
    updateShapesList();
    updateCanvas();
}

void MainWindow::onShapeSelected(int index) {
    selectedShapeIndex = index;
    updateInfoDisplay();
}

void MainWindow::onDeleteShape() {
    if (selectedShapeIndex >= 0) {
        shapeManager->removeShape(selectedShapeIndex);
        selectedShapeIndex = -1;
        updateShapesList();
        updateCanvas();
        infoDisplay->clear();
    }
}

void MainWindow::onClearAll() {
    shapeManager->clearShapes();
    selectedShapeIndex = -1;
    shapesList->clear();
    updateCanvas();
    infoDisplay->clear();
}

void MainWindow::onMoveShape() {
    // Реализация перемещения
    if (selectedShapeIndex >= 0) {
        auto shape = shapeManager->getShape(selectedShapeIndex);
        // shape->moveTo(target, 1000);
    }
}

void MainWindow::onRotateShape() {
    // Реализация поворота
    if (selectedShapeIndex >= 0) {
        auto shape = shapeManager->getShape(selectedShapeIndex);
        // shape->rotateTo(angle * M_PI / 180, 1000);
    }
}

void MainWindow::onScaleShape() {
    // Реализация масштабирования
    if (selectedShapeIndex >= 0) {
        auto shape = shapeManager->getShape(selectedShapeIndex);
        // shape->scaleTo(factor, 1000);
    }
}

void MainWindow::onStartAnimation() {
    if (selectedShapeIndex >= 0) {
        auto shape = shapeManager->getShape(selectedShapeIndex);

        // Подключаем сигналы
        connect(shape.get(), &Shape::animationStarted, this, &MainWindow::onShapeAnimationStarted);
        connect(shape.get(), &Shape::animationStep, this, &MainWindow::onShapeAnimationStep);
        connect(shape.get(), &Shape::animationFinished, this, &MainWindow::onShapeAnimationFinished);

        // Запускаем комбинированную анимацию
        shape->transformTo(Point(400, 300), M_PI, 2.0, 2000);
    }
}

void MainWindow::onCanvasMousePress(QMouseEvent* event) {
    if (!canvasLabel) return;

    QPoint pos = event->pos();
    Point p(pos.x(), pos.y());

    int index = shapeManager->findShapeAtPoint(p);
    if (index >= 0) {
        selectedShapeIndex = index;
        shapesList->setCurrentRow(index);
        lastMousePos = p;
        isDragging = true;
    }
}

void MainWindow::onCanvasMouseMove(QMouseEvent* event) {
    if (isDragging && selectedShapeIndex >= 0) {
        QPoint pos = event->pos();
        Point currentPos(pos.x(), pos.y());

        Point delta = currentPos - lastMousePos;
        auto shape = shapeManager->getShape(selectedShapeIndex);
        Point newCenter = shape->getCenter() + delta;
        shape->setCenter(newCenter);

        lastMousePos = currentPos;
        updateCanvas();
        updateInfoDisplay();
    }
}

void MainWindow::onCanvasMouseRelease(QMouseEvent* event) {
    isDragging = false;
}

void MainWindow::onAnimationTimer() {
    updateCanvas();
}

void MainWindow::onShapeAnimationStarted() {
    animationTimer->start();
}

void MainWindow::onShapeAnimationStep() {
    updateCanvas();
    updateInfoDisplay();
}

void MainWindow::onShapeAnimationFinished() {
    animationTimer->stop();

    // Отключаем сигналы
    if (selectedShapeIndex >= 0) {
        auto shape = shapeManager->getShape(selectedShapeIndex);
        disconnect(shape.get(), nullptr, this, nullptr);
    }
}

void MainWindow::updateCanvas() {
    if (!canvasLabel) return;

    QPixmap pixmap(canvasLabel->size());
    pixmap.fill(Qt::white);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    // Рисуем сетку для ориентира
    painter.setPen(QPen(Qt::lightGray, 1, Qt::DotLine));
    for (int x = 0; x < pixmap.width(); x += 50) {
        painter.drawLine(x, 0, x, pixmap.height());
    }
    for (int y = 0; y < pixmap.height(); y += 50) {
        painter.drawLine(0, y, pixmap.width(), y);
    }

    // Рисуем все фигуры
    shapeManager->drawAll(painter);

    // Если выбрана фигура, рисуем рамку
    if (selectedShapeIndex >= 0) {
        auto shape = shapeManager->getShape(selectedShapeIndex);
        Point c = shape->getCenter();

        painter.setPen(QPen(Qt::red, 2, Qt::DashLine));
        painter.setBrush(Qt::NoBrush);
        painter.drawEllipse(QPointF(c.x, c.y), 5, 5);
    }

    canvasLabel->setPixmap(pixmap);
}

void MainWindow::updateShapesList() {
    shapesList->clear();

    for (int i = 0; i < shapeManager->getShapeCount(); ++i) {
        QString name;
        auto shape = shapeManager->getShape(i);

        // Определяем тип фигуры (упрощенно)
        if (dynamic_cast<Triangle*>(shape.get())) name = "Triangle";
        else if (dynamic_cast<Circle*>(shape.get())) name = "Circle";
        else if (dynamic_cast<Rectangle*>(shape.get())) name = "Rectangle";
        else if (dynamic_cast<Square*>(shape.get())) name = "Square";
        else if (dynamic_cast<Rhombus*>(shape.get())) name = "Rhombus";
        else if (dynamic_cast<Hexagon*>(shape.get())) name = "Hexagon";
        else if (dynamic_cast<Star*>(shape.get())) name = "Star";
        else if (dynamic_cast<Ellipse*>(shape.get())) name = "Ellipse";
        else name = "Shape";

        name += QString(" #%1").arg(i + 1);
        shapesList->addItem(name);
    }

    if (selectedShapeIndex >= 0 && selectedShapeIndex < shapesList->count()) {
        shapesList->setCurrentRow(selectedShapeIndex);
    }
}

void MainWindow::updateInfoDisplay() {
    if (selectedShapeIndex >= 0) {
        infoDisplay->setText(shapeManager->getShapeInfo(selectedShapeIndex));
    }
    else {
        infoDisplay->clear();
    }
}

// Переопределение eventFilter для обработки событий мыши
bool MainWindow::eventFilter(QObject* obj, QEvent* event) {
    if (obj == canvasLabel) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

        switch (event->type()) {
        case QEvent::MouseButtonPress:
            onCanvasMousePress(mouseEvent);
            break;
        case QEvent::MouseMove:
            onCanvasMouseMove(mouseEvent);
            break;
        case QEvent::MouseButtonRelease:
            onCanvasMouseRelease(mouseEvent);
            break;
        default:
            break;
        }
    }

    return QMainWindow::eventFilter(obj, event);
}