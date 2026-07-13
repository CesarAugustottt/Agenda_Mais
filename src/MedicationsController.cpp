#include "MedicationsController.h"

// MODIFICADO: Construtor inicializa o sistema e usa as fábricas virtuais
MedicationsController::MedicationsController(System* sys) : sistema(sys) {

    // 1. Inserir Medicamentos usando o SYSTEM (padrão de fábrica)
    medications.push_back(sistema->createMedication("Dipirona 500mg", 50, false));
    medications.push_back(sistema->createMedication("Amoxicilina 500mg", 20, true));
    medications.push_back(sistema->createMedication("Ibuprofeno 400mg", 0, false));
    medications.push_back(sistema->createMedication("Clonazepam 2mg", 15, true));

    // 2. Inserir Reservas usando o SYSTEM
    pendingReservations.push_back(sistema->createReservation("111.222.333-44", medications[1], 2, "caminho/receita_amox.jpg"));
    pendingReservations.push_back(sistema->createReservation("555.666.777-88", medications[3], 1, "caminho/receita_clona.jpg"));
}

MedicationsController::~MedicationsController() {}

std::vector<Medication*> MedicationsController::getAllMedications() const {
    return medications;
}

std::vector<Reservation*> MedicationsController::getPendingReservations() const {
    return pendingReservations;
}

void MedicationsController::updateStock(size_t index, int newQuantity) {
    if (index < medications.size()) {
        medications[index]->setQuantity(newQuantity); // MODIFICADO: . para ->
    }
}

void MedicationsController::approveReservation(size_t index) {
    if (index < pendingReservations.size()) {
        pendingReservations[index]->setStatus(ReservationStatus::APPROVED); // MODIFICADO: . para ->
    }
}

void MedicationsController::refuseReservation(size_t index, const std::string& justification) {
    if (index < pendingReservations.size()) {
        pendingReservations[index]->setStatus(ReservationStatus::REFUSED); // MODIFICADO: . para ->
        pendingReservations[index]->setJustification(justification);       // MODIFICADO: . para ->

        // Se a sua lógica de devolução usar métodos internos, lembre-se de usar -> também:
        // int qte = pendingReservations[index]->getQuantity();
        // ...
    }
}