#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "component.h"
#include <QInputDialog>
#include <QDoubleSpinBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels({
        "Type", "Manufacturer", "Model", "Parameters", "Price ($)", "In Stock"
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnLoadFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this, "Open Components File", QDir::homePath(),
        "Text Files (*.txt);;All Files (*)"
        );

    if (fileName.isEmpty()) return;
    currentFileName = fileName;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to open file");
        return;
    }

    components.clear();
    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (!line.isEmpty()) {
            components.push_back(Component::fromString(line.toStdString()));
        }
    }
    file.close();

    fillTable();
    QMessageBox::information(this, "Success",
                             QString("Loaded %1 components").arg(components.size()));
}

void MainWindow::on_btnSaveFile_clicked()
{
    if (components.empty()) {
        QMessageBox::warning(this, "Warning", "No components to save");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(
        this, "Save Components File", QDir::homePath(),
        "Text Files (*.txt)"
        );

    if (fileName.isEmpty()) return;
    currentFileName = fileName;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to save file");
        return;
    }

    QTextStream out(&file);
    for (const auto& comp : components) {
        out << QString::fromStdString(comp.toString()) << "\n";
    }
    file.close();

    QMessageBox::information(this, "Success", "File saved successfully");
}

void MainWindow::on_btnAddComponent_clicked()
{
    bool ok;

    QStringList componentTypes = {
        "CPU (Processor)",
        "GPU (Graphics Card)",
        "Motherboard",
        "RAM (Memory)",
        "Storage (SSD/HDD)",
        "PSU (Power Supply)"
    };

    QString typeStr = QInputDialog::getItem(this, "Add Component",
                                            "Select component type:", componentTypes, 0, false, &ok);
    if (!ok) return;

    std::string type;
    if (typeStr.startsWith("CPU")) type = ComponentTypes::CPU;
    else if (typeStr.startsWith("GPU")) type = ComponentTypes::GPU;
    else if (typeStr.startsWith("Motherboard")) type = ComponentTypes::MOTHERBOARD;
    else if (typeStr.startsWith("RAM")) type = ComponentTypes::RAM;
    else if (typeStr.startsWith("Storage")) type = ComponentTypes::STORAGE;
    else if (typeStr.startsWith("PSU")) type = ComponentTypes::PSU;

    QString manufacturer = QInputDialog::getText(this, "Add Component",
                                                 "Manufacturer (Intel/AMD/NVIDIA/etc.):", QLineEdit::Normal, "", &ok);
    if (!ok || manufacturer.isEmpty()) return;

    QString model = QInputDialog::getText(this, "Add Component",
                                          "Model:", QLineEdit::Normal, "", &ok);
    if (!ok || model.isEmpty()) return;

    QString parameters = QInputDialog::getText(this, "Add Component",
                                               "Parameters (e.g., '3.5 GHz, 8 cores'):", QLineEdit::Normal, "", &ok);
    if (!ok || parameters.isEmpty()) return;

    double price = QInputDialog::getDouble(this, "Add Component",
                                           "Price ($):", 0, 0, 100000, 2, &ok);
    if (!ok) return;

    int inStockInt = QInputDialog::getInt(this, "Add Component",
                                          "In Stock? (1=Yes, 0=No):", 1, 0, 1, 1, &ok);
    if (!ok) return;

    Component comp(type, manufacturer.toStdString(),
                   model.toStdString(), parameters.toStdString(),
                   price, inStockInt == 1);

    components.push_back(comp);
    fillTable();

    if (!currentFileName.isEmpty()) {
        QFile file(currentFileName);
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << QString::fromStdString(comp.toString()) << "\n";
            file.close();
        }
    }

    QMessageBox::information(this, "Success", "Component added");
}

void MainWindow::on_btnDeleteComponent_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow < 0 || currentRow >= static_cast<int>(components.size())) {
        QMessageBox::warning(this, "Warning", "Select a component to delete");
        return;
    }

    auto btn = QMessageBox::question(this, "Confirm Delete",
                                     QString("Delete component: %1 - %2?")
                                         .arg(QString::fromStdString(components[currentRow].getType()))
                                         .arg(QString::fromStdString(components[currentRow].getModel())),
                                     QMessageBox::Yes | QMessageBox::No);

    if (btn == QMessageBox::Yes) {
        components.erase(components.begin() + currentRow);
        fillTable();
        QMessageBox::information(this, "Success", "Component deleted");
    }
}

void MainWindow::on_btnSearch_clicked()
{
    QString searchText = ui->lineEditSearch->text();
    if (searchText.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Enter search text");
        return;
    }

    std::vector<Component> found;
    for (const auto& comp : components) {
        if (comp.getType().find(searchText.toStdString()) != std::string::npos ||
            comp.getManufacturer().find(searchText.toStdString()) != std::string::npos ||
            comp.getModel().find(searchText.toStdString()) != std::string::npos) {
            found.push_back(comp);
        }
    }

    if (found.empty()) {
        QMessageBox::information(this, "Search Result", "No components found");
        return;
    }

    ui->tableWidget->setRowCount(0);
    for (const auto& comp : found) {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(comp.getType())));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(comp.getManufacturer())));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(comp.getModel())));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(comp.getParameters())));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(comp.getPrice(), 'f', 2)));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(comp.getInStock() ? "Yes" : "No"));
    }

    QMessageBox::information(this, "Search Result",
                             QString("Found %1 components").arg(found.size()));
}

void MainWindow::on_btnSortByPrice_clicked()
{
    if (components.empty()) {
        QMessageBox::warning(this, "Warning", "No components to sort");
        return;
    }

    std::sort(components.begin(), components.end(),
              [](const Component& a, const Component& b) {
                  if (a.getType() != b.getType()) {
                      return a.getType() < b.getType();
                  }
                  return a.getPrice() > b.getPrice();
              });

    fillTable();
    QMessageBox::information(this, "Success", "Components sorted by price");
}

void MainWindow::on_btnBuildConfig_clicked()
{
    bool ok1, ok2;

    double minPrice = QInputDialog::getDouble(this, "Build PC Configuration",
                                              "Minimum Total Price ($):", 500, 0, 100000, 2, &ok1);
    if (!ok1) return;

    double maxPrice = QInputDialog::getDouble(this, "Build PC Configuration",
                                              "Maximum Total Price ($):", 2000, 0, 100000, 2, &ok2);
    if (!ok2) return;

    if (minPrice > maxPrice) {
        QMessageBox::warning(this, "Warning", "Min price cannot be greater than max price");
        return;
    }

    std::map<std::string, std::vector<Component>> byType;
    for (const auto& comp : components) {
        if (comp.getInStock()) {
            byType[comp.getType()].push_back(comp);
        }
    }

    std::vector<std::string> requiredTypes = ComponentTypes::getAllTypes();
    std::string missingTypes;
    for (const auto& type : requiredTypes) {
        if (byType.find(type) == byType.end() || byType[type].empty()) {
            missingTypes += type + ", ";
        }
    }

    if (!missingTypes.empty()) {
        missingTypes.pop_back();
        missingTypes.pop_back();
        QMessageBox::warning(this, "Missing Components",
                             QString("The following component types are missing:\n%1\n\n"
                                     "Please add: CPU, GPU, Motherboard, RAM, Storage, PSU")
                                 .arg(QString::fromStdString(missingTypes)));
        return;
    }

    std::vector<std::vector<Component>> allConfigs;
    std::vector<Component> currentConfig;

    generateConfigs(requiredTypes, byType, 0, currentConfig, allConfigs,
                    minPrice, maxPrice);

    if (allConfigs.empty()) {
        QMessageBox::information(this, "Configuration Result",
                                 "No complete PC configurations found in this price range");
        return;
    }

    QString result;
    int configNum = 1;

    for (const auto& config : allConfigs) {
        double totalPrice = 0;
        result += QString("=== Configuration #%1 ===\n").arg(configNum++);

        for (const auto& comp : config) {
            result += QString("%1: %2 %3 - $%4\n")
                          .arg(QString::fromStdString(comp.getType()), -15)
                          .arg(QString::fromStdString(comp.getManufacturer()), -12)
                          .arg(QString::fromStdString(comp.getModel()), -25)
                          .arg(comp.getPrice(), 8, 'f', 2);
            totalPrice += comp.getPrice();
        }

        result += QString("\n%1\n\n").arg(QString(50, '='));
        result += QString("Total Price: $%1\n\n\n").arg(totalPrice, 8, 'f', 2);
    }

    ConfigResultDialog *dialog = new ConfigResultDialog(this);
    dialog->setConfigurations(result, allConfigs.size());
    dialog->exec();
    delete dialog;
}

void MainWindow::generateConfigs(
    const std::vector<std::string>& types,
    std::map<std::string, std::vector<Component>>& byType,
    size_t index,
    std::vector<Component>& currentConfig,
    std::vector<std::vector<Component>>& allConfigs,
    double minPrice,
    double maxPrice)
{
    if (index == types.size()) {
        double totalPrice = 0;
        for (const auto& comp : currentConfig) {
            totalPrice += comp.getPrice();
        }

        if (totalPrice >= minPrice && totalPrice <= maxPrice) {
            allConfigs.push_back(currentConfig);
        }
        return;
    }

    const std::string& currentType = types[index];
    for (const auto& comp : byType[currentType]) {
        currentConfig.push_back(comp);
        generateConfigs(types, byType, index + 1, currentConfig, allConfigs, minPrice, maxPrice);
        currentConfig.pop_back();
    }
}

void MainWindow::on_btnClearTable_clicked()
{
    components.clear();
    ui->tableWidget->setRowCount(0);
    currentFileName.clear();
    QMessageBox::information(this, "Success", "Table cleared");
}

void MainWindow::fillTable()
{
    ui->tableWidget->setRowCount(0);

    for (const auto& comp : components) {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(comp.getType())));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(comp.getManufacturer())));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(comp.getModel())));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(comp.getParameters())));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(comp.getPrice(), 'f', 2)));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(comp.getInStock() ? "Yes" : "No"));
    }
}

std::vector<Component> MainWindow::filterByType(const std::string& type)
{
    std::vector<Component> result;
    for (const auto& comp : components) {
        if (comp.getType() == type) {
            result.push_back(comp);
        }
    }
    return result;
}
