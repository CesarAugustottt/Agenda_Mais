#include "TelaCadastroUsuario.h"
#include "System.h"
#include <QMessageBox>

TelaCadastroUsuario::TelaCadastroUsuario(QWidget *parent, System* sys) 
    : QWidget(parent), sys(sys) { 
    
    // configura a janela
    this->resize(360, 640);
    this->setWindowTitle("Cadastro de Usuário");

    layoutPrincipal = new QVBoxLayout(this);

    // cria os campos de texto e adiciona no layout
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
    txtSenha->setEchoMode(QLineEdit::Password); // esconde a senha digitada
    layoutPrincipal->addWidget(lblSenha);
    layoutPrincipal->addWidget(txtSenha);

    // opcoes de tipo de usuario
    lblTipo = new QLabel("Tipo de Usuário:", this);
    cbxTipo = new QComboBox(this);
    cbxTipo->addItem("Paciente");      
    cbxTipo->addItem("Secretária");    
    cbxTipo->addItem("Médico");        
    cbxTipo->addItem("Administrador"); 
    layoutPrincipal->addWidget(lblTipo);
    layoutPrincipal->addWidget(cbxTipo);

    // botoes finais
    btnSalvar = new QPushButton("Salvar", this);
    btnVoltar = new QPushButton("Voltar", this);
    layoutPrincipal->addWidget(btnSalvar);
    layoutPrincipal->addWidget(btnVoltar);

    // conecta clique ao slot
    connect(btnSalvar, &QPushButton::clicked, this, &TelaCadastroUsuario::on_btnSalvar_clicked);
    connect(btnVoltar, &QPushButton::clicked, this, &TelaCadastroUsuario::on_btnVoltar_clicked);
}

// destrutor
TelaCadastroUsuario::~TelaCadastroUsuario() {}

void TelaCadastroUsuario::on_btnSalvar_clicked() {
    // verifica se o sistema ta funcionando
    if (!sys) {
        QMessageBox::critical(this, "Erro", "Sistema não inicializado.");
        return;
    }

    UserType tipoSelecionado = static_cast<UserType>(cbxTipo->currentIndex());

    // cria o usuario usando o sistema global
    sys->createUser(
        txtNome->text().toStdString(),
        txtCpf->text().toStdString(),
        txtEmail->text().toStdString(),
        txtSenha->text().toStdString(),
        tipoSelecionado
    );
    
    QMessageBox::information(this, "Sucesso", "Usuário cadastrado com sucesso!");
    
    this->close(); // fecha tela atual
}

// se apertar em voltar, fecha a tela
void TelaCadastroUsuario::on_btnVoltar_clicked() {
    this->close();
}
