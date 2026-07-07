#include <QApplication>
#include "mainwindow.h"
#include "TelaEspecialidade.h"

// Inicializando as variáveis globais do Handle-Body para o linker não reclamar
int numBodyCreated = 0;
int numBodyDeleted = 0;
int numHandleCreated = 0;
int numHandleDeleted = 0;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    TelaEspecialidade tela;
    tela.show();

    return app.exec();
}