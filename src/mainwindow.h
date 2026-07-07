#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include "MedicationsController.h" // COM 'S'

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_btnAbrirAgendamento_clicked();
    void on_btnAbrirCadastro_clicked();
    void on_btnGerenciarMedicamentos_clicked();

private:
    Ui::MainWindow *ui;
    
    QPushButton *btnAbrirAgendamento;
    QPushButton *btnAbrirCadastro;
    QPushButton *btnGerenciarMedicamentos; 
    
    QVBoxLayout *layoutCentral;

    MedicationsController *medicationsController; // COM 'S'
};
#endif // MAINWINDOW_H