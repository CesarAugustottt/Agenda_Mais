#ifndef TELAESPECIALIDADE_H
#define TELAESPECIALIDADE_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "../../src/Appointment.h"

class TelaEspecialidade : public QWidget {
    Q_OBJECT

public:
    explicit TelaEspecialidade(QWidget *parent = nullptr);
    ~TelaEspecialidade();

private:
    // Um slot para cada botão da interface
    void on_btnDentista_clicked();
    void on_btnNeurologista_clicked();
    void on_btnPsicologo_clicked();
    void on_btnCardiologista_clicked();
    void on_btnNutricionista_clicked();
    void on_btnDermatologista_clicked();

private:
    QVBoxLayout *layoutPrincipal;
    
    // Os 6 botões correspondentes aAs especialidades do seu Enum
    QPushButton *btnDentista;
    QPushButton *btnNeurologista;
    QPushButton *btnPsicologo;
    QPushButton *btnCardiologista;
    QPushButton *btnNutricionista;
    QPushButton *btnDermatologista;

    void abrirProximaTela(Specialty esp);
};

#endif