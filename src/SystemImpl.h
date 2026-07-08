#ifndef SYSTEMIMPL_H
#define SYSTEMIMPL_H

#include "System.h"
#include "handleBody.h"
#include <vector>

class SystemBody : public Body {
protected:
    std::vector<User*> users;
    std::vector<Appointment*> appointments;
    std::vector<Medication*> medications;
    std::vector<Reservation*> reservations;

public:
    SystemBody() {}
    virtual ~SystemBody();

    // Métodos do ciclo de vida
    User* createUser(const std::string& name, const std::string& cpf, const std::string& email, const std::string& password, UserType type);
    Appointment* createAppointment(User* patient, User* doctor, const std::string& date, const std::string& time, Specialty esp);
    Medication* createMedication(const std::string& name, int quantity, bool requiresPrescription);
    Reservation* createReservation(const std::string& patientCpf, Medication* medication, int quantity, const std::string& prescriptionPath);

    void addUser(User* user);
    void addAppointment(Appointment* appointment);
    void addMedication(Medication* medication);
    void addReservation(Reservation* reservation);

    bool deleteUser(const std::string& cpf);
    bool deleteAppointment(Appointment* appointment);
    bool deleteMedication(const std::string& name);
    bool deleteReservation(Reservation* reservation);
};

class SystemHandle : public System, public Handle<SystemBody> {
public:
    SystemHandle();
    virtual ~SystemHandle();

    User* createUser(const std::string& name, const std::string& cpf, const std::string& email, const std::string& password, UserType type) override;
    Appointment* createAppointment(User* patient, User* doctor, const std::string& date, const std::string& time, Specialty esp) override;
    Medication* createMedication(const std::string& name, int quantity, bool requiresPrescription) override { return pImpl_->createMedication(name, quantity, requiresPrescription); } // Caso queira deixar inline, mas movido abaixo
    Reservation* createReservation(const std::string& patientCpf, Medication* medication, int quantity, const std::string& prescriptionPath) override;

    void addUser(User* user) override;
    void addAppointment(Appointment* appointment) override;
    void addMedication(Medication* medication) override;
    void addReservation(Reservation* reservation) override;

    bool deleteUser(const std::string& cpf) override;
    bool deleteAppointment(Appointment* appointment) override;
    bool deleteMedication(const std::string& name) override;
    bool deleteReservation(Reservation* reservation) override;
};

#endif // SYSTEMIMPL_H