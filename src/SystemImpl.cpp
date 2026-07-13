#include "SystemImpl.h"
#include "UserImpl.h"
#include "AppointmentImpl.h"
#include "MedicationImpl.h"
#include "ReservationImpl.h"
#include <algorithm>

// IMPLEMENTAÇÂO BODY

SystemBody::~SystemBody() {
    // O destrutor garante que tudo o que sobrou no sistema seja deletado da RAM
    for (auto u : users) delete u;
    for (auto a : appointments) delete a;
    for (auto m : medications) delete m;
    for (auto r : reservations) delete r;
}

//fabrica global
System* System::createSystem() {
    return new SystemHandle(); 
}

//fabricas
User* SystemBody::createUser(const std::string& name, const std::string& cpf, const std::string& email, const std::string& password, UserType type) {
    User* u = new UserHandle(name, cpf, email, password, type);
    users.push_back(u);
    return u;
}

Appointment* SystemBody::createAppointment(User* patient, User* doctor, const std::string& date, const std::string& time, Specialty esp) {
    Appointment* a = new AppointmentHandle(patient, doctor, date, time, Status::PENDING, esp);
    appointments.push_back(a);
    return a;
}

Medication* SystemBody::createMedication(const std::string& name, int quantity, bool requiresPrescription) {
    Medication* m = new MedicationHandle(name, quantity, requiresPrescription);
    medications.push_back(m);
    return m;
}

Reservation* SystemBody::createReservation(const std::string& patientCpf, Medication* medication, int quantity, const std::string& prescriptionPath) {
    Reservation* r = new ReservationHandle(patientCpf, medication, quantity, prescriptionPath);
    reservations.push_back(r);
    return r;
}


void SystemBody::addUser(User* user) { 
    if(user) 
        users.push_back(user); 
}

void SystemBody::addAppointment(Appointment* appointment) { 
    if(appointment) 
        appointments.push_back(appointment); 
}

void SystemBody::addMedication(Medication* medication) { 
    if(medication) 
        medications.push_back(medication); 
}

void SystemBody::addReservation(Reservation* reservation) { 
    if(reservation) 
    reservations.push_back(reservation); 
}

std::vector<Appointment*> SystemBody::getAllAppointments() const {
    return appointments;
}

//Remoções Práticas com 'delete' 
bool SystemBody::deleteUser(const std::string& cpf) {
    for (auto it = users.begin(); it != users.end(); ++it) {
        if ((*it)->getCpf() == cpf) {
            delete *it; 
            users.erase(it);
            return true;
        }
    }
    return false;
}

bool SystemBody::deleteAppointment(Appointment* appointment) {
    auto it = std::find(appointments.begin(), appointments.end(), appointment);
    if (it != appointments.end()) {
        delete *it;
        appointments.erase(it);
        return true;
    }
    return false;
}

bool SystemBody::deleteMedication(const std::string& name) {
    for (auto it = medications.begin(); it != medications.end(); ++it) {
        if ((*it)->getName() == name) {
            delete *it;
            medications.erase(it);
            return true;
        }
    }
    return false;
}

bool SystemBody::deleteReservation(Reservation* reservation) {
    auto it = std::find(reservations.begin(), reservations.end(), reservation);
    if (it != reservations.end()) {
        delete *it;
        reservations.erase(it);
        return true;
    }
    return false;
}



///IMPLEMENTAÇÂO DO HANDLE
SystemHandle::SystemHandle() {}
SystemHandle::~SystemHandle() {}

User* SystemHandle::createUser(const std::string& name, const std::string& cpf, const std::string& email, const std::string& password, UserType type) {
    return pImpl_->createUser(name, cpf, email, password, type);
}

Appointment* SystemHandle::createAppointment(User* patient, User* doctor, const std::string& date, const std::string& time, Specialty esp) {
    return pImpl_->createAppointment(patient, doctor, date, time, esp);
}

Medication* SystemHandle::createMedication(const std::string& name, int quantity, bool requiresPrescription) {
    return pImpl_->createMedication(name, quantity, requiresPrescription);
}

Reservation* SystemHandle::createReservation(const std::string& patientCpf, Medication* medication, int quantity, const std::string& prescriptionPath) {
    return pImpl_->createReservation(patientCpf, medication, quantity, prescriptionPath);
}

std::vector<Appointment*> SystemHandle::getAllAppointments() const {
    return pImpl_->getAllAppointments();
}

void SystemHandle::addUser(User* user) { pImpl_->addUser(user); }
void SystemHandle::addAppointment(Appointment* appointment) { pImpl_->addAppointment(appointment); }
void SystemHandle::addMedication(Medication* medication) { pImpl_->addMedication(medication); }
void SystemHandle::addReservation(Reservation* reservation) { pImpl_->addReservation(reservation); }

bool SystemHandle::deleteUser(const std::string& cpf) { return pImpl_->deleteUser(cpf); }
bool SystemHandle::deleteAppointment(Appointment* appointment) { return pImpl_->deleteAppointment(appointment); }
bool SystemHandle::deleteMedication(const std::string& name) { return pImpl_->deleteMedication(name); }
bool SystemHandle::deleteReservation(Reservation* reservation) { return pImpl_->deleteReservation(reservation); }