#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QPushButton>
#include <QTextEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void solveHanoi();

private:
    QSpinBox *nSpinBox;
    QTextEdit *outputText;

    void hanoi(int n, char from, char to, char aux, QString &steps);
};

#endif