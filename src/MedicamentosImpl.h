#ifndef MEDICAMENTOIMPL_H
#define MEDICAMENTOIMPL_H

#include "Medicamento.h"
#include "Bridge.h" // Sua classe template Handle e Body base
#include <string>

class MedicamentoBody : public Body {
protected:
    std::string nome;
    int quantidade;
    bool exigeReceita;

public:
    MedicamentoBody(const std::string& nome, int quantidade, bool exigeReceita);
    virtual ~MedicamentoBody();

    std::string getNome() const;
    int getQuantidade() const;
    bool getExigeReceita() const;

    void setNome(const std::string& nome);
    void setQuantidade(int quantidade);
    void setExigeReceita(bool exige);
    
    bool decrementarEstoque(int qtd);
};

class MedicamentoHandle : public Medicamento, public Handle<MedicamentoBody> {
public:
    MedicamentoHandle(const std::string& nome, int quantidade, bool exigeReceita);
    virtual ~MedicamentoHandle();

    std::string getNome() const override;
    int getQuantidade() const override;
    bool exigeReceita() const override;

    void setNome(const std::string& nome) override;
    void setQuantidade(int quantidade) override;
    void setExigeReceita(bool exige) override;
    
    bool decrementarEstoque(int qtd) override;
};

#endif