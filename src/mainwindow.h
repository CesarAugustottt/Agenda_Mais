#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

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
    // Deixamos apenas o slot do agendamento
    void on_btnAbrirAgendamento_clicked();

private:
    Ui::MainWindow *ui;

    // Deixamos apenas o botão de agendamento
    QPushButton *btnAbrirAgendamento;
    QVBoxLayout *layoutCentral;
};
#endif // MAINWINDOW_H