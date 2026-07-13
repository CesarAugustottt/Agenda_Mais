#ifndef TELAAGENDA_H
#define TELAAGENDA_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include "System.h"

class TelaAgenda : public QWidget {
    Q_OBJECT

public:
    explicit TelaAgenda(QWidget *parent = nullptr, System* sys = nullptr);
    ~TelaAgenda();

private slots:
    void on_btnAtualizar_clicked();
    void on_btnVoltar_clicked();

private:
    System* sistema;

    QVBoxLayout *layoutPrincipal;
    QTableWidget *tabela;
    QPushButton *btnAtualizar;
    QPushButton *btnVoltar;

    void carregarAgenda();
    static QString especialidadeToString(Specialty esp);
    static QString statusToString(Status status);
};

#endif // TELAAGENDA_H