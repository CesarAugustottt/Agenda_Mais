#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "TelaEspecialidade.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Menu Principal - Clínica");

    layoutCentral = new QVBoxLayout(ui->centralwidget);
    
    // Deixando apenas o botão de Solicitar Agendamento como pedido
    btnAbrirAgendamento = new QPushButton("Solicitar Agendamento", this);
    btnAbrirAgendamento->setMinimumHeight(50); // Dá um destaque maior para o botão único

    layoutCentral->addWidget(btnAbrirAgendamento);

    connect(btnAbrirAgendamento, &QPushButton::clicked, this, &MainWindow::on_btnAbrirAgendamento_clicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_btnAbrirAgendamento_clicked() {
    TelaEspecialidade *tela = new TelaEspecialidade(nullptr);
    tela->setAttribute(Qt::WA_DeleteOnClose);
    tela->show();
}