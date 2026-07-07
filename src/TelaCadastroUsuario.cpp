#include "TelaCadastroUsuario.h"
#include "UserImpl.h"
#include <QMessageBox>

TelaCadastroUsuario::TelaCadastroUsuario(QWidget *parent) : QWidget(parent) {
    layoutPrincipal = new QVBoxLayout(this);

    lblNome = new QLabel("Nome:", this);
    txtNome = new QLineEdit(this);
    layoutPrincipal->addWidget(lblNome);
    layoutPrincipal->addWidget(txtNome);

    lblCpf = new QLabel("CPF:", this);
    txtCpf = new QLineEdit(this);
    layoutPrincipal->addWidget(lblCpf);
    layoutPrincipal->addWidget(txtCpf);

    lblSenha = new QLabel("Senha:", this);
    txtSenha = new QLineEdit(this);
    txtSenha->setEchoMode(QLineEdit::Password);
    layoutPrincipal->addWidget(lblSenha);
    layoutPrincipal->addWidget(txtSenha);

    btnSalvar = new QPushButton("Salvar", this);
    btnVoltar = new QPushButton("Voltar", this);
    layoutPrincipal->addWidget(btnSalvar);
    layoutPrincipal->addWidget(btnVoltar);

    connect(btnSalvar, &QPushButton::clicked, this, &TelaCadastroUsuario::on_btnSalvar_clicked);
    connect(btnVoltar, &QPushButton::clicked, this, &TelaCadastroUsuario::on_btnVoltar_clicked);
}

TelaCadastroUsuario::~TelaCadastroUsuario() {}

void TelaCadastroUsuario::on_btnSalvar_clicked() {
    User* newUser = new UserImpl(txtNome->text().toStdString(), txtCpf->text().toStdString(), txtSenha->text().toStdString());
    
    QMessageBox::information(this, "Sucesso", "Usuário criado com sucesso!");
    
    delete newUser;
    this->close();
}

void TelaCadastroUsuario::on_btnVoltar_clicked() {
    this->close();
}
