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
    void on_btnAbrirAgendamento_clicked();
    void on_btnAbrirCadastro_clicked();

private:
    Ui::MainWindow *ui;
    QPushButton *btnAbrirAgendamento;
    QPushButton *btnAbrirCadastro;
    QVBoxLayout *layoutCentral;
};
#endif // MAINWINDOW_H
