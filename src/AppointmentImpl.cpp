#include "AppointmentImpl.h"

// =========================================================
// AppointmentBody Implementation
// =========================================================
AppointmentBody::AppointmentBody(){
    this->patient = nullptr;
    this->doctor = nullptr;
    this->date = "";
    this->time = "";
    this->status = Status::PENDING;
    this->appointmentType = Specialty::DENTIST;
    this->justificativa = "";
}

AppointmentBody::~AppointmentBody() {}

User* AppointmentBody::getPatient() const { return this->patient; }
User* AppointmentBody::getDoctor() const { return this->doctor; }
std::string AppointmentBody::getDate() const { return this->date; }
std::string AppointmentBody::getTime() const { return this->time; }
Status AppointmentBody::getStatus() const { return this->status; }
Specialty AppointmentBody::getAppointmentType() const { return this->appointmentType; }
std::string AppointmentBody::getJustificativa() const { return this->justificativa; }

void AppointmentBody::setPatient( User* patient) { this->patient = patient; }
void AppointmentBody::setDoctor( User* doctor) { this->doctor = doctor; }
void AppointmentBody::setDate(const std::string& date) { this->date = date; }
void AppointmentBody::setTime(const std::string& time) { this->time = time; }
void AppointmentBody::setStatus(const Status status) { this->status = status; }
void AppointmentBody::setAppointmentType(const Specialty type) { this->appointmentType = type; }
void AppointmentBody::setJustificativa(const std::string& justificativa) { this->justificativa = justificativa; }

// =========================================================
// AppointmentHandle Implementation
// =========================================================
AppointmentHandle::AppointmentHandle(User* patient, User* doctor, const std::string& date, const std::string& time, const Status status, const Specialty type){
    pImpl_->setPatient(patient);
    pImpl_->setDoctor(doctor);
    pImpl_->setDate(date);
    pImpl_->setTime(time);
    pImpl_->setStatus(status);
    pImpl_->setAppointmentType(type);
}

AppointmentHandle::AppointmentHandle(){}

AppointmentHandle::~AppointmentHandle() {}

User* AppointmentHandle::getPatient() const { return pImpl_->getPatient(); }
User* AppointmentHandle::getDoctor() const { return pImpl_->getDoctor(); }
std::string AppointmentHandle::getDate() const { return pImpl_->getDate(); }
std::string AppointmentHandle::getTime() const { return pImpl_->getTime(); }
Status AppointmentHandle::getStatus() const { return pImpl_->getStatus(); }
Specialty AppointmentHandle::getAppointmentType() const { return pImpl_->getAppointmentType(); }
std::string AppointmentHandle::getJustificativa() const { return pImpl_->getJustificativa(); }

void AppointmentHandle::setPatient( User* patient) { pImpl_->setPatient(patient); }
void AppointmentHandle::setDoctor( User* doctor) { pImpl_->setDoctor(doctor); }
void AppointmentHandle::setDate(const std::string& date) { pImpl_->setDate(date); }
void AppointmentHandle::setTime(const std::string& time) { pImpl_->setTime(time); }
void AppointmentHandle::setStatus(const Status status) { pImpl_->setStatus(status); }
void AppointmentHandle::setAppointmentType(const Specialty type) { pImpl_->setAppointmentType(type); }
void AppointmentHandle::setJustificativa(const std::string& justificativa) { pImpl_->setJustificativa(justificativa); }