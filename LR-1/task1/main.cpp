#include <QApplication>
#include <QMessageBox>
#include "mainwindow/mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    try {
        MainWindow window;
        window.show();
        return app.exec();
    }
    catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Critical Error",
            QString("Unexpected error occurred: %1").arg(e.what()));
        return 1;
    }
    catch (...) {
        QMessageBox::critical(nullptr, "Critical Error",
            "Unknown error occurred!");
        return 1;
    }
}