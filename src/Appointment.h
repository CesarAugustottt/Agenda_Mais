#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>

class Appointment {
public:
    virtual ~Appointment() {}
    
    virtual std::string getPatientName() const = 0;
    virtual std::string getDoctorName() const = 0;
    virtual std::string getDate() const = 0;
    virtual std::string getTime() const = 0;
    virtual std::string getStatus() const = 0;
    virtual std::string getReason() const = 0;
    virtual std::string getAppointmentType() const = 0;

    virtual void setPatientName(const std::string& name) = 0;
    virtual void setDoctorName(const std::string& name) = 0;
    virtual void setDate(const std::string& date) = 0;
    virtual void setTime(const std::string& time) = 0;
    virtual void setStatus(const std::string& status) = 0;
    virtual void setReason(const std::string& reason) = 0;
    virtual void setAppointmentType(const std::string& type) = 0;
};

#endif // APPOINTMENT_H