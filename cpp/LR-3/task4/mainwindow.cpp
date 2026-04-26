#include "mainwindow.h"
#include <QVBoxLayout>
#include <QFormLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Ханойская башня");

    QWidget *central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    QFormLayout *formLayout = new QFormLayout();
    nSpinBox = new QSpinBox(this);
    nSpinBox->setRange(1, 20);
    nSpinBox->setValue(3);
    nSpinBox->setPrefix("n = ");
    formLayout->addRow("Количество колец:", nSpinBox);
    mainLayout->addLayout(formLayout);

    QPushButton *solveBtn = new QPushButton("Решить", this);
    mainLayout->addWidget(solveBtn);

    outputText = new QTextEdit(this);
    outputText->setReadOnly(true);
    outputText->setStyleSheet("font-family: monospace; font-size: 13px;");
    mainLayout->addWidget(outputText);

    setCentralWidget(central);
    connect(solveBtn, &QPushButton::clicked, this, &MainWindow::solveHanoi);
}

MainWindow::~MainWindow() {}

void MainWindow::hanoi(int n, char from, char to, char mid, QString &steps)
{
    if (n == 1) {
        steps += QString("Переместить кольцо 1 с %1 на %2\n").arg(from).arg(to);
        return;
    }
    hanoi(n - 1, from, mid, to, steps);
    steps += QString("Переместить кольцо %1 с %2 на %3\n").arg(n).arg(from).arg(to);
    hanoi(n - 1, mid, to, from, steps);
}

void MainWindow::solveHanoi()
{
    int n = nSpinBox->value();
    QString steps;
    steps += QString("Решение для %1 колец:\n\n").arg(n);
    hanoi(n, 'A', 'C', 'B', steps);
    outputText->setPlainText(steps);
}