#ifndef TELACADASTROUSUARIO_H
#define TELACADASTROUSUARIO_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

class System; // declaracao antecipada pra evitar erro de dependencia circular

class TelaCadastroUsuario : public QWidget {
    Q_OBJECT

public:
    explicit TelaCadastroUsuario(QWidget *parent = nullptr, System* sys = nullptr);
    ~TelaCadastroUsuario();

private slots:
    // slots de clique dos botoes
    void on_btnSalvar_clicked();
    void on_btnVoltar_clicked();

private:
    System* sys; // ponteiro do sistema global
    QVBoxLayout *layoutPrincipal; // layout que organiza tudo
    
    // campos da tela
    QLabel *lblNome;
    QLineEdit *txtNome;
    
    QLabel *lblCpf;
    QLineEdit *txtCpf;
    
    QLabel *lblEmail;
    QLineEdit *txtEmail;
    
    QLabel *lblSenha;
    QLineEdit *txtSenha;
    
    QLabel *lblTipo;
    QComboBox *cbxTipo; // caixa de selecao do tipo
    
    QPushButton *btnSalvar;
    QPushButton *btnVoltar;
};

#endif
