#ifndef RESERVATIONIMPL_H
#define RESERVATIONIMPL_H

#include "Reservation.h"
#include "handleBody.h"
#include <string>

/*!
 * @class ReservationBody
 * @brief This class represents the concrete implementation of a Reservation.
 */
class ReservationBody : public Body {
protected:
    /*! This attribute contains the patient cpf for the reservation. */
    std::string patientCpf;
    /*! This attribute contains a pointer to the medication of the reservation. */
    Medication* medication;
    /*! This attribute contains the medicine quantity for the reservation. */
    int quantity;
    /*! This attribute contains the digital file path of the prescription. */
    std::string prescriptionPath;
    /*! This attribute contains the current status of the reservation. */
    ReservationStatus status;
    /*! This attribute contains a justification for refusal if applicable. */
    std::string justification;

public:
    // construtores e destrutor
    /*!
     * @brief This is the default constructor for the ReservationBody Class.
     */
    ReservationBody();

    /*!
     * @brief This is the default destructor for the ReservationBody Class.
     */
    virtual ~ReservationBody();

    //getters e setters
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

    // Permite que a classe de controle gerencie o contêiner interno
    friend class SystemBody; 
};

/*!
 * @class ReservationHandle
 * @brief This class represents the handle of a Reservation.
 */
class ReservationHandle : public Reservation, public Handle<ReservationBody> {
protected:
    // construtores e destrutor
    /*!
     * @brief This is the parameterized constructor for the ReservationHandle Class.
     * * @param patientCpf the cpf of the patient making the reservation.
     * * @param medication the pointer to the medication object.
     * * @param quantity the amount of units requested.
     * * @param prescriptionPath the path string for the attached prescription document.
     */
    ReservationHandle(const std::string& patientCpf, Medication* medication, int quantity, const std::string& prescriptionPath);

    /*!
     * @brief This is the default constructor for the ReservationHandle Class.
     */
    ReservationHandle();
public:
    /*!
     * @brief This is the default destructor for the ReservationHandle Class.
     */
    virtual ~ReservationHandle();

    //getters e setters
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

    // Permite que a classe de controle gerencie o contêiner interno
    friend class SystemBody; 
};

#endif // RESERVATIONIMPL_H