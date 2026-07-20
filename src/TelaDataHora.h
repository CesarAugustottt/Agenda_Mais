#ifndef TELADATAHORA_H
#define TELADATAHORA_H

#include <QWidget>
#include <QCalendarWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "Appointment.h"
#include "System.h"

class System;

class TelaDataHora : public QWidget {
    Q_OBJECT

public:
    explicit TelaDataHora(QWidget *parent = nullptr, Specialty esp = Specialty::DENTIST, System* sys = nullptr);
    ~TelaDataHora();

private:
    //slots acionados dependendo do botao com horario que o usuario clicar
    void on_btnHora1330_clicked();
    void on_btnHora1400_clicked();
    void on_btnHora1430_clicked();
    void on_btnHora1500_clicked();
    void on_btnVoltar_clicked();

private:
    System* sistema;
    Specialty espSelecionada;
    User* pacienteAtual; // paciente reaproveitado entre os cliques nesta tela, em vez de recriado a cada horário

    QVBoxLayout *layoutPrincipal; //layout que organiza tudo
    QCalendarWidget *calendarioWidget; //ponteiro com calendario
    QPushButton *btnHora1330;
    QPushButton *btnHora1400;
    QPushButton *btnHora1430;
    QPushButton *btnHora1500;
    QPushButton *btnVoltar;

    void processarAgendamento(const std::string& horario, User* patient);
    User* getOrCreatePacienteTeste();
};

#endif // TELADATAHORA_H