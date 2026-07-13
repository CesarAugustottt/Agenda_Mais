#ifndef APPOINTMENTIMPL_H
#define APPOINTMENTIMPL_H

#include "Appointment.h"
#include "handleBody.h"
#include <string>

/*!
 * @class AppointmentBody
 * @brief This class represents the concrete implementation of an Appointment.
 */
class AppointmentBody : public Body {
protected:
    /*! This attribute contains the patient. */
    User* patient;
    /*! This attribute contains the doctor. */
    User* doctor;
    /*! This attribute contains the date of the appointment. */
    std::string date;
    /*! This attribute contains the time of the appointment. */
    std::string time;
    /*! This attribute contains the status. */
    Status status;
    /*! This attribute contains the type of the appointment. */
    Specialty appointmentType;
    /*! This attribute contains the justification of the appointment. */
    std::string justificativa;

public:
    /*!
     * @brief This is the default constructor for the AppointmentBody Class.
     */
    AppointmentBody();
    /*!
     * @brief This is the default destructor for the AppointmentBody Class.
     */
    virtual ~AppointmentBody();

    User* getPatient() const;
    User* getDoctor() const;
    std::string getDate() const;
    std::string getTime() const;
    Status getStatus() const;
    Specialty getAppointmentType() const;
    std::string getJustificativa() const;

    void setPatient( User* patient);
    void setDoctor( User* doctor);
    void setDate(const std::string& date);
    void setTime(const std::string& time);
    void setStatus(const Status status);
    void setAppointmentType(const Specialty type);
    void setJustificativa(const std::string& justificativa);

    friend class Unit_Appointment; 
    friend class SystemBody; 
};

/*!
 * @class AppointmentHandle
 * @brief This class represents the handle of an Appointment.
 */
class AppointmentHandle : public Appointment, public Handle<AppointmentBody> {
protected:
    /*!
     * @brief This is the parameterized constructor for the AppointmentHandle Class.
     * * @param patient the patient from the appointment.
     * * @param doctor the doctor from the appointment.
     * * @param date the date of the appointment.
     * * @param time the time of the appointment.
     * * @param status the status of the appointment.
     * * @param type the type of the appointment.
     */
    AppointmentHandle(User* patient, User* doctor, const std::string& date, const std::string& time, const Status status, const Specialty type);

    /*!
     * @brief This is the default constructor for the AppointmentHandle Class.
     */
    AppointmentHandle();

public:
    /*!
     * @brief This is the default destructor for the AppointmentHandle Class.
     */
    virtual ~AppointmentHandle();

    User* getPatient() const override;
    User* getDoctor() const override;
    std::string getDate() const override;
    std::string getTime() const override;
    Status getStatus() const override;
    Specialty getAppointmentType() const override;
    std::string getJustificativa() const override;

    void setPatient( User* patient) override;
    void setDoctor( User* doctor) override;
    void setDate(const std::string& date) override;
    void setTime(const std::string& time) override;
    void setStatus(const Status status) override;
    void setAppointmentType(const Specialty type) override;
    void setJustificativa(const std::string& justificativa) override;

    friend class Unit_Appointment;
    friend class SystemBody; 
};

#endif // APPOINTMENTIMPL_H