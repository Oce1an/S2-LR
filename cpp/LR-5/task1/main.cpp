#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("Keyboard Trainer");

    MainWindow w;
    w.resize(900, 600);
    w.show();

    return app.exec();
}