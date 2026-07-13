#ifndef TELASTATUSAGENDAMENTO_H
#define TELASTATUSAGENDAMENTO_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include "System.h"

class TelaStatusAgendamento : public QWidget {
    Q_OBJECT

public:
    explicit TelaStatusAgendamento(QWidget *parent = nullptr, System* sys = nullptr);
    ~TelaStatusAgendamento();

private slots:
    void on_btnBuscar_clicked();
    void on_btnVoltar_clicked();

private:
    System* sistema;

    QVBoxLayout *layoutPrincipal;
    QHBoxLayout *layoutBusca;

    QLabel *lblCpf;
    QLineEdit *txtCpf;
    QPushButton *btnBuscar;

    QTableWidget *tabela;
    QPushButton *btnVoltar;

    void carregarStatus(const std::string& cpfPaciente);
    static QString especialidadeToString(Specialty esp);
    static QString statusToString(Status status);
};

#endif // TELASTATUSAGENDAMENTO_H