#ifndef MEDICATIONSCONTROLLER_H
#define MEDICATIONSCONTROLLER_H

#include "System.h" // ADICIONADO: Inclui a interface do sistema
#include <vector>
#include <string>

class MedicationsController {
private:
    System* sistema; // ADICIONADO: Guarda o ponteiro do sistema global
    std::vector<Medication*> medications; // MODIFICADO: De MedicationHandle para Medication*
    std::vector<Reservation*> pendingReservations; // MODIFICADO: De ReservationHandle para Reservation*

public:
    // MODIFICADO: Agora recebe o System* no construtor
    MedicationsController(System* sys);
    virtual ~MedicationsController();

    // MODIFICADO: Retornam vetores de ponteiros das interfaces
    std::vector<Medication*> getAllMedications() const;
    std::vector<Reservation*> getPendingReservations() const;

    void updateStock(size_t index, int newQuantity);
    void approveReservation(size_t index);
    void refuseReservation(size_t index, const std::string& justification);
};

#endif // MEDICATIONSCONTROLLER_H