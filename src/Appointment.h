#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include "User.h"

// Definição dos Enums limitando as opções do Storyboard

/*!
 * @brief Enum class that defines the possible types of a status.
 */
enum class Status{
    PENDING,
    CONFIRMED,
    REJECTED
};

/*!
 * @brief Enumeration class defining the possible types of a doctor.
 */
enum class Specialty {
    DENTIST,
    NEUROLOGIST,
    PSYCHOLOGIST,
    CARDIOLOGIST,
    NUTRITIONIST,
    DERMATOLOGIST
};

/*!
 * @brief This class represents the interface of an Appointment as implemented in this code.
 * * It defines the abstract methods for appointment management.
 */

class Appointment {
public:
    /*!
     * @brief This is the default destructor for the Appointment Class.
     */
    virtual ~Appointment() {}
    
    //getters e setters
    /*!
     * @brief Returns the patientName attribute in the Appointment Class.
     * * @return User - the content patient attribute.
     */
    virtual User* getPatient() const = 0;

    /*!
     * @brief Returns the doctorName attribute in the Appointment Class.
     * * @return User - the content doctor attribute.
     */
    virtual User* getDoctor() const = 0;

    /*!
     * @brief Returns the date attribute in the Appointment Class.
     * * @return string - the content date attribute.
     */
    virtual std::string getDate() const = 0;

    /*!
     * @brief Returns the time attribute in the Appointment Class.
     * * @return string - the content time attribute.
     */
    virtual std::string getTime() const = 0;

    /*!
     * @brief Returns the status attribute in the Appointment Class.
     * * @return Status - the content status attribute.
     */
    virtual Status getStatus() const = 0;

    /*!
     * @brief Returns the appointmentType attribute in the Appointment Class.
     * * @return Specialty - the content appointmentType attribute.
     */
    virtual Specialty getAppointmentType() const = 0;

    /*!
     * @brief Retorna a justificativa cadastrada para a consulta (usada em caso de recusa).
     * @return std::string - a justificativa, ou string vazia se nenhuma foi registrada.
     */
    virtual std::string getJustificativa() const = 0;

    /*!
     * @brief Sets the patientName attribute in the Appointment Class.
     * * @param  patient will be set to the current appointment.
     */
    virtual void setPatient( User* patient) = 0;

    /*!
     * @brief Sets the doctorName attribute in the Appointment Class.
     * * @param doctor which will be set to the current appointment.
     */
    virtual void setDoctor( User* doctor) = 0;

    /*!
     * @brief Sets the date attribute in the Appointment Class.
     * * @param date which will be set to the current appointment.
     */
    virtual void setDate(const std::string& date) = 0;

    /*!
     * @brief Sets the time attribute in the Appointment Class.
     * * @param time which will be set to the current appointment.
     */
    virtual void setTime(const std::string& time) = 0;

    /*!
     * @brief Sets the status attribute in the Appointment Class.
     * * @param status which will be set to the current appointment.
     */
    virtual void setStatus(const Status status) = 0;

    /*!
     * @brief Sets the appointmentType attribute in the Appointment Class.
     * * @param type which will be set to the current appointment.
     */
    virtual void setAppointmentType(const Specialty type) = 0;

    /*!
     * @brief Define a justificativa da consulta (ex: motivo da recusa pela secretária/médico).
     * @param justificativa texto explicando o motivo.
     */
    virtual void setJustificativa(const std::string& justificativa) = 0;
};

#endif // APPOINTMENT_H