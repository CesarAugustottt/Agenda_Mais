#include "TelaCadastroUsuario.h"
#include "UserImpl.h"
#include "User.h"
#include <QMessageBox>

TelaCadastroUsuario::TelaCadastroUsuario(QWidget *parent) : QWidget(parent) {
    this->resize(360, 640);
    this->setWindowTitle("Cadastro de Usuário");

    layoutPrincipal = new QVBoxLayout(this);

    lblNome = new QLabel("Nome:", this);
    txtNome = new QLineEdit(this);
    layoutPrincipal->addWidget(lblNome);
    layoutPrincipal->addWidget(txtNome);

    lblCpf = new QLabel("CPF:", this);
    txtCpf = new QLineEdit(this);
    layoutPrincipal->addWidget(lblCpf);
    layoutPrincipal->addWidget(txtCpf);

    lblEmail = new QLabel("Email:", this);
    txtEmail = new QLineEdit(this);
    layoutPrincipal->addWidget(lblEmail);
    layoutPrincipal->addWidget(txtEmail);

    lblSenha = new QLabel("Senha:", this);
    txtSenha = new QLineEdit(this);
    txtSenha->setEchoMode(QLineEdit::Password);
    layoutPrincipal->addWidget(lblSenha);
    layoutPrincipal->addWidget(txtSenha);

    lblTipo = new QLabel("Tipo de Usuário:", this);
    cbxTipo = new QComboBox(this);
    cbxTipo->addItem("Paciente");      // Index 0 -> PATIENT
    cbxTipo->addItem("Secretária");    // Index 1 -> SECRETARY
    cbxTipo->addItem("Médico");        // Index 2 -> DOCTOR
    cbxTipo->addItem("Administrador"); // Index 3 -> ADMINISTRATOR
    layoutPrincipal->addWidget(lblTipo);
    layoutPrincipal->addWidget(cbxTipo);

    btnSalvar = new QPushButton("Salvar", this);
    btnVoltar = new QPushButton("Voltar", this);
    layoutPrincipal->addWidget(btnSalvar);
    layoutPrincipal->addWidget(btnVoltar);

    connect(btnSalvar, &QPushButton::clicked, this, &TelaCadastroUsuario::on_btnSalvar_clicked);
    connect(btnVoltar, &QPushButton::clicked, this, &TelaCadastroUsuario::on_btnVoltar_clicked);
}

TelaCadastroUsuario::~TelaCadastroUsuario() {}

void TelaCadastroUsuario::on_btnSalvar_clicked() {
    UserType tipoSelecionado = static_cast<UserType>(cbxTipo->currentIndex());

    User* newUser = new UserHandle(
        txtNome->text().toStdString(),
        txtCpf->text().toStdString(),
        txtEmail->text().toStdString(),
        txtSenha->text().toStdString(),
        tipoSelecionado
    );
    
    QMessageBox::information(this, "Sucesso", "Usuário alocado na memória com sucesso!");
    
    delete newUser;
    this->close();
}

void TelaCadastroUsuario::on_btnVoltar_clicked() {
    this->close();
}
