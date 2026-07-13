#include "ManageMedicationsView.h"
#include <QMessageBox>
#include <QPixmap>
#include <QHeaderView>

ManageMedicationsView::ManageMedicationsView(MedicationsController* controller, QWidget *parent)
    : QWidget(parent), controller(controller) {

    setupUI();
    refreshUI(); // Agora isto vai preencher as tabelas!
}

ManageMedicationsView::~ManageMedicationsView() {
}

void ManageMedicationsView::setupUI() {
    this->resize(650, 500);
    this->setWindowTitle("Secretária - Gerenciar Medicamentos");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    tabWidget = new QTabWidget(this);

    // ==========================================
    // ABA 1: GERENCIAR ESTOQUE
    // ==========================================
    tabStock = new QWidget();
    QVBoxLayout *stockLayout = new QVBoxLayout(tabStock);

    tableStock = new QTableWidget(0, 3, this);
    tableStock->setHorizontalHeaderLabels({"Nome do Medicamento", "Quantidade", "Exige Receita"});
    tableStock->horizontalHeader()->setStretchLastSection(true);
    stockLayout->addWidget(tableStock);

    QHBoxLayout *stockControls = new QHBoxLayout();
    stockControls->addWidget(new QLabel("Nova Quantidade:", this));

    spinNewQuantity = new QSpinBox(this);
    spinNewQuantity->setMaximum(10000);
    stockControls->addWidget(spinNewQuantity);

    btnUpdateStock = new QPushButton("Atualizar Estoque", this);
    stockControls->addWidget(btnUpdateStock);

    stockLayout->addLayout(stockControls);

    // ==========================================
    // ABA 2: VALIDAR RECEITAS E RESERVAS
    // ==========================================
    tabReservations = new QWidget();
    QVBoxLayout *resLayout = new QVBoxLayout(tabReservations);

    // Adicionámos 4 colunas em vez de 3 para mostrar o Status
    tableReservations = new QTableWidget(0, 4, this);
    tableReservations->setHorizontalHeaderLabels({"CPF Paciente", "Medicamento", "Qtd Solicitada", "Status"});
    tableReservations->horizontalHeader()->setStretchLastSection(true);
    resLayout->addWidget(tableReservations);

    lblPrescriptionPreview = new QLabel("Selecione uma reserva acima para visualizar a receita anexada.", this);
    lblPrescriptionPreview->setMinimumHeight(150);
    lblPrescriptionPreview->setAlignment(Qt::AlignCenter);
    lblPrescriptionPreview->setStyleSheet("border: 1px dashed gray; background-color: #f0f0f0; color: black;"); // Correção do texto escuro
    resLayout->addWidget(lblPrescriptionPreview);

    QHBoxLayout *resControls = new QHBoxLayout();
    resControls->addWidget(new QLabel("Justificativa da Recusa:", this));

    txtJustification = new QLineEdit(this);
    resControls->addWidget(txtJustification);

    btnApprove = new QPushButton("Aprovar Reserva", this);
    btnApprove->setStyleSheet("background-color: #4CAF50; color: white; font-weight: bold; padding: 5px;");

    btnRefuse = new QPushButton("Recusar Reserva", this);
    btnRefuse->setStyleSheet("background-color: #F44336; color: white; font-weight: bold; padding: 5px;");

    resControls->addWidget(btnApprove);
    resControls->addWidget(btnRefuse);

    resLayout->addLayout(resControls);

    tabWidget->addTab(tabStock, "Controle de Estoque");
    tabWidget->addTab(tabReservations, "Validação de Receitas");
    mainLayout->addWidget(tabWidget);

    connect(btnUpdateStock, &QPushButton::clicked, this, &ManageMedicationsView::on_btnUpdateStock_clicked);
    connect(tableReservations, &QTableWidget::itemSelectionChanged, this, &ManageMedicationsView::on_tableReservations_itemSelectionChanged);
    connect(btnApprove, &QPushButton::clicked, this, &ManageMedicationsView::on_btnApprove_clicked);
    connect(btnRefuse, &QPushButton::clicked, this, &ManageMedicationsView::on_btnRefuse_clicked);
}

void ManageMedicationsView::refreshUI() {
    // 1. Atualizar a Tabela de Estoque
    auto meds = controller->getAllMedications();
    tableStock->setRowCount(0); // Limpa as linhas antigas
    for (int i = 0; i < (int)meds.size(); ++i) {
        tableStock->insertRow(i);
        tableStock->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(meds[i]->getName())));
        tableStock->setItem(i, 1, new QTableWidgetItem(QString::number(meds[i]->getQuantity())));
        tableStock->setItem(i, 2, new QTableWidgetItem(meds[i]->requiresPrescription() ? "Sim" : "Não"));
    }

    // 2. Atualizar a Tabela de Reservas
    auto pendings = controller->getPendingReservations();
    tableReservations->setRowCount(0);
    for (int i = 0; i < (int)pendings.size(); ++i) {
        tableReservations->insertRow(i);
        tableReservations->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(pendings[i]->getPatientCpf())));

        QString medName = pendings[i]->getMedication() ? QString::fromStdString(pendings[i]->getMedication()->getName()) : "Desconhecido";
        tableReservations->setItem(i, 1, new QTableWidgetItem(medName));
        tableReservations->setItem(i, 2, new QTableWidgetItem(QString::number(pendings[i]->getQuantity())));

        QString statusStr = "Pendente";
        if (pendings[i]->getStatus() == ReservationStatus::APPROVED) statusStr = "Aprovado";
        else if (pendings[i]->getStatus() == ReservationStatus::REFUSED) statusStr = "Recusado";

        tableReservations->setItem(i, 3, new QTableWidgetItem(statusStr));
    }
}

void ManageMedicationsView::on_btnUpdateStock_clicked() {
    int currentRow = tableStock->currentRow();
    if (currentRow >= 0) {
        int newQty = spinNewQuantity->value();
        controller->updateStock(currentRow, newQty);
        emit stockUpdatedImmediately();
        refreshUI(); // Atualiza a tela para mostrar a nova quantidade
        QMessageBox::information(this, "Sucesso", "Estoque atualizado com sucesso!");
    } else {
        QMessageBox::warning(this, "Aviso", "Por favor, selecione um medicamento na tabela.");
    }
}

void ManageMedicationsView::on_tableReservations_itemSelectionChanged() {
    int currentRow = tableReservations->currentRow();
    if (currentRow >= 0) {
        auto pending = controller->getPendingReservations();
        if (currentRow < (int)pending.size()) {
            QString imagePath = QString::fromStdString(pending[currentRow]->getPrescriptionPath());
            QPixmap prescriptionImage(imagePath);
            if (!prescriptionImage.isNull()) {
                lblPrescriptionPreview->setPixmap(prescriptionImage.scaled(
                    lblPrescriptionPreview->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            } else {
                lblPrescriptionPreview->setText("Documento de receita não encontrado.\nCaminho: " + imagePath);
            }
        }
    }
}

void ManageMedicationsView::on_btnApprove_clicked() {
    int currentRow = tableReservations->currentRow();
    if (currentRow >= 0) {
        if (controller->getPendingReservations()[currentRow]->getStatus() != ReservationStatus::PENDING) {
            QMessageBox::warning(this, "Aviso", "Esta reserva já foi avaliada!");
            return;
        }
        controller->approveReservation(currentRow);
        QMessageBox::information(this, "Aprovado", "Reserva de medicamento aprovada!");
        refreshUI();
    } else {
        QMessageBox::warning(this, "Aviso", "Selecione uma reserva na tabela.");
    }
}

void ManageMedicationsView::on_btnRefuse_clicked() {
    int currentRow = tableReservations->currentRow();
    QString justification = txtJustification->text();

    if (currentRow >= 0) {
        if (controller->getPendingReservations()[currentRow]->getStatus() != ReservationStatus::PENDING) {
            QMessageBox::warning(this, "Aviso", "Esta reserva já foi avaliada!");
            return;
        }
        if (justification.isEmpty()) {
            QMessageBox::warning(this, "Aviso", "Para recusar, tem de preencher a justificativa.");
            return;
        }
        controller->refuseReservation(currentRow, justification.toStdString());
        emit stockUpdatedImmediately();
        QMessageBox::information(this, "Recusado", "Reserva recusada e quantidade devolvida ao estoque.");
        refreshUI();
    } else {
        QMessageBox::warning(this, "Aviso", "Selecione uma reserva na tabela.");
    }
}