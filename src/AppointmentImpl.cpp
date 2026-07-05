#include "AppointmentImpl.h"

// =========================================================
// AppointmentBody Implementation
// =========================================================
AppointmentBody::AppointmentBody(const std::string& patient, const std::string& doctor, 
                                 const std::string& date, const std::string& time, 
                                 const std::string& type)
    : Body(), patientName(patient), doctorName(doctor), date(date), time(time), 
      status("Pending"), reason(""), appointmentType(type) {}

AppointmentBody::~AppointmentBody() {}

std::string AppointmentBody::getPatientName() const { return this->patientName; }
std::string AppointmentBody::getDoctorName() const { return this->doctorName; }
std::string AppointmentBody::getDate() const { return this->date; }
std::string AppointmentBody::getTime() const { return this->time; }
std::string AppointmentBody::getStatus() const { return this->status; }
std::string AppointmentBody::getReason() const { return this->reason; }
std::string AppointmentBody::getAppointmentType() const { return this->appointmentType; }

void AppointmentBody::setPatientName(const std::string& name) { this->patientName = name; }
void AppointmentBody::setDoctorName(const std::string& name) { this->doctorName = name; }
void AppointmentBody::setDate(const std::string& date) { this->date = date; }
void AppointmentBody::setTime(const std::string& time) { this->time = time; }
void AppointmentBody::setStatus(const std::string& status) { this->status = status; }
void AppointmentBody::setReason(const std::string& reason) { this->reason = reason; }
void AppointmentBody::setAppointmentType(const std::string& type) { this->appointmentType = type; }

// =========================================================
// AppointmentHandle Implementation
// =========================================================
AppointmentHandle::AppointmentHandle(const std::string& patient, const std::string& doctor, 
                                     const std::string& date, const std::string& time, 
                                     const std::string& type)
    : Handle<AppointmentBody>(new AppointmentBody(patient, doctor, date, time, type)) {}

AppointmentHandle::~AppointmentHandle() {}

std::string AppointmentHandle::getPatientName() const { return pImpl_->getPatientName(); }
std::string AppointmentHandle::getDoctorName() const { return pImpl_->getDoctorName(); }
std::string AppointmentHandle::getDate() const { return pImpl_->getDate(); }
std::string AppointmentHandle::getTime() const { return pImpl_->getTime(); }
std::string AppointmentHandle::getStatus() const { return pImpl_->getStatus(); }
std::string AppointmentHandle::getReason() const { return pImpl_->getReason(); }
std::string AppointmentHandle::getAppointmentType() const { return pImpl_->getAppointmentType(); }

void AppointmentHandle::setPatientName(const std::string& name) { pImpl_->setPatientName(name); }
void AppointmentHandle::setDoctorName(const std::string& name) { pImpl_->setDoctorName(name); }
void AppointmentHandle::setDate(const std::string& date) { pImpl_->setDate(date); }
void AppointmentHandle::setTime(const std::string& time) { pImpl_->setTime(time); }
void AppointmentHandle::setStatus(const std::string& status) { pImpl_->setStatus(status); }
void AppointmentHandle::setReason(const std::string& reason) { pImpl_->setReason(reason); }
void AppointmentHandle::setAppointmentType(const std::string& type) { pImpl_->setAppointmentType(type); }