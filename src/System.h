#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include "User.h"
#include "Appointment.h"
#include "Medication.h"
#include "Reservation.h"

class System {
public:
    virtual ~System() {}

    //Fabricas
    virtual User* createUser(const std::string& name, const std::string& cpf, const std::string& email, const std::string& password, UserType type) = 0;
    virtual Appointment* createAppointment(User* patient, User* doctor, const std::string& date, const std::string& time, Specialty esp) = 0;
    virtual Medication* createMedication(const std::string& name, int quantity, bool requiresPrescription) = 0;
    virtual Reservation* createReservation(const std::string& patientCpf, Medication* medication, int quantity, const std::string& prescriptionPath) = 0;

    // metodos de adicionar
    virtual void addUser(User* user) = 0;
    virtual void addAppointment(Appointment* appointment) = 0;
    virtual void addMedication(Medication* medication) = 0;
    virtual void addReservation(Reservation* reservation) = 0;

    // metodos de delete
    virtual bool deleteUser(const std::string& cpf) = 0;
    virtual bool deleteAppointment(Appointment* appointment) = 0;
    virtual bool deleteMedication(const std::string& name) = 0;
    virtual bool deleteReservation(Reservation* reservation) = 0;
};

#endif // SYSTEM_H