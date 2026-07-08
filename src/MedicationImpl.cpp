/**
 * @file MedicationImpl.cpp
 * @brief Implementation of the MedicationBody and MedicationHandle classes.
 */

#include "MedicationImpl.h"

// MedicationBody Implementation

MedicationBody::MedicationBody()
    : name(""), quantity(0), requiresPrescription(false) {}

MedicationBody::~MedicationBody() {}

std::string MedicationBody::getName() const { 
    return this->name; 
}

int MedicationBody::getQuantity() const { 
    return this->quantity; 
}

bool MedicationBody::getRequiresPrescription() const { 
    return this->requiresPrescription; 
}

void MedicationBody::setName(const std::string& name) { 
    this->name = name; 
}

void MedicationBody::setQuantity(int quantity) { 
    this->quantity = quantity; 
}

void MedicationBody::setRequiresPrescription(bool requires) { 
    this->requiresPrescription = requires; 
}

bool MedicationBody::decreaseStock(int amount) {
    if (this->quantity >= amount) {
        this->quantity -= amount;
        return true;
    }
    return false;
}


// MedicationHandle Implementation

MedicationHandle::MedicationHandle(const std::string& name, int quantity, bool requiresPrescription) {
    // O pImpl_ já foi criado vazio pelo Handle, agora usamos os setters:
    pImpl_->setName(name);
    pImpl_->setQuantity(quantity);
    pImpl_->setRequiresPrescription(requiresPrescription);
}

MedicationHandle::MedicationHandle(){}

MedicationHandle::~MedicationHandle() {}

std::string MedicationHandle::getName() const { 
    return pImpl_->getName(); 
}

int MedicationHandle::getQuantity() const { 
    return pImpl_->getQuantity(); 
}

bool MedicationHandle::requiresPrescription() const { 
    return pImpl_->getRequiresPrescription(); 
}

void MedicationHandle::setName(const std::string& name) { 
    pImpl_->setName(name); 
}

void MedicationHandle::setQuantity(int quantity) { 
    pImpl_->setQuantity(quantity); 
}

void MedicationHandle::setRequiresPrescription(bool requires) { 
    pImpl_->setRequiresPrescription(requires); 
}

bool MedicationHandle::decreaseStock(int amount) { 
    return pImpl_->decreaseStock(amount); 
}
