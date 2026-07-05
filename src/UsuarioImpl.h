#ifndef USUARIOIMPL_H
#define USUARIOIMPL_H

#include "Usuario.h"
#include "handleBody.h"
#include <string>

class UsuarioBody : public Body {
protected:
    std::string nome;
    std::string cpf;
    std::string email;
    std::string senha;
    TipoUsuario tipo;
    bool ativo;

public:
    UsuarioBody(const std::string& nome, const std::string& cpf, const std::string& email, const std::string& senha, TipoUsuario tipo);
    virtual ~UsuarioBody();

    std::string getCpf() const;
    std::string getEmail() const;
    TipoUsuario getTipo() const;
    bool isAtivo() const;
    void setTipo(TipoUsuario novoTipo);
    void inativar();

    friend class Unit_Usuario;
};

class UsuarioHandle : public Usuario, public Handle<UsuarioBody> {
public:
    UsuarioHandle(const std::string& nome, const std::string& cpf, const std::string& email, const std::string& senha, TipoUsuario tipo);
    virtual ~UsuarioHandle();

    std::string getCpf() const override;
    std::string getEmail() const override;
    TipoUsuario getTipo() const override;
    bool isAtivo() const override;
    void setTipo(TipoUsuario novoTipo) override;
    void inativar() override;

    friend class Unit_Usuario;
};

#endif
