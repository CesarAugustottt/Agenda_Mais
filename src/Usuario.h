#ifndef USUARIO_H
#define USUARIO_H

#include <string>

enum class TipoUsuario {
    PACIENTE,
    SECRETARIA,
    MEDICO,
    ADMINISTRADOR
};

class Usuario {
public:
    virtual ~Usuario() {}
    virtual std::string getCpf() const = 0;
    virtual std::string getEmail() const = 0;
    virtual TipoUsuario getTipo() const = 0;
    virtual bool isAtivo() const = 0;
    virtual void setTipo(TipoUsuario novoTipo) = 0;
    virtual void inativar() = 0;
};

#endif
