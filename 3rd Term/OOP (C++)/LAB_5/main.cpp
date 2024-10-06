#include "mainwindow.h"
//#include "VideoClass.h"
#include <QApplication>



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(800, 600);
    w.setWindowTitle("Car collection manager");
    w.show();
    return a.exec();
}


























