#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "TelaEspecialidade.h"
#include "TelaCadastroUsuario.h"
#include "ManageMedicationsView.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Menu Principal - Clínica");

    medicationsController = new MedicationsController(); // COM 'S'

    layoutCentral = new QVBoxLayout(ui->centralwidget);
    
    btnAbrirAgendamento = new QPushButton("Solicitar Agendamento", this);
    btnAbrirAgendamento->setMinimumHeight(50);
    btnAbrirCadastro = new QPushButton("Cadastrar Usuário", this);
    btnGerenciarMedicamentos = new QPushButton("Gerenciar Medicamentos (Secretária)", this);

    layoutCentral->addWidget(btnAbrirAgendamento);
    layoutCentral->addWidget(btnAbrirCadastro);
    layoutCentral->addWidget(btnGerenciarMedicamentos);

    connect(btnAbrirAgendamento, &QPushButton::clicked, this, &MainWindow::on_btnAbrirAgendamento_clicked);
    connect(btnAbrirCadastro, &QPushButton::clicked, this, &MainWindow::on_btnAbrirCadastro_clicked);
    connect(btnGerenciarMedicamentos, &QPushButton::clicked, this, &MainWindow::on_btnGerenciarMedicamentos_clicked);
}

MainWindow::~MainWindow() {
    delete ui;
    delete medicationsController; 
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

void MainWindow::on_btnGerenciarMedicamentos_clicked() {
    ManageMedicationsView *tela = new ManageMedicationsView(medicationsController, nullptr);
    tela->setAttribute(Qt::WA_DeleteOnClose);
    tela->show();
}