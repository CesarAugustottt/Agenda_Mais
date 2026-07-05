#ifndef APPOINTMENTIMPL_H
#define APPOINTMENTIMPL_H

#include "Appointment.h"
#include "handleBody.h"
#include <string>

class AppointmentBody : public Body {
protected:
    std::string patientName;
    std::string doctorName;
    std::string date;
    std::string time;
    std::string status; // e.g., "Pending", "Confirmed", "Declined"
    std::string reason; // Justificativa
    std::string appointmentType;

public:
    AppointmentBody(const std::string& patient, const std::string& doctor, 
                    const std::string& date, const std::string& time, 
                    const std::string& type);
    virtual ~AppointmentBody();

    std::string getPatientName() const;
    std::string getDoctorName() const;
    std::string getDate() const;
    std::string getTime() const;
    std::string getStatus() const;
    std::string getReason() const;
    std::string getAppointmentType() const;

    void setPatientName(const std::string& name);
    void setDoctorName(const std::string& name);
    void setDate(const std::string& date);
    void setTime(const std::string& time);
    void setStatus(const std::string& status);
    void setReason(const std::string& reason);
    void setAppointmentType(const std::string& type);

    friend class Unit_Appointment; 
};

class AppointmentHandle : public Appointment, public Handle<AppointmentBody> {
public:
    AppointmentHandle(const std::string& patient, const std::string& doctor, 
                      const std::string& date, const std::string& time, 
                      const std::string& type);
    virtual ~AppointmentHandle();

    std::string getPatientName() const override;
    std::string getDoctorName() const override;
    std::string getDate() const override;
    std::string getTime() const override;
    std::string getStatus() const override;
    std::string getReason() const override;
    std::string getAppointmentType() const override;

    void setPatientName(const std::string& name) override;
    void setDoctorName(const std::string& name) override;
    void setDate(const std::string& date) override;
    void setTime(const std::string& time) override;
    void setStatus(const std::string& status) override;
    void setReason(const std::string& reason) override;
    void setAppointmentType(const std::string& type) override;

    friend class Unit_Appointment;
};

#endif // APPOINTMENTIMPL_H