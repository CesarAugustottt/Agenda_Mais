#include "TelaEspecialidade.h"
#include "TelaDataHora.h"

TelaEspecialidade::TelaEspecialidade(QWidget *parent) : QWidget(parent) {
    this->resize(360, 640); //define o tamanho da janela
    this->setWindowTitle("Agende Sua Consulta"); //titulo

    layoutPrincipal = new QVBoxLayout(this);

    // Inicializando todos os 6 botões
    btnDentista      = new QPushButton("Dentista", this);
    btnNeurologista  = new QPushButton("Neurologista", this);
    btnPsicologo     = new QPushButton("Psicologo", this);
    btnCardiologista = new QPushButton("Cardiologista", this);
    btnNutricionista = new QPushButton("Nutricionista", this);
    btnDermatologista = new QPushButton("Dermatologista", this);

    // Adicionando todos os botoes ao layout de exibição
    layoutPrincipal->addWidget(btnDentista);
    layoutPrincipal->addWidget(btnNeurologista);
    layoutPrincipal->addWidget(btnPsicologo);
    layoutPrincipal->addWidget(btnCardiologista);
    layoutPrincipal->addWidget(btnNutricionista);
    layoutPrincipal->addWidget(btnDermatologista);

    // Conectando os sinais aos slots
    connect(btnDentista,      &QPushButton::clicked, this, &TelaEspecialidade::on_btnDentista_clicked);
    connect(btnNeurologista,  &QPushButton::clicked, this, &TelaEspecialidade::on_btnNeurologista_clicked);
    connect(btnPsicologo,     &QPushButton::clicked, this, &TelaEspecialidade::on_btnPsicologo_clicked);
    connect(btnCardiologista, &QPushButton::clicked, this, &TelaEspecialidade::on_btnCardiologista_clicked);
    connect(btnNutricionista, &QPushButton::clicked, this, &TelaEspecialidade::on_btnNutricionista_clicked);
    connect(btnDermatologista, &QPushButton::clicked, this, &TelaEspecialidade::on_btnDermatologista_clicked);
}

//destrutor
TelaEspecialidade::~TelaEspecialidade() {}

void TelaEspecialidade::abrirProximaTela(Specialty esp) {
    TelaDataHora *proximaTela = new TelaDataHora(nullptr, esp);
    proximaTela->setAttribute(Qt::WA_DeleteOnClose);
    proximaTela->show(); //exibir
    this->close(); //fechar tela atual
}

// Repassando o valor do Enum original para a próxima tela
void TelaEspecialidade::on_btnDentista_clicked()      { abrirProximaTela(Specialty::DENTIST); }
void TelaEspecialidade::on_btnNeurologista_clicked()  { abrirProximaTela(Specialty::NEUROLOGIST); }
void TelaEspecialidade::on_btnPsicologo_clicked()     { abrirProximaTela(Specialty::PSYCHOLOGIST); }
void TelaEspecialidade::on_btnCardiologista_clicked() { abrirProximaTela(Specialty::CARDIOLOGIST); }
void TelaEspecialidade::on_btnNutricionista_clicked() { abrirProximaTela(Specialty::NUTRITIONIST); }
void TelaEspecialidade::on_btnDermatologista_clicked() { abrirProximaTela(Specialty::DERMATOLOGIST); }