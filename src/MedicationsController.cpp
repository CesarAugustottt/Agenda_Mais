#include "MedicationsController.h"

MedicationsController::MedicationsController(System* sys) : sistema(sys) {
    medications.push_back(sistema->createMedication("Dipirona 500mg", 50, false));
    medications.push_back(sistema->createMedication("Amoxicilina 500mg", 20, true));
    medications.push_back(sistema->createMedication("Ibuprofeno 400mg", 0, false));
    medications.push_back(sistema->createMedication("Clonazepam 2mg", 15, true));

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
        medications[index]->setQuantity(newQuantity);
    }
}

void MedicationsController::approveReservation(size_t index) {
    if (index < pendingReservations.size()) {
        pendingReservations[index]->setStatus(ReservationStatus::APPROVED);
        // Estoque já foi descontado no momento da solicitação (requestMedication),
        // então aprovar só confirma o que já estava reservado.
    }
}

void MedicationsController::refuseReservation(size_t index, const std::string& justification) {
    if (index < pendingReservations.size()) {
        Reservation* reserva = pendingReservations[index];
        reserva->setStatus(ReservationStatus::REFUSED);
        reserva->setJustification(justification);

        // Devolve a quantidade reservada ao estoque, já que a solicitação foi negada.
        Medication* med = reserva->getMedication();
        if (med) {
            med->setQuantity(med->getQuantity() + reserva->getQuantity());
        }
    }
}

Reservation* MedicationsController::requestMedication(const std::string& patientCpf, Medication* medication, int quantity, const std::string& prescriptionPath) {
    if (!medication) return nullptr;
    if (medication->getQuantity() < quantity) return nullptr; // estoque insuficiente

    medication->decreaseStock(quantity); // reserva o estoque imediatamente

    Reservation* reserva = sistema->createReservation(patientCpf, medication, quantity, prescriptionPath);
    pendingReservations.push_back(reserva);
    return reserva;
}