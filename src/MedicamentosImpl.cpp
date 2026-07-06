#include "MedicamentoImpl.h"

MedicamentoBody::MedicamentoBody(const std::string& nome, int quantidade, bool exigeReceita)
    : Body(), nome(nome), quantidade(quantidade), exigeReceita(exigeReceita) {}

MedicamentoBody::~MedicamentoBody() {}

std::string MedicamentoBody::getNome() const { return this->nome; }
int MedicamentoBody::getQuantidade() const { return this->quantidade; }
bool MedicamentoBody::getExigeReceita() const { return this->exigeReceita; }

void MedicamentoBody::setNome(const std::string& nome) { this->nome = nome; }
void MedicamentoBody::setQuantidade(int quantidade) { this->quantidade = quantidade; }
void MedicamentoBody::setExigeReceita(bool exige) { this->exigeReceita = exige; }

bool MedicamentoBody::decrementarEstoque(int qtd) {
    if (this->quantidade >= qtd) {
        this->quantidade -= qtd;
        return true;
    }
    return false;
}

MedicamentoHandle::MedicamentoHandle(const std::string& nome, int quantidade, bool exigeReceita)
    : Handle<MedicamentoBody>(new MedicamentoBody(nome, quantidade, exigeReceita)) {}

MedicamentoHandle::~MedicamentoHandle() {}

std::string MedicamentoHandle::getNome() const { return pImpl_->getNome(); }
int MedicamentoHandle::getQuantidade() const { return pImpl_->getQuantidade(); }
bool MedicamentoHandle::exigeReceita() const { return pImpl_->getExigeReceita(); }

void MedicamentoHandle::setNome(const std::string& nome) { pImpl_->setNome(nome); }
void MedicamentoHandle::setQuantidade(int quantidade) { pImpl_->setQuantidade(quantidade); }
void MedicamentoHandle::setExigeReceita(bool exige) { pImpl_->setExigeReceita(exige); }

bool MedicamentoHandle::decrementarEstoque(int qtd) { return pImpl_->decrementarEstoque(qtd); }