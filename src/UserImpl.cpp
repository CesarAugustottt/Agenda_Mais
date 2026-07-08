#include "UserImpl.h"

// Implementação de UserBody
UserBody::UserBody() {
    this->name = "";
    this->cpf = "";
    this->email = "";
    this->password = "";
    this->type = UserType::PATIENT;
    this->active = true;
}

UserBody::~UserBody() {} // fica vazio, pois não há ponteiros dinâmicos locais para desalocar

std::string UserBody::getCpf() const {
    return this->cpf; 
}

std::string UserBody::getEmail() const {
    return this->email; 
}

UserType UserBody::getType() const {
    return this->type; 
}

bool UserBody::isActive() const {
    return this->active; 
}

void UserBody::setName(const std::string& name) {
    this->name = name; 
}

void UserBody::setCpf(const std::string& cpf) {
    this->cpf = cpf; 
}

void UserBody::setEmail(const std::string& email) {
    this->email = email; 
}

void UserBody::setPassword(const std::string& password) {
    this->password = password; 
}

void UserBody::setType(UserType newType) {
    this->type = newType; 
}

void UserBody::deactivate() {
    this->active = false; 
}

// Implementação de UserHandle
UserHandle::UserHandle(const std::string& name, const std::string& cpf, const std::string& email, const std::string& password, UserType type) {
    pImpl_->setName(name);
    pImpl_->setCpf(cpf);
    pImpl_->setEmail(email);
    pImpl_->setPassword(password);
    pImpl_->setType(type);
}

UserHandle::UserHandle(){}

UserHandle::~UserHandle() {}

std::string UserHandle::getCpf() const {
    return pImpl_->getCpf(); 
}

std::string UserHandle::getEmail() const {
    return pImpl_->getEmail(); 
}

UserType UserHandle::getType() const { 
    return pImpl_->getType(); 
}

bool UserHandle::isActive() const { 
    return pImpl_->isActive(); 
}

void UserHandle::setType(UserType newType) { 
    pImpl_->setType(newType); 
}

void UserHandle::deactivate() { 
    pImpl_->deactivate(); 
}
