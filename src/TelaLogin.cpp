#include "TelaLogin.h"
#include "mainwindow.h"
#include "UserImpl.h"
#include <QMessageBox>
#include <QFrame>

TelaLogin::TelaLogin(QWidget *parent) : QWidget(parent) {
    this->resize(380, 680);
    this->setWindowTitle("Clínica - Acesso ao Sistema");

    layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setSpacing(8);

    // ================= SEÇÃO DE LOGIN =================
    lblTituloLogin = new QLabel("<h2>Acessar Conta</h2>", this);
    lblTituloLogin->setAlignment(Qt::AlignCenter);
    layoutPrincipal->addWidget(lblTituloLogin);

    lblUsuario = new QLabel("Usuário (Email ou admin):", this);
    txtUsuario = new QLineEdit(this);
    layoutPrincipal->addWidget(lblUsuario);
    layoutPrincipal->addWidget(txtUsuario);

    lblSenha = new QLabel("Senha:", this);
    txtSenha = new QLineEdit(this);
    txtSenha->setEchoMode(QLineEdit::Password);
    layoutPrincipal->addWidget(lblSenha);
    layoutPrincipal->addWidget(txtSenha);

    btnEntrar = new QPushButton("Entrar", this);
    layoutPrincipal->addWidget(btnEntrar);

    // ================= LINHA DIVISÓRIA =================
    linhaDivisoria = new QFrame(this);
    linhaDivisoria->setFrameShape(QFrame::HLine);
    linhaDivisoria->setFrameShadow(QFrame::Sunken);
    layoutPrincipal->addWidget(linhaDivisoria);

    // ================= SEÇÃO DE CADASTRO =================
    lblTituloCadastro = new QLabel("<h2>Não tem conta? Cadastre-se</h2>", this);
    lblTituloCadastro->setAlignment(Qt::AlignCenter);
    layoutPrincipal->addWidget(lblTituloCadastro);

    lblCadNome = new QLabel("Nome Completo:", this);
    txtCadNome = new QLineEdit(this);
    layoutPrincipal->addWidget(lblCadNome);
    layoutPrincipal->addWidget(txtCadNome);

    lblCadCpf = new QLabel("CPF:", this);
    txtCadCpf = new QLineEdit(this);
    layoutPrincipal->addWidget(lblCadCpf);
    layoutPrincipal->addWidget(txtCadCpf);

    lblCadEmail = new QLabel("Email:", this);
    txtCadEmail = new QLineEdit(this);
    layoutPrincipal->addWidget(lblCadEmail);
    layoutPrincipal->addWidget(txtCadEmail);

    lblCadSenha = new QLabel("Senha de Cadastro:", this);
    txtCadSenha = new QLineEdit(this);
    txtCadSenha->setEchoMode(QLineEdit::Password);
    layoutPrincipal->addWidget(lblCadSenha);
    layoutPrincipal->addWidget(txtCadSenha);

    lblCadTipo = new QLabel("Tipo de Usuário:", this);
    cbxCadTipo = new QComboBox(this);
    cbxCadTipo->addItem("Paciente");
    cbxCadTipo->addItem("Secretária");
    cbxCadTipo->addItem("Médico");
    cbxCadTipo->addItem("Administrador");
    layoutPrincipal->addWidget(lblCadTipo);
    layoutPrincipal->addWidget(cbxCadTipo);

    btnCadastrar = new QPushButton("Criar Nova Conta", this);
    layoutPrincipal->addWidget(btnCadastrar);

    // Conexões dos botões
    connect(btnEntrar, &QPushButton::clicked, this, &TelaLogin::on_btnEntrar_clicked);
    connect(btnCadastrar, &QPushButton::clicked, this, &TelaLogin::on_btnCadastrar_clicked);
}

TelaLogin::~TelaLogin() {}

void TelaLogin::on_btnEntrar_clicked() {
    QString usuario = txtUsuario->text();
    QString senha = txtSenha->text();

    // Validação master rápida ou você pode expandir para ler do seu sistema de usuários
    if ((usuario == "admin" && senha == "1234") || (!usuario.isEmpty() && !senha.isEmpty())) {
        MainWindow *janelaPrincipal = new MainWindow();
        janelaPrincipal->setAttribute(Qt::WA_DeleteOnClose);
        janelaPrincipal->show();
        
        this->close(); // Fecha a tela de login integrada
    } else {
        QMessageBox::warning(this, "Erro de Acesso", "Por favor, preencha o usuário e senha corretamente!");
    }
}

void TelaLogin::on_btnCadastrar_clicked() {
    if (txtCadNome->text().isEmpty() || txtCadEmail->text().isEmpty() || txtCadSenha->text().isEmpty()) {
        QMessageBox::warning(this, "Erro no Cadastro", "Preencha todos os campos obrigatórios (Nome, Email e Senha)!");
        return;
    }

    UserType tipoSelecionado = static_cast<UserType>(cbxCadTipo->currentIndex());

    // Cria o usuário usando a estrutura Handle-Body que você possui
    User* newUser = new UserHandle(
        txtCadNome->text().toStdString(),
        txtCadCpf->text().toStdString(),
        txtCadEmail->text().toStdString(),
        txtCadSenha->text().toStdString(),
        tipoSelecionado
    );

    QMessageBox::information(this, "Sucesso", "Usuário cadastrado com sucesso! Agora você já pode fazer o Login no topo.");
    
    // Limpa os campos de cadastro após o sucesso
    txtCadNome->clear();
    txtCadCpf->clear();
    txtCadEmail->clear();
    txtCadSenha->clear();
}