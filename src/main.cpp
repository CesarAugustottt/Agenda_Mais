#include <QApplication>
#include "mainwindow.h"
#include "TelaLogin.h"
#include "System.h"

int numBodyCreated = 0;
int numBodyDeleted = 0;
int numHandleCreated = 0;
int numHandleDeleted = 0;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    System* sys = System::createSystem();

    TelaLogin w(sys);
    w.show();

    return app.exec();
}
