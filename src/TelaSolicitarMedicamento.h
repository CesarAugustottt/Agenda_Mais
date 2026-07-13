#ifndef TELASOLICITARMEDICAMENTO_H
#define TELASOLICITARMEDICAMENTO_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <vector>
#include "MedicationsController.h"

class TelaSolicitarMedicamento : public QWidget {
    Q_OBJECT

public:
    explicit TelaSolicitarMedicamento(QWidget *parent = nullptr, MedicationsController* controller = nullptr);
    ~TelaSolicitarMedicamento();

private slots:
    void on_cbxMedicamento_currentIndexChanged(int index);
    void on_btnSolicitar_clicked();
    void on_btnVoltar_clicked();

private:
    MedicationsController* controller;
    std::vector<Medication*> medicamentosDisponiveis;

    QVBoxLayout *layoutPrincipal;

    QLabel *lblCpf;
    QLineEdit *txtCpf;

    QLabel *lblMedicamento;
    QComboBox *cbxMedicamento;

    QLabel *lblEstoqueDisponivel;
    QLabel *lblExigeReceita;

    QLabel *lblQuantidade;
    QSpinBox *spinQuantidade;

    QLabel *lblReceita;
    QLineEdit *txtCaminhoReceita;

    QPushButton *btnSolicitar;
    QPushButton *btnVoltar;

    void carregarMedicamentos();
    void atualizarInfoMedicamento();
};

#endif // TELASOLICITARMEDICAMENTO_H