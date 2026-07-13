#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include "MedicationsController.h"
#include "System.h"
#include "TelaAgenda.h"
#include "TelaStatusAgendamento.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(System* sys, QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_btnAbrirAgendamento_clicked();
    void on_btnAbrirCadastro_clicked();
    void on_btnGerenciarMedicamentos_clicked();
    void on_btnConsultarAgenda_clicked();
    void on_btnAcompanharStatus_clicked();

private:
    Ui::MainWindow *ui;
    
    QPushButton *btnAbrirAgendamento;
    QPushButton *btnAbrirCadastro;
    QPushButton *btnGerenciarMedicamentos; 
    QPushButton *btnConsultarAgenda;
    QPushButton *btnAcompanharStatus;
    
    QVBoxLayout *layoutCentral; //layout que organiza tudo

    MedicationsController *medicationsController;
    System* sistema; //ponteiro de system
};
#endif // MAINWINDOW_H
