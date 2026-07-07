#ifndef RESERVATIONIMPL_H
#define RESERVATIONIMPL_H

#include "Reservation.h"
#include "handleBody.h"
#include <string>

class ReservationBody : public Body {
protected:
    std::string patientCpf;
    Medication* medication;
    int quantity;
    std::string prescriptionPath;
    ReservationStatus status;
    std::string justification;

public:
    ReservationBody(const std::string& patientCpf, Medication* medication, int quantity, const std::string& prescriptionPath);
    virtual ~ReservationBody();

    std::string getPatientCpf() const;
    Medication* getMedication() const;
    int getQuantity() const;
    std::string getPrescriptionPath() const;
    ReservationStatus getStatus() const;
    std::string getJustification() const;

    void setPatientCpf(const std::string& cpf);
    void setMedication(Medication* med);
    void setQuantity(int qty);
    void setPrescriptionPath(const std::string& path);
    void setStatus(ReservationStatus stat);
    void setJustification(const std::string& just);
};

class ReservationHandle : public Reservation, public Handle<ReservationBody> {
public:
    ReservationHandle(const std::string& patientCpf, Medication* medication, int quantity, const std::string& prescriptionPath);
    virtual ~ReservationHandle();

    std::string getPatientCpf() const override;
    Medication* getMedication() const override;
    int getQuantity() const override;
    std::string getPrescriptionPath() const override;
    ReservationStatus getStatus() const override;
    std::string getJustification() const override;

    void setPatientCpf(const std::string& cpf) override;
    void setMedication(Medication* med) override;
    void setQuantity(int qty) override;
    void setPrescriptionPath(const std::string& path) override;
    void setStatus(ReservationStatus stat) override;
    void setJustification(const std::string& just) override;
};

#endif // RESERVATIONIMPL_H