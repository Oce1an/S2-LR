#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QMessageBox>

#include "shapes/hdr/Circle.h"
#include "shapes/hdr/Hexagon.h"
#include "shapes/hdr/Rectangle.h"
#include "shapes/hdr/Rhombus.h"
#include "shapes/hdr/Square.h"
#include "shapes/hdr/Star.h"
#include "shapes/hdr/Trapezoid.h"
#include "shapes/hdr/Triangle.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Geometric Shapes with Animation");
    
    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    QHBoxLayout *mainLayout = new QHBoxLayout(central);
    
    m_canvas = new Canvas;
    mainLayout->addWidget(m_canvas, 1);
    
    QWidget *panel = new QWidget;
    QVBoxLayout *panelLayout = new QVBoxLayout(panel);
    panel->setFixedWidth(280);
    
    panelLayout->addWidget(new QLabel("Shape type:"));
    m_shapeTypeCombo = new QComboBox;
    m_shapeTypeCombo->addItems({"Rectangle", "Square", "Circle", "Triangle", "Star", "Hexagon", "Rhombus", "Trapezoid"});
    panelLayout->addWidget(m_shapeTypeCombo);
    
    QGroupBox *paramGroup = new QGroupBox("Parameters");
    QFormLayout *paramLayout = new QFormLayout(paramGroup);
    
    QDoubleSpinBox *param1 = new QDoubleSpinBox;
    param1->setRange(1.0, 500.0);
    param1->setValue(100.0);
    param1->setSingleStep(5.0);
    paramLayout->addRow("Param 1:", param1);
    
    QDoubleSpinBox *param2 = new QDoubleSpinBox;
    param2->setRange(1.0, 500.0);
    param2->setValue(80.0);
    param2->setSingleStep(5.0);
    paramLayout->addRow("Param 2:", param2);
    
    QDoubleSpinBox *param3 = new QDoubleSpinBox;
    param3->setRange(1.0, 500.0);
    param3->setValue(60.0);
    param3->setSingleStep(5.0);
    paramLayout->addRow("Param 3:", param3);
    
    m_paramSpins.append(param1);
    m_paramSpins.append(param2);
    m_paramSpins.append(param3);
    
    panelLayout->addWidget(paramGroup);
    
    connect(m_shapeTypeCombo, &QComboBox::currentTextChanged, this, &MainWindow::updateParamLabels);
    updateParamLabels(m_shapeTypeCombo->currentText());
    
    m_addBtn = new QPushButton("Add Shape");
    panelLayout->addWidget(m_addBtn);
    
    panelLayout->addWidget(new QLabel("Select shape:"));
    m_shapeListCombo = new QComboBox;
    panelLayout->addWidget(m_shapeListCombo);
    
    m_removeBtn = new QPushButton("Remove Selected");
    panelLayout->addWidget(m_removeBtn);
    
    QGroupBox *animGroup = new QGroupBox("Animation (duration 1000ms)");
    QVBoxLayout *animLayout = new QVBoxLayout(animGroup);
    m_translateBtn = new QPushButton("Translate (+50, +50)");
    m_rotateBtn = new QPushButton("Rotate 45° around center");
    m_scaleBtn = new QPushButton("Scale 1.5x around center");
    animLayout->addWidget(m_translateBtn);
    animLayout->addWidget(m_rotateBtn);
    animLayout->addWidget(m_scaleBtn);
    panelLayout->addWidget(animGroup);
    
    m_infoLabel = new QLabel;
    m_infoLabel->setWordWrap(true);
    panelLayout->addWidget(m_infoLabel);
    
    panelLayout->addStretch();
    mainLayout->addWidget(panel);
    
    connect(m_addBtn, &QPushButton::clicked, this, &MainWindow::onAddShape);
    connect(m_removeBtn, &QPushButton::clicked, this, &MainWindow::onRemoveSelected);
    connect(m_translateBtn, &QPushButton::clicked, this, &MainWindow::onAnimateTranslate);
    connect(m_rotateBtn, &QPushButton::clicked, this, &MainWindow::onAnimateRotate);
    connect(m_scaleBtn, &QPushButton::clicked, this, &MainWindow::onAnimateScale);
    connect(m_shapeListCombo, &QComboBox::currentIndexChanged, this, &MainWindow::onShapeSelected);
}

MainWindow::~MainWindow() {}

void MainWindow::updateParamLabels(const QString &shapeType)
{
    QFormLayout *layout = qobject_cast<QFormLayout*>(m_paramSpins[0]->parentWidget()->layout());
    if (!layout) return;
    
    for (auto spin : m_paramSpins) {
        spin->setVisible(false);
        QWidget *labelWidget = layout->labelForField(spin);
        if (labelWidget) {
            labelWidget->setVisible(false);
        }
    }
    
    auto getLabel = [layout](QWidget *field) -> QLabel* {
        return qobject_cast<QLabel*>(layout->labelForField(field));
    };
    
    if (shapeType == "Rectangle") {
        if (QLabel *lbl = getLabel(m_paramSpins[0])) lbl->setText("Width:");
        if (QLabel *lbl = getLabel(m_paramSpins[1])) lbl->setText("Height:");
        m_paramSpins[0]->setVisible(true);
        m_paramSpins[1]->setVisible(true);
        layout->labelForField(m_paramSpins[0])->setVisible(true);
        layout->labelForField(m_paramSpins[1])->setVisible(true);
        m_paramSpins[0]->setValue(120);
        m_paramSpins[1]->setValue(80);
    } else if (shapeType == "Square") {
        if (QLabel *lbl = getLabel(m_paramSpins[0])) lbl->setText("Side:");
        m_paramSpins[0]->setVisible(true);
        layout->labelForField(m_paramSpins[0])->setVisible(true);
        m_paramSpins[0]->setValue(100);
    } else if (shapeType == "Circle") {
        if (QLabel *lbl = getLabel(m_paramSpins[0])) lbl->setText("Radius:");
        m_paramSpins[0]->setVisible(true);
        layout->labelForField(m_paramSpins[0])->setVisible(true);
        m_paramSpins[0]->setValue(60);
    } else if (shapeType == "Triangle") {
        if (QLabel *lbl = getLabel(m_paramSpins[0])) lbl->setText("Side:");
        m_paramSpins[0]->setVisible(true);
        layout->labelForField(m_paramSpins[0])->setVisible(true);
        m_paramSpins[0]->setValue(100);
    } else if (shapeType == "Star") {
        if (QLabel *lbl = getLabel(m_paramSpins[0])) lbl->setText("Points (5,6,8):");
        if (QLabel *lbl = getLabel(m_paramSpins[1])) lbl->setText("Outer radius:");
        if (QLabel *lbl = getLabel(m_paramSpins[2])) lbl->setText("Inner radius:");
        m_paramSpins[0]->setRange(5, 8);
        m_paramSpins[0]->setSingleStep(1);
        m_paramSpins[0]->setValue(5);
        m_paramSpins[1]->setValue(80);
        m_paramSpins[2]->setValue(40);
        m_paramSpins[0]->setVisible(true);
        m_paramSpins[1]->setVisible(true);
        m_paramSpins[2]->setVisible(true);
        layout->labelForField(m_paramSpins[0])->setVisible(true);
        layout->labelForField(m_paramSpins[1])->setVisible(true);
        layout->labelForField(m_paramSpins[2])->setVisible(true);
    } else if (shapeType == "Hexagon") {
        if (QLabel *lbl = getLabel(m_paramSpins[0])) lbl->setText("Side:");
        m_paramSpins[0]->setVisible(true);
        layout->labelForField(m_paramSpins[0])->setVisible(true);
        m_paramSpins[0]->setValue(80);
    } else if (shapeType == "Rhombus") {
        if (QLabel *lbl = getLabel(m_paramSpins[0])) lbl->setText("Diagonal X:");
        if (QLabel *lbl = getLabel(m_paramSpins[1])) lbl->setText("Diagonal Y:");
        m_paramSpins[0]->setVisible(true);
        m_paramSpins[1]->setVisible(true);
        layout->labelForField(m_paramSpins[0])->setVisible(true);
        layout->labelForField(m_paramSpins[1])->setVisible(true);
        m_paramSpins[0]->setValue(120);
        m_paramSpins[1]->setValue(80);
    } else if (shapeType == "Trapezoid") {
        if (QLabel *lbl = getLabel(m_paramSpins[0])) lbl->setText("Top width:");
        if (QLabel *lbl = getLabel(m_paramSpins[1])) lbl->setText("Bottom width:");
        if (QLabel *lbl = getLabel(m_paramSpins[2])) lbl->setText("Height:");
        m_paramSpins[0]->setVisible(true);
        m_paramSpins[1]->setVisible(true);
        m_paramSpins[2]->setVisible(true);
        layout->labelForField(m_paramSpins[0])->setVisible(true);
        layout->labelForField(m_paramSpins[1])->setVisible(true);
        layout->labelForField(m_paramSpins[2])->setVisible(true);
        m_paramSpins[0]->setValue(60);
        m_paramSpins[1]->setValue(100);
        m_paramSpins[2]->setValue(80);
    }
}

void MainWindow::onAddShape()
{
    Shape *shape = nullptr;
    QString type = m_shapeTypeCombo->currentText();
    double cx = m_canvas->width() / 2.0;
    double cy = m_canvas->height() / 2.0;
    
    if (type == "Rectangle") {
        double w = m_paramSpins[0]->value();
        double h = m_paramSpins[1]->value();
        shape = new Rectangle(cx, cy, w, h);
    } else if (type == "Square") {
        double s = m_paramSpins[0]->value();
        shape = new Square(cx, cy, s);
    } else if (type == "Circle") {
        double r = m_paramSpins[0]->value();
        shape = new Circle(cx, cy, r);
    } else if (type == "Triangle") {
        double s = m_paramSpins[0]->value();
        shape = new Triangle(cx, cy, s);
    } else if (type == "Star") {
        int points = static_cast<int>(m_paramSpins[0]->value());
        double outer = m_paramSpins[1]->value();
        double inner = m_paramSpins[2]->value();
        shape = new Star(cx, cy, points, outer, inner);
    } else if (type == "Hexagon") {
        double s = m_paramSpins[0]->value();
        shape = new Hexagon(cx, cy, s);
    } else if (type == "Rhombus") {
        double dx = m_paramSpins[0]->value();
        double dy = m_paramSpins[1]->value();
        shape = new Rhombus(cx, cy, dx, dy);
    } else if (type == "Trapezoid") {
        double top = m_paramSpins[0]->value();
        double bottom = m_paramSpins[1]->value();
        double h = m_paramSpins[2]->value();
        shape = new Trapezoid(cx, cy, top, bottom, h);
    }
    
    if (shape) {
        m_canvas->addShape(shape);
        QString itemText = QString("%1 #%2").arg(type).arg(m_shapeListCombo->count() + 1);
        m_shapeListCombo->addItem(itemText, QVariant::fromValue(static_cast<void*>(shape)));
        m_shapeListCombo->setCurrentIndex(m_shapeListCombo->count() - 1);
        updateInfo();
    }
}

void MainWindow::onRemoveSelected()
{
    Shape *s = currentShape();
    if (s) {
        m_canvas->removeShape(s);
        int idx = m_shapeListCombo->currentIndex();
        m_shapeListCombo->removeItem(idx);
        delete s;
        updateInfo();
    }
}

void MainWindow::onAnimateTranslate()
{
    Shape *s = currentShape();
    if (s) s->animateTranslate(50, 50, 1000);
}

void MainWindow::onAnimateRotate()
{
    Shape *s = currentShape();
    if (s) s->animateRotate(45, s->center(), 1000);
}

void MainWindow::onAnimateScale()
{
    Shape *s = currentShape();
    if (s) s->animateScale(1.5, s->center(), 1000);
}

void MainWindow::onShapeSelected(int index)
{
    Q_UNUSED(index);
    updateInfo();
}

Shape *MainWindow::currentShape() const
{
    int idx = m_shapeListCombo->currentIndex();
    if (idx < 0) return nullptr;
    void *ptr = m_shapeListCombo->itemData(idx).value<void*>();
    return static_cast<Shape*>(ptr);
}

void MainWindow::updateInfo()
{
    Shape *s = currentShape();
    if (!s) {
        m_infoLabel->setText("No shape selected");
        return;
    }
    QString info = QString("Area: %1\nPerimeter: %2\nCenter: (%3, %4)")
                       .arg(s->area(), 0, 'f', 2)
                       .arg(s->perimeter(), 0, 'f', 2)
                       .arg(s->center().x(), 0, 'f', 1)
                       .arg(s->center().y(), 0, 'f', 1);
    m_infoLabel->setText(info);
}