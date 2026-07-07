#ifndef TELACADASTROUSUARIO_H
#define TELACADASTROUSUARIO_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

class TelaCadastroUsuario : public QWidget {
    Q_OBJECT

public:
    explicit TelaCadastroUsuario(QWidget *parent = nullptr);
    ~TelaCadastroUsuario();

private slots:
    void on_btnSalvar_clicked();
    void on_btnVoltar_clicked();

private:
    QVBoxLayout *layoutPrincipal;
    
    QLabel *lblNome;
    QLineEdit *txtNome;
    
    QLabel *lblCpf;
    QLineEdit *txtCpf;
    
    QLabel *lblEmail;
    QLineEdit *txtEmail;
    
    QLabel *lblSenha;
    QLineEdit *txtSenha;
    
    QLabel *lblTipo;
    QComboBox *cbxTipo;
    
    QPushButton *btnSalvar;
    QPushButton *btnVoltar;
};

#endif
