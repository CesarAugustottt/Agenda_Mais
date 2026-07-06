#include "mainwindow.h"
#include <QApplication>

int numHandleCreated = 0;
int numHandleDeleted = 0;
int numBodyCreated = 0;
int numBodyDeleted = 0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}