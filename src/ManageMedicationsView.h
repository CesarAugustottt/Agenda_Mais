#ifndef MANAGEMEDICATIONSVIEW_H
#define MANAGEMEDICATIONSVIEW_H

#include <QWidget>
#include <QTableWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include "MedicationsController.h" // COM 'S'

class ManageMedicationsView : public QWidget {
    Q_OBJECT

public:
    explicit ManageMedicationsView(MedicationsController* controller, QWidget *parent = nullptr); // COM 'S'
    ~ManageMedicationsView();

    void refreshUI();

signals:
    void stockUpdatedImmediately();

private slots:
    void on_btnUpdateStock_clicked();
    void on_tableReservations_itemSelectionChanged();
    void on_btnApprove_clicked();
    void on_btnRefuse_clicked();

private:
    MedicationsController* controller; // COM 'S'

    QTabWidget *tabWidget;
    QWidget *tabStock;
    QWidget *tabReservations;

    QTableWidget *tableStock;
    QSpinBox *spinNewQuantity;
    QPushButton *btnUpdateStock;

    QTableWidget *tableReservations;
    QLabel *lblPrescriptionPreview;
    QLineEdit *txtJustification;
    QPushButton *btnApprove;
    QPushButton *btnRefuse;

    void setupUI();
};

#endif // MANAGEMEDICATIONSVIEW_H