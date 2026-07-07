#ifndef MEDICATIONSCONTROLLER_H
#define MEDICATIONSCONTROLLER_H

#include "MedicationImpl.h" // SEM 'S' (A entidade é singular)
#include "ReservationImpl.h"
#include <vector>
#include <string>

class MedicationsController { // COM 'S'
private:
    std::vector<MedicationHandle> medications;
    std::vector<ReservationHandle> pendingReservations;

public:
    MedicationsController();
    virtual ~MedicationsController();

    std::vector<MedicationHandle> getAllMedications() const;
    std::vector<ReservationHandle> getPendingReservations() const;

    void updateStock(size_t index, int newQuantity);
    void approveReservation(size_t index);
    void refuseReservation(size_t index, const std::string& justification);
};

#endif // MEDICATIONSCONTROLLER_H