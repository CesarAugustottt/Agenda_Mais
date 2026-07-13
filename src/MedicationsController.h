#ifndef MEDICATIONSCONTROLLER_H
#define MEDICATIONSCONTROLLER_H

#include "System.h"
#include <vector>
#include <string>

class MedicationsController {
private:
    System* sistema;
    std::vector<Medication*> medications;
    std::vector<Reservation*> pendingReservations;

public:
    MedicationsController(System* sys);
    virtual ~MedicationsController();

    std::vector<Medication*> getAllMedications() const;
    std::vector<Reservation*> getPendingReservations() const;

    void updateStock(size_t index, int newQuantity);
    void approveReservation(size_t index);
    void refuseReservation(size_t index, const std::string& justification);

    /*!
     * @brief Registra uma nova solicitação de medicamento feita pelo paciente.
     * Desconta o estoque imediatamente (reserva), criando a Reservation via System.
     * @param patientCpf CPF do paciente solicitante.
     * @param medication ponteiro para o medicamento solicitado.
     * @param quantity quantidade solicitada.
     * @param prescriptionPath caminho do arquivo de receita (pode ser vazio se não exigir).
     * @return Reservation* - ponteiro para a reserva criada, ou nullptr se estoque insuficiente.
     */
    Reservation* requestMedication(const std::string& patientCpf, Medication* medication, int quantity, const std::string& prescriptionPath);
};

#endif // MEDICATIONSCONTROLLER_H