#ifndef USERIMPL_H
#define USERIMPL_H

#include "User.h"
#include "handleBody.h"
#include <string>

/*!
 * @class UserBody
 * @brief This class represents the concrete implementation of a User.
 */
class UserBody : public Body {
protected:
    /*! This attribute contains a name for the user. */
    std::string name;
    /*! This attribute contains a cpf for the user. */
    std::string cpf;
    /*! This attribute contains an email for the user. */
    std::string email;
    /*! This attribute contains a password for the user. */
    std::string password;
    /*! This attribute contains the type of the user. */
    UserType type;
    /*! This attribute indicates if the user is active. */
    bool active;

public:
    // construtores e destrutor
    /*!
     * @brief This is the default constructor for the UserBody Class.
     */
    UserBody();

    /*!
     * @brief This is the default destructor for the UserBody Class.
     */
    virtual ~UserBody();

    //getters e setters
    std::string getCpf() const;
    std::string getEmail() const;
    UserType getType() const;
    bool isActive() const;
    
    void setName(const std::string& name);
    void setCpf(const std::string& cpf);
    void setEmail(const std::string& email);
    void setPassword(const std::string& password);
    void setType(UserType newType);
    void deactivate();

    // Permite que a classe de teste faça testes unitários
    friend class Unit_User;
    friend class SystemBody; 
};

/*!
 * @class UserHandle
 * @brief This class represents the handle of a User.
 */
class UserHandle : public User, public Handle<UserBody> {
protected:
    // construtores e destrutor
    /*!
     * @brief This is the parameterized constructor for the UserHandle Class.
     * * @param name the name of the User.
     * * @param cpf the cpf of the User.
     * * @param email the email of the User.
     * * @param password the password of the User.
     * * @param type the type of the User.
     */
    UserHandle(const std::string& name, const std::string& cpf, const std::string& email, const std::string& password, UserType type);

     /*!
     * @brief This is the default constructor for the UserHandle Class.
     */
    UserHandle();
public:

    /*!
     * @brief This is the default destructor for the UserHandle Class.
     */
    virtual ~UserHandle();

    //getters e setters
    std::string getCpf() const override;
    std::string getEmail() const override;
    UserType getType() const override;
    bool isActive() const override;
    void setType(UserType newType) override;
    void deactivate() override;

    // Permite que a classe de teste faça testes unitários
    friend class Unit_User;
    friend class SystemBody; 
};

#endif
