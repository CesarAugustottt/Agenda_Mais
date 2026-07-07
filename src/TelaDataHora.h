#ifndef TELADATAHORA_H
#define TELADATAHORA_H

#include <QWidget>
#include <QCalendarWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "Appointment.h"

class TelaDataHora : public QWidget {
    Q_OBJECT

public:
    explicit TelaDataHora(QWidget *parent = nullptr, Specialty esp = Specialty::DENTIST);
    ~TelaDataHora();

private:
    void on_btnHora1330_clicked();
    void on_btnHora1400_clicked();
    void on_btnHora1430_clicked();
    void on_btnHora1500_clicked();
    void on_btnVoltar_clicked();

private:
    Specialty espSelecionada; 

    QVBoxLayout *layoutPrincipal;
    QCalendarWidget *calendarioWidget;
    QPushButton *btnHora1330;
    QPushButton *btnHora1400;
    QPushButton *btnHora1430;
    QPushButton *btnHora1500;
    QPushButton *btnVoltar;

    void processarAgendamento(const std::string& horario);
};

#endif // TELADATAHORA_H