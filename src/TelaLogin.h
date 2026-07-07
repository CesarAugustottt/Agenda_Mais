#ifndef TELALOGIN_H
#define TELALOGIN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

class TelaLogin : public QWidget {
    Q_OBJECT

public:
    explicit TelaLogin(QWidget *parent = nullptr);
    ~TelaLogin();

private slots:
    void on_btnEntrar_clicked();
    void on_btnCadastrar_clicked();

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

    // --- COMPONENTES DE CADASTRO ---
    QLabel *lblTituloCadastro;
    QLabel *lblCadNome;
    QLineEdit *txtCadNome;
    QLabel *lblCadCpf;
    QLineEdit *txtCadCpf;
    QLabel *lblCadEmail;
    QLineEdit *txtCadEmail;
    QLabel *lblCadSenha;
    QLineEdit *txtCadSenha;
    QLabel *lblCadTipo;
    QComboBox *cbxCadTipo;
    QPushButton *btnCadastrar;
};
#endif // TELALOGIN_H