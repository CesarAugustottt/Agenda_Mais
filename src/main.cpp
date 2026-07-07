#include <QApplication>
#include "mainwindow.h"
#include "TelaLogin.h"

int numBodyCreated = 0;
int numBodyDeleted = 0;
int numHandleCreated = 0;
int numHandleDeleted = 0;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Agora o aplicativo inicia obrigatoriamente pela tela de Login integrada
    TelaLogin w;
    w.show();

    return app.exec();
}
