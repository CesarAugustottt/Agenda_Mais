#ifndef TELACADASTROUSUARIO_H
#define TELACADASTROUSUARIO_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

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
    
    QLabel *lblSenha;
    QLineEdit *txtSenha;
    
    QPushButton *btnSalvar;
    QPushButton *btnVoltar;
};

#endif // TELACADASTROUSUARIO_H
