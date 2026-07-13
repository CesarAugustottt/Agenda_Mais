#ifndef TELALOGIN_H
#define TELALOGIN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>
#include "System.h"

class TelaLogin : public QWidget {
    Q_OBJECT

public:
    explicit TelaLogin(System* sys, QWidget *parent = nullptr);
    ~TelaLogin();

private slots:
    void on_btnEntrar_clicked();
    void on_btnIrParaCadastro_clicked(); // Slot alterado para abrir a nova tela

private:
    QVBoxLayout *layoutPrincipal;

    // --- COMPONENTES DE LOGIN ---
    QLabel *lblTituloLogin;
    QLabel *lblUsuario;
    QLineEdit *txtUsuario;
    QLabel *lblSenha;
    QLineEdit *txtSenha;
    QPushButton *btnEntrar;

    // Linha divisória visual
    QFrame *linhaDivisoria;

    // --- COMPONENTES DE CADASTRO SIMPLIFICADO ---
    QLabel *lblTextoCadastro;
    QPushButton *btnIrParaCadastro; // Apenas o botão agora!

    System* sistema;
};

#endif // TELALOGIN_H