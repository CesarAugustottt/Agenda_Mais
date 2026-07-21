#include "SystemImpl.h"
#include "UserImpl.h"
#include "AppointmentImpl.h"
#include "MedicationImpl.h"
#include "ReservationImpl.h"
#include "Database.h"
#include <algorithm>
#include <map>

// IMPLEMENTAÇÂO BODY

SystemBody::SystemBody() {
    // Abre (ou cria) o arquivo agenda.db e garante que as tabelas existam.
    Database::instance().open();
    // Repovoa os vectors em memória com tudo que já estava salvo em execuções anteriores.
    loadFromDatabase();
}

SystemBody::~SystemBody() {
    // O destrutor garante que tudo o que sobrou no sistema seja deletado da RAM
    for (auto u : users) delete u;
    for (auto a : appointments) delete a;
    for (auto m : medications) delete m;
    for (auto r : reservations) delete r;
}

void SystemBody::loadFromDatabase() {
    // 1. Usuários primeiro, pois Appointments referenciam pacientes/médicos por cpf.
    std::map<std::string, User*> usersByCpf;
    for (const auto& rec : userRepo.loadAll()) {
        User* u = new UserHandle(rec.name, rec.cpf, rec.email, rec.password, rec.type);
        if (!rec.active) u->deactivate();
        users.push_back(u);
        usersByCpf[rec.cpf] = u;
    }

    // 2. Medicamentos, pois Reservations referenciam medicamentos por nome.
    std::map<std::string, Medication*> medicationsByName;
    for (const auto& rec : medicationRepo.loadAll()) {
        Medication* m = new MedicationHandle(rec.name, rec.quantity, rec.requiresPrescription);
        medications.push_back(m);
        medicationsByName[rec.name] = m;
    }

    // 3. Appointments, ligando paciente/médico já carregados.
    for (const auto& rec : appointmentRepo.loadAll()) {
        User* patient = usersByCpf.count(rec.patientCpf) ? usersByCpf[rec.patientCpf] : nullptr;
        User* doctor = usersByCpf.count(rec.doctorCpf) ? usersByCpf[rec.doctorCpf] : nullptr;

        Appointment* a = new AppointmentHandle(patient, doctor, rec.date, rec.time,
                                                static_cast<Status>(rec.status),
                                                static_cast<Specialty>(rec.specialty));
        a->setJustificativa(rec.justificativa);
        appointments.push_back(a);
        appointmentIds[a] = rec.id;
    }

    // 4. Reservations, ligando o medicamento já carregado pelo nome.
    for (const auto& rec : reservationRepo.loadAll()) {
        Medication* med = medicationsByName.count(rec.medicationName) ? medicationsByName[rec.medicationName] : nullptr;

        Reservation* r = new ReservationHandle(rec.patientCpf, med, rec.quantity, rec.prescriptionPath);
        r->setStatus(static_cast<ReservationStatus>(rec.status));
        r->setJustification(rec.justification);
        reservations.push_back(r);
        reservationIds[r] = rec.id;
    }
}

//fabrica global
System* System::createSystem() {
    return new SystemHandle(); 
}

//fabricas
User* SystemBody::createUser(const std::string& name, const std::string& cpf, const std::string& email, const std::string& password, UserType type) {
    User* u = new UserHandle(name, cpf, email, password, type);
    users.push_back(u);
    userRepo.insertUser(name, cpf, email, password, type, true);
    return u;
}

Appointment* SystemBody::createAppointment(User* patient, User* doctor, const std::string& date, const std::string& time, Specialty esp) {
    Appointment* a = new AppointmentHandle(patient, doctor, date, time, Status::PENDING, esp);
    appointments.push_back(a);

    std::string patientCpf = patient ? patient->getCpf() : "";
    std::string doctorCpf = doctor ? doctor->getCpf() : "";
    int id = appointmentRepo.insertAppointment(patientCpf, doctorCpf, date, time,
                                                static_cast<int>(Status::PENDING), static_cast<int>(esp), "");
    if (id >= 0) appointmentIds[a] = id;
    return a;
}

Medication* SystemBody::createMedication(const std::string& name, int quantity, bool requiresPrescription) {
    Medication* m = new MedicationHandle(name, quantity, requiresPrescription);
    medications.push_back(m);
    medicationRepo.insertMedication(name, quantity, requiresPrescription);
    return m;
}

Reservation* SystemBody::createReservation(const std::string& patientCpf, Medication* medication, int quantity, const std::string& prescriptionPath) {
    Reservation* r = new ReservationHandle(patientCpf, medication, quantity, prescriptionPath);
    reservations.push_back(r);

    std::string medName = medication ? medication->getName() : "";
    int id = reservationRepo.insertReservation(patientCpf, medName, quantity, prescriptionPath,
                                                static_cast<int>(ReservationStatus::PENDING), "");
    if (id >= 0) reservationIds[r] = id;
    return r;
}


void SystemBody::addUser(User* user) {
    if (user) {
        users.push_back(user);
        userRepo.insertUser(user->getName(), user->getCpf(), user->getEmail(), "", user->getType(), user->isActive());
    }
}

void SystemBody::addAppointment(Appointment* appointment) {
    if (appointment) {
        appointments.push_back(appointment);
        std::string patientCpf = appointment->getPatient() ? appointment->getPatient()->getCpf() : "";
        std::string doctorCpf = appointment->getDoctor() ? appointment->getDoctor()->getCpf() : "";
        int id = appointmentRepo.insertAppointment(patientCpf, doctorCpf, appointment->getDate(), appointment->getTime(),
                                                    static_cast<int>(appointment->getStatus()),
                                                    static_cast<int>(appointment->getAppointmentType()),
                                                    appointment->getJustificativa());
        if (id >= 0) appointmentIds[appointment] = id;
    }
}

void SystemBody::addMedication(Medication* medication) {
    if (medication) {
        medications.push_back(medication);
        medicationRepo.insertMedication(medication->getName(), medication->getQuantity(), medication->requiresPrescription());
    }
}

void SystemBody::addReservation(Reservation* reservation) {
    if (reservation) {
        reservations.push_back(reservation);
        std::string medName = reservation->getMedication() ? reservation->getMedication()->getName() : "";
        int id = reservationRepo.insertReservation(reservation->getPatientCpf(), medName, reservation->getQuantity(),
                                                     reservation->getPrescriptionPath(),
                                                     static_cast<int>(reservation->getStatus()),
                                                     reservation->getJustification());
        if (id >= 0) reservationIds[reservation] = id;
    }
}

void SystemBody::updateAppointment(Appointment* appointment) {
    if (!appointment || !appointmentIds.count(appointment)) return;
    std::string patientCpf = appointment->getPatient() ? appointment->getPatient()->getCpf() : "";
    std::string doctorCpf = appointment->getDoctor() ? appointment->getDoctor()->getCpf() : "";
    appointmentRepo.updateAppointment(appointmentIds[appointment], patientCpf, doctorCpf,
                                       appointment->getDate(), appointment->getTime(),
                                       static_cast<int>(appointment->getStatus()),
                                       static_cast<int>(appointment->getAppointmentType()),
                                       appointment->getJustificativa());
}

void SystemBody::updateMedication(Medication* medication) {
    if (!medication) return;
    medicationRepo.updateMedication(medication->getName(), medication->getQuantity(), medication->requiresPrescription());
}

void SystemBody::updateReservation(Reservation* reservation) {
    if (!reservation || !reservationIds.count(reservation)) return;
    std::string medName = reservation->getMedication() ? reservation->getMedication()->getName() : "";
    reservationRepo.updateReservation(reservationIds[reservation], reservation->getPatientCpf(), medName,
                                       reservation->getQuantity(), reservation->getPrescriptionPath(),
                                       static_cast<int>(reservation->getStatus()), reservation->getJustification());
}

std::vector<Appointment*> SystemBody::getAllAppointments() const {
    return appointments;
}

std::vector<Medication*> SystemBody::getAllMedications() const {
    return medications;
}

std::vector<Reservation*> SystemBody::getAllReservations() const {
    return reservations;
}

//Remoções Práticas com 'delete' 
bool SystemBody::deleteUser(const std::string& cpf) {
    for (auto it = users.begin(); it != users.end(); ++it) {
        if ((*it)->getCpf() == cpf) {
            delete *it; 
            users.erase(it);
            userRepo.deleteUser(cpf);
            return true;
        }
    }
    return false;
}

bool SystemBody::deleteAppointment(Appointment* appointment) {
    auto it = std::find(appointments.begin(), appointments.end(), appointment);
    if (it != appointments.end()) {
        if (appointmentIds.count(appointment)) {
            appointmentRepo.deleteAppointment(appointmentIds[appointment]);
            appointmentIds.erase(appointment);
        }
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
            medicationRepo.deleteMedication(name);
            return true;
        }
    }
    return false;
}

bool SystemBody::deleteReservation(Reservation* reservation) {
    auto it = std::find(reservations.begin(), reservations.end(), reservation);
    if (it != reservations.end()) {
        if (reservationIds.count(reservation)) {
            reservationRepo.deleteReservation(reservationIds[reservation]);
            reservationIds.erase(reservation);
        }
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

std::vector<Medication*> SystemHandle::getAllMedications() const {
    return pImpl_->getAllMedications();
}

std::vector<Reservation*> SystemHandle::getAllReservations() const {
    return pImpl_->getAllReservations();
}

void SystemHandle::addUser(User* user) { pImpl_->addUser(user); }
void SystemHandle::addAppointment(Appointment* appointment) { pImpl_->addAppointment(appointment); }
void SystemHandle::addMedication(Medication* medication) { pImpl_->addMedication(medication); }
void SystemHandle::addReservation(Reservation* reservation) { pImpl_->addReservation(reservation); }

void SystemHandle::updateAppointment(Appointment* appointment) { pImpl_->updateAppointment(appointment); }
void SystemHandle::updateMedication(Medication* medication) { pImpl_->updateMedication(medication); }
void SystemHandle::updateReservation(Reservation* reservation) { pImpl_->updateReservation(reservation); }

bool SystemHandle::deleteUser(const std::string& cpf) { return pImpl_->deleteUser(cpf); }
bool SystemHandle::deleteAppointment(Appointment* appointment) { return pImpl_->deleteAppointment(appointment); }
bool SystemHandle::deleteMedication(const std::string& name) { return pImpl_->deleteMedication(name); }
bool SystemHandle::deleteReservation(Reservation* reservation) { return pImpl_->deleteReservation(reservation); }