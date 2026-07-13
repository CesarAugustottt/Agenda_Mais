#include "TelaLogin.h"
#include "mainwindow.h"
#include "TelaCadastroUsuario.h" // Incluindo a sua tela de cadastro existente
#include <QMessageBox>

TelaLogin::TelaLogin(System* sys, QWidget *parent) : QWidget(parent), sistema(sys){
    // Reduzimos o tamanho da janela já que agora ela tem menos componentes
    this->resize(380, 400);
    this->setWindowTitle("Clínica - Acesso ao Sistema");

    layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setSpacing(12);

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
    btnEntrar->setMinimumHeight(40);
    layoutPrincipal->addWidget(btnEntrar);

    // ================= LINHA DIVISÓRIA =================
    linhaDivisoria = new QFrame(this);
    linhaDivisoria->setFrameShape(QFrame::HLine);
    linhaDivisoria->setFrameShadow(QFrame::Sunken);
    layoutPrincipal->addWidget(linhaDivisoria);

    // ================= SEÇÃO DE CADASTRO SIMPLIFICADA =================
    lblTextoCadastro = new QLabel("Ainda não tem uma conta no sistema?", this);
    lblTextoCadastro->setAlignment(Qt::AlignCenter);
    layoutPrincipal->addWidget(lblTextoCadastro);

    btnIrParaCadastro = new QPushButton("Criar Nova Conta / Cadastrar", this);
    btnIrParaCadastro->setMinimumHeight(35);
    layoutPrincipal->addWidget(btnIrParaCadastro);

    // Conexões dos botões
    connect(btnEntrar, &QPushButton::clicked, this, &TelaLogin::on_btnEntrar_clicked);
    connect(btnIrParaCadastro, &QPushButton::clicked, this, &TelaLogin::on_btnIrParaCadastro_clicked);
}

TelaLogin::~TelaLogin() {}

void TelaLogin::on_btnEntrar_clicked() {
    QString usuario = txtUsuario->text();
    QString senha = txtSenha->text();

    if ((usuario == "admin" && senha == "1234") || (!usuario.isEmpty() && !senha.isEmpty())) {
        MainWindow *janelaPrincipal = new MainWindow(sistema);
        janelaPrincipal->setAttribute(Qt::WA_DeleteOnClose);
        janelaPrincipal->show();

        this->close();
    } else {
        QMessageBox::warning(this, "Erro de Acesso", "Por favor, preencha o usuário e senha corretamente!");
    }
}

// Essa função roda quando clicam no botão de Cadastrar lá embaixo
void TelaLogin::on_btnIrParaCadastro_clicked() {
    // Abre a sua tela de cadastro de usuário padrão do projeto
    TelaCadastroUsuario *telaCadastro = new TelaCadastroUsuario(nullptr, sistema);
    telaCadastro->setAttribute(Qt::WA_DeleteOnClose);
    telaCadastro->show();

    // Opcional: Se quiser fechar a tela de login ao abrir o cadastro, descomente a linha abaixo:
    // this->close();
}