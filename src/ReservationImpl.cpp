#include "ReservationImpl.h"
#include "Medication.h"

// ==========================================
// Implementação do Body
// ==========================================
ReservationBody::ReservationBody(const std::string& patientCpf, Medication* medication, int quantity, const std::string& prescriptionPath)
    : Body(), patientCpf(patientCpf), medication(medication), quantity(quantity), 
      prescriptionPath(prescriptionPath), status(ReservationStatus::PENDING), justification("") {}

ReservationBody::~ReservationBody() {}

std::string ReservationBody::getPatientCpf() const { return this->patientCpf; }
Medication* ReservationBody::getMedication() const { return this->medication; }
int ReservationBody::getQuantity() const { return this->quantity; }
std::string ReservationBody::getPrescriptionPath() const { return this->prescriptionPath; }
ReservationStatus ReservationBody::getStatus() const { return this->status; }
std::string ReservationBody::getJustification() const { return this->justification; }

void ReservationBody::setPatientCpf(const std::string& cpf) { this->patientCpf = cpf; }
void ReservationBody::setMedication(Medication* med) { this->medication = med; }
void ReservationBody::setQuantity(int qty) { this->quantity = qty; }
void ReservationBody::setPrescriptionPath(const std::string& path) { this->prescriptionPath = path; }
void ReservationBody::setStatus(ReservationStatus stat) { this->status = stat; }
void ReservationBody::setJustification(const std::string& just) { this->justification = just; }

// ==========================================
// Implementação do Handle
// ==========================================
ReservationHandle::ReservationHandle(const std::string& patientCpf, Medication* medication, int quantity, const std::string& prescriptionPath)
    : Handle<ReservationBody>(new ReservationBody(patientCpf, medication, quantity, prescriptionPath)) {}

ReservationHandle::~ReservationHandle() {}

std::string ReservationHandle::getPatientCpf() const { return pImpl_->getPatientCpf(); }
Medication* ReservationHandle::getMedication() const { return pImpl_->getMedication(); }
int ReservationHandle::getQuantity() const { return pImpl_->getQuantity(); }
std::string ReservationHandle::getPrescriptionPath() const { return pImpl_->getPrescriptionPath(); }
ReservationStatus ReservationHandle::getStatus() const { return pImpl_->getStatus(); }
std::string ReservationHandle::getJustification() const { return pImpl_->getJustification(); }

void ReservationHandle::setPatientCpf(const std::string& cpf) { pImpl_->setPatientCpf(cpf); }
void ReservationHandle::setMedication(Medication* med) { pImpl_->setMedication(med); }
void ReservationHandle::setQuantity(int qty) { pImpl_->setQuantity(qty); }
void ReservationHandle::setPrescriptionPath(const std::string& path) { pImpl_->setPrescriptionPath(path); }
void ReservationHandle::setStatus(ReservationStatus stat) { pImpl_->setStatus(stat); }
void ReservationHandle::setJustification(const std::string& just) { pImpl_->setJustification(just); }