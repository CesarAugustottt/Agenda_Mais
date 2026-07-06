#include "UsuarioImpl.h"

// Implementação de UsuarioBody
UsuarioBody::UsuarioBody(const std::string& nome, const std::string& cpf, const std::string& email, const std::string& senha, TipoUsuario tipo)
    : Body(), nome(nome), cpf(cpf), email(email), senha(senha), tipo(tipo), ativo(true) {}

UsuarioBody::~UsuarioBody() {}

std::string UsuarioBody::getCpf() const {
    return this->cpf;
}

std::string UsuarioBody::getEmail() const {
    return this->email;
}

TipoUsuario UsuarioBody::getTipo() const {
    return this->tipo;
}

bool UsuarioBody::isAtivo() const {
    return this->ativo;
}

void UsuarioBody::setTipo(TipoUsuario novoTipo) {
    this->tipo = novoTipo;
}

void UsuarioBody::inativar() {
    this->ativo = false;
}

// Implementação de UsuarioHandle
UsuarioHandle::UsuarioHandle(const std::string& nome, const std::string& cpf, const std::string& email, const std::string& senha, TipoUsuario tipo)
    : Handle<UsuarioBody>(new UsuarioBody(nome, cpf, email, senha, tipo)) {}

UsuarioHandle::~UsuarioHandle() {}

std::string UsuarioHandle::getCpf() const {
    return pImpl_->getCpf();
}

std::string UsuarioHandle::getEmail() const {
    return pImpl_->getEmail();
}

TipoUsuario UsuarioHandle::getTipo() const {
    return pImpl_->getTipo();
}

bool UsuarioHandle::isAtivo() const {
    return pImpl_->isAtivo();
}

void UsuarioHandle::setTipo(TipoUsuario novoTipo) {
    pImpl_->setTipo(novoTipo);
}

void UsuarioHandle::inativar() {
    pImpl_->inativar();
}
