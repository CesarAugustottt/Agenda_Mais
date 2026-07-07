#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

enum class ReservationStatus {
    PENDING,
    APPROVED,
    REFUSED
};

class Medication; // Forward declaration para evitar dependências circulares

class Reservation {
public:
    virtual ~Reservation() {}

    virtual std::string getPatientCpf() const = 0;
    virtual Medication* getMedication() const = 0;
    virtual int getQuantity() const = 0;
    virtual std::string getPrescriptionPath() const = 0;
    virtual ReservationStatus getStatus() const = 0;
    virtual std::string getJustification() const = 0;

    virtual void setPatientCpf(const std::string& cpf) = 0;
    virtual void setMedication(Medication* medication) = 0;
    virtual void setQuantity(int quantity) = 0;
    virtual void setPrescriptionPath(const std::string& path) = 0;
    virtual void setStatus(ReservationStatus status) = 0;
    virtual void setJustification(const std::string& justification) = 0;
};

#endif // RESERVATION_H