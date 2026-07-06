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
    /*! This attribute contains the name of the patient. */
    std::string patientName;
    /*! This attribute contains the name of the doctor. */
    std::string doctorName;
    /*! This attribute contains the date of the appointment. */
    std::string date;
    /*! This attribute contains the time of the appointment. */
    std::string time;
    /*! This attribute contains the status. */
    Status status;
    /*! This attribute contains the type of the appointment. */
    Specialty appointmentType;

public:
    /*!
     * @brief This is the default constructor for the AppointmentBody Class.
     */
    AppointmentBody();
    /*!
     * @brief This is the default destructor for the AppointmentBody Class.
     */
    virtual ~AppointmentBody();

    std::string getPatientName() const;
    std::string getDoctorName() const;
    std::string getDate() const;
    std::string getTime() const;
    Status getStatus() const;
    Specialty getAppointmentType() const;

    void setPatientName(const std::string& name);
    void setDoctorName(const std::string& name);
    void setDate(const std::string& date);
    void setTime(const std::string& time);
    void setStatus(const Status status);
    void setAppointmentType(const Specialty type);

    friend class Unit_Appointment; 
};

/*!
 * @class AppointmentHandle
 * @brief This class represents the handle of an Appointment.
 */
class AppointmentHandle : public Appointment, public Handle<AppointmentBody> {
public:

    /*!
     * @brief This is the parameterized constructor for the AppointmentHandle Class.
     * * @param patient the name of the patient.
     * * @param doctor the name of the doctor.
     * * @param date the date of the appointment.
     * * @param time the time of the appointment.
     * * @param status the status of the appointment.
     * * @param type the type of the appointment.
     */
    AppointmentHandle(const std::string& patient, const std::string& doctor, 
                      const std::string& date, const std::string& time, const Status status,
                      const Specialty type);

    /*!
     * @brief This is the default destructor for the AppointmentHandle Class.
     */
    virtual ~AppointmentHandle();

    std::string getPatientName() const override;
    std::string getDoctorName() const override;
    std::string getDate() const override;
    std::string getTime() const override;
    Status getStatus() const override;
    Specialty getAppointmentType() const override;

    void setPatientName(const std::string& name) override;
    void setDoctorName(const std::string& name) override;
    void setDate(const std::string& date) override;
    void setTime(const std::string& time) override;
    void setStatus(const Status status) override;
    void setAppointmentType(const Specialty type) override;

    friend class Unit_Appointment;
};

#endif // APPOINTMENTIMPL_H