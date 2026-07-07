/**
 * @file MedicationsController.cpp
 * @brief Implementation of the MedicationController class.
 */

#include "MedicationsController.h"

MedicationsController::MedicationsController() {
    // ==============================================================
    // MOCK DATA: Dados fictícios para testar a interface
    // ==============================================================
    
    // 1. Inserir Medicamentos (Nome, Quantidade no Estoque, Exige Receita?)
    medications.push_back(MedicationHandle("Dipirona 500mg", 50, false));
    medications.push_back(MedicationHandle("Amoxicilina 500mg", 20, true));
    medications.push_back(MedicationHandle("Ibuprofeno 400mg", 0, false)); // Estoque zerado de propósito!
    medications.push_back(MedicationHandle("Clonazepam 2mg", 15, true));

    // 2. Inserir Reservas Falsas feitas por pacientes
    // (CPF, Ponteiro para o Medicamento, Quantidade, Caminho da Foto da Receita)
    pendingReservations.push_back(ReservationHandle("111.222.333-44", &medications[1], 2, "caminho/receita_amox.jpg"));
    pendingReservations.push_back(ReservationHandle("555.666.777-88", &medications[3], 1, "caminho/receita_clona.jpg"));
}

MedicationsController::~MedicationsController() {}

std::vector<MedicationHandle> MedicationsController::getAllMedications() const {
    return medications;
}

std::vector<ReservationHandle> MedicationsController::getPendingReservations() const {
    return pendingReservations;
}

void MedicationsController::updateStock(size_t index, int newQuantity) {
    if (index < medications.size()) {
        medications[index].setQuantity(newQuantity);
    }
}

void MedicationsController::approveReservation(size_t index) {
    if (index < pendingReservations.size()) {
        pendingReservations[index].setStatus(ReservationStatus::APPROVED);
    }
}

void MedicationsController::refuseReservation(size_t index, const std::string& justification) {
    if (index < pendingReservations.size()) {
        pendingReservations[index].setStatus(ReservationStatus::REFUSED);
        pendingReservations[index].setJustification(justification);
        
        // REGRA DE NEGÓCIO: Se foi recusado, devolve a quantidade para o stock da clínica
        Medication* med = pendingReservations[index].getMedication();
        if (med) {
            med->setQuantity(med->getQuantity() + pendingReservations[index].getQuantity());
        }
    }
}