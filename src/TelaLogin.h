#ifndef TELALOGIN_H
#define TELALOGIN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>

class TelaLogin : public QWidget {
    Q_OBJECT

public:
    explicit TelaLogin(QWidget *parent = nullptr);
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
};

#endif // TELALOGIN_H