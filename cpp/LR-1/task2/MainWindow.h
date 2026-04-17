#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QDoubleSpinBox>
#include "Canvas.h"
#include "shapes/Shape.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddShape();
    void onRemoveSelected();
    void onAnimateTranslate();
    void onAnimateRotate();
    void onAnimateScale();
    void onShapeSelected(int index);
    void updateParamLabels(const QString &shapeType);

private:
    Canvas *m_canvas;
    QComboBox *m_shapeTypeCombo;
    QComboBox *m_shapeListCombo;
    QPushButton *m_addBtn;
    QPushButton *m_removeBtn;
    QPushButton *m_translateBtn;
    QPushButton *m_rotateBtn;
    QPushButton *m_scaleBtn;
    QLabel *m_infoLabel;
    QList<QDoubleSpinBox*> m_paramSpins;

    Shape *currentShape() const;
    void updateInfo();
};

#endif