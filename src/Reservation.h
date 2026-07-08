#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

/*!
 * @brief Enum class that defines the possible status of a medicine reservation.
 */
enum class ReservationStatus {
    PENDING,
    APPROVED,
    REFUSED
};

class Medication; // Forward declaration to prevent circular dependencies

/*!
 * @brief This class represents the interface of a Reservation as implemented in this code.
 * * It defines the abstract methods for medicine reservation management.
 */
class Reservation {
public:
    /*!
     * @brief This is the default destructor for the Reservation Class.
     */
    virtual ~Reservation() {}

    /*!
     * @brief Returns the patient cpf attribute in the Reservation Class.
     * * @return string - the content patient cpf attribute.
     */
    virtual std::string getPatientCpf() const = 0;

    /*!
     * @brief Returns the medication pointer attribute in the Reservation Class.
     * * @return Medication* - the content medication pointer attribute.
     */
    virtual Medication* getMedication() const = 0;

    /*!
     * @brief Returns the quantity attribute in the Reservation Class.
     * * @return int - the content quantity attribute.
     */
    virtual int getQuantity() const = 0;

    /*!
     * @brief Returns the prescription path attribute in the Reservation Class.
     * * @return string - the content prescription path attribute.
     */
    virtual std::string getPrescriptionPath() const = 0;

    /*!
     * @brief Returns the status attribute in the Reservation Class.
     * * @return ReservationStatus - the content status attribute.
     */
    virtual ReservationStatus getStatus() const = 0;

    /*!
     * @brief Returns the justification attribute in the Reservation Class.
     * * @return string - the content justification attribute.
     */
    virtual std::string getJustification() const = 0;

    /*!
     * @brief Sets the patient cpf attribute in the Reservation Class.
     * * @param cpf which will be set to the current reservation.
     */
    virtual void setPatientCpf(const std::string& cpf) = 0;

    /*!
     * @brief Sets the medication attribute in the Reservation Class.
     * * @param medication which will be set to the current reservation.
     */
    virtual void setMedication(Medication* medication) = 0;

    /*!
     * @brief Sets the quantity attribute in the Reservation Class.
     * * @param quantity which will be set to the current reservation.
     */
    virtual void setQuantity(int quantity) = 0;

    /*!
     * @brief Sets the prescription path attribute in the Reservation Class.
     * * @param path which will be set to the current reservation.
     */
    virtual void setPrescriptionPath(const std::string& path) = 0;

    /*!
     * @brief Sets the status attribute in the Reservation Class.
     * * @param status which will be set to the current reservation.
     */
    virtual void setStatus(ReservationStatus status) = 0;

    /*!
     * @brief Sets the justification attribute in the Reservation Class.
     * * @param justification which will be set to the current reservation.
     */
    virtual void setJustification(const std::string& justification) = 0;
};

#endif // RESERVATION_H