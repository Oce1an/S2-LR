#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTableWidget>
#include <vector>
#include <algorithm>
#include "component.h"
#include "configresultdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnLoadFile_clicked();
    void on_btnSaveFile_clicked();
    void on_btnAddComponent_clicked();
    void on_btnDeleteComponent_clicked();
    void on_btnSearch_clicked();
    void on_btnSortByPrice_clicked();
    void on_btnBuildConfig_clicked();
    void on_btnClearTable_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<Component> components;
    QString currentFileName;

    void fillTable();
    std::vector<Component> filterByType(const std::string& type);

    void generateConfigs(const std::vector<std::string>& types,
                         std::map<std::string, std::vector<Component>>& byType,
                         size_t index,
                         std::vector<Component>& currentConfig,
                         std::vector<std::vector<Component>>& allConfigs,
                         double minPrice,
                         double maxPrice);
};

#endif
