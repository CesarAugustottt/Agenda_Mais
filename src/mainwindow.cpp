#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "TelaEspecialidade.h"
#include "TelaCadastroUsuario.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    layoutCentral = new QVBoxLayout(ui->centralwidget);
    
    btnAbrirAgendamento = new QPushButton("Solicitar Agendamento", this);
    btnAbrirCadastro = new QPushButton("Cadastrar Usuário", this);

    layoutCentral->addWidget(btnAbrirAgendamento);
    layoutCentral->addWidget(btnAbrirCadastro);

    connect(btnAbrirAgendamento, &QPushButton::clicked, this, &MainWindow::on_btnAbrirAgendamento_clicked);
    connect(btnAbrirCadastro, &QPushButton::clicked, this, &MainWindow::on_btnAbrirCadastro_clicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_btnAbrirAgendamento_clicked() {
    TelaEspecialidade *tela = new TelaEspecialidade(nullptr);
    tela->setAttribute(Qt::WA_DeleteOnClose);
    tela->show();
}

void MainWindow::on_btnAbrirCadastro_clicked() {
    TelaCadastroUsuario *tela = new TelaCadastroUsuario(nullptr);
    tela->setAttribute(Qt::WA_DeleteOnClose);
    tela->show();
}
