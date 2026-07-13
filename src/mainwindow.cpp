#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "TelaEspecialidade.h"
#include "TelaCadastroUsuario.h"
#include "ManageMedicationsView.h"

//recebe o sistema pelo construtor
MainWindow::MainWindow(System* sys, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sistema(sys) //guarda o ponteiro do sistema
{
    ui->setupUi(this);
    this->setWindowTitle("Menu Principal - Clínica"); //titulo

    medicationsController = new MedicationsController();

    layoutCentral = new QVBoxLayout(ui->centralwidget);
    
    //inicializando os botoes
    btnAbrirAgendamento = new QPushButton("Solicitar Agendamento", this);
    btnAbrirAgendamento->setMinimumHeight(50);
    btnAbrirCadastro = new QPushButton("Cadastrar Usuário", this);
    btnGerenciarMedicamentos = new QPushButton("Gerenciar Medicamentos (Secretária)", this);

    //adiciona botoes ao layout
    layoutCentral->addWidget(btnAbrirAgendamento);
    layoutCentral->addWidget(btnAbrirCadastro);
    layoutCentral->addWidget(btnGerenciarMedicamentos);

    //conecta clique ao slot
    connect(btnAbrirAgendamento, &QPushButton::clicked, this, &MainWindow::on_btnAbrirAgendamento_clicked);
    connect(btnAbrirCadastro, &QPushButton::clicked, this, &MainWindow::on_btnAbrirCadastro_clicked);
    connect(btnGerenciarMedicamentos, &QPushButton::clicked, this, &MainWindow::on_btnGerenciarMedicamentos_clicked);
}

//destrutor
MainWindow::~MainWindow() {
    delete ui;
    delete medicationsController; 
}

void MainWindow::on_btnAbrirAgendamento_clicked() {
    TelaEspecialidade *tela = new TelaEspecialidade(nullptr);
    tela->setAttribute(Qt::WA_DeleteOnClose);
    tela->show(); //exibir
}

void MainWindow::on_btnAbrirCadastro_clicked() {
    //abre a tela repassando o sistema global
    TelaCadastroUsuario *tela = new TelaCadastroUsuario(nullptr, sistema);
    tela->setAttribute(Qt::WA_DeleteOnClose);
    tela->show(); //exibir
}

void MainWindow::on_btnGerenciarMedicamentos_clicked() {
    ManageMedicationsView *tela = new ManageMedicationsView(medicationsController, nullptr);
    tela->setAttribute(Qt::WA_DeleteOnClose);
    tela->show(); //exibir
}
