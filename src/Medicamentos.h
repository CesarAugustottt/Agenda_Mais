#ifndef MEDICAMENTO_H
#define MEDICAMENTO_H

#include <string>

class Medicamento {
public:
    virtual ~Medicamento() {}
    
    virtual std::string getNome() const = 0;
    virtual int getQuantidade() const = 0;
    virtual bool exigeReceita() const = 0;
    
    virtual void setNome(const std::string& nome) = 0;
    virtual void setQuantidade(int quantidade) = 0;
    virtual void setExigeReceita(bool exige) = 0;
    
    // Método auxiliar para o Requisito 7 (reduzir estoque na reserva)
    virtual bool decrementarEstoque(int qtd) = 0;
};

#endif1