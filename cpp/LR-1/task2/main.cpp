#include <QApplication>
#include <QMainWindow>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    QMainWindow w;
    QLabel *label = new QLabel("If you see this, Qt works!");
    w.setCentralWidget(label);
    w.show();
    
    return app.exec();
}