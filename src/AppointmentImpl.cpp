#include "AppointmentImpl.h"

// =========================================================
// AppointmentBody Implementation
// =========================================================
AppointmentBody::AppointmentBody(){
  this->patientName = "";
  this->doctorName = "";
  this->date = "";
  this->time = "";
  this->status = Status::PENDING;
  this->appointmentType = Specialty::DENTIST;
}

AppointmentBody::~AppointmentBody() {}

std::string AppointmentBody::getPatientName() const { return this->patientName; }
std::string AppointmentBody::getDoctorName() const { return this->doctorName; }
std::string AppointmentBody::getDate() const { return this->date; }
std::string AppointmentBody::getTime() const { return this->time; }
Status AppointmentBody::getStatus() const { return this->status; }
Specialty AppointmentBody::getAppointmentType() const { return this->appointmentType; }

void AppointmentBody::setPatientName(const std::string& name) { this->patientName = name; }
void AppointmentBody::setDoctorName(const std::string& name) { this->doctorName = name; }
void AppointmentBody::setDate(const std::string& date) { this->date = date; }
void AppointmentBody::setTime(const std::string& time) { this->time = time; }
void AppointmentBody::setStatus(const Status status) { this->status = status; }
void AppointmentBody::setAppointmentType(const Specialty type) { this->appointmentType = type; }

// =========================================================
// AppointmentHandle Implementation
// =========================================================
AppointmentHandle::AppointmentHandle(const std::string& patient, const std::string& doctor, const std::string& date, const std::string& time, const Status status, const Specialty type){
  pImpl_->setPatientName(patient);
  pImpl_->setDoctorName(doctor);
  pImpl_->setDate(date);
  pImpl_->setTime(time);
  pImpl_->setStatus(status);
  pImpl_->setAppointmentType(type);
}

AppointmentHandle::~AppointmentHandle() {}

std::string AppointmentHandle::getPatientName() const { return pImpl_->getPatientName(); }
std::string AppointmentHandle::getDoctorName() const { return pImpl_->getDoctorName(); }
std::string AppointmentHandle::getDate() const { return pImpl_->getDate(); }
std::string AppointmentHandle::getTime() const { return pImpl_->getTime(); }
Status AppointmentHandle::getStatus() const { return pImpl_->getStatus(); }
Specialty AppointmentHandle::getAppointmentType() const { return pImpl_->getAppointmentType(); }

void AppointmentHandle::setPatientName(const std::string& name) { pImpl_->setPatientName(name); }
void AppointmentHandle::setDoctorName(const std::string& name) { pImpl_->setDoctorName(name); }
void AppointmentHandle::setDate(const std::string& date) { pImpl_->setDate(date); }
void AppointmentHandle::setTime(const std::string& time) { pImpl_->setTime(time); }
void AppointmentHandle::setStatus(const Status status) { pImpl_->setStatus(status); }
void AppointmentHandle::setAppointmentType(const Specialty type) { pImpl_->setAppointmentType(type); }