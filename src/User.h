#ifndef USER_H
#define USER_H

#include <string>

/*!
 * @brief Enum class that defines the possible types of a user.
 */
enum class UserType {
    PATIENT,
    SECRETARY,
    DOCTOR,
    ADMINISTRATOR
};

/*!
 * @brief This class represents the interface of a User as implemented in this code.
 * * It defines the abstract methods for user management.
 */
class User {
public:
    /*!
     * @brief This is the default destructor for the User Class.
     */
    virtual ~User() {}

    //getters e setters
    /*!
     * @brief Returns the cpf attribute in the User Class.
     * * @return string - the content cpf attribute.
     */
    virtual std::string getCpf() const = 0;

    /*!
     * @brief Retorna o nome do usuário.
     * @return std::string - O nome armazenado.
     */
    virtual std::string getName() const = 0;

    /*!
     * @brief Returns the email attribute in the User Class.
     * * @return string - the content email attribute.
     */
    virtual std::string getEmail() const = 0;

    /*!
     * @brief Returns the type attribute in the User Class.
     * * @return UserType - the content type attribute.
     */
    virtual UserType getType() const = 0;

    /*!
     * @brief Returns the active status attribute in the User Class.
     * * @return bool - the content active status attribute.
     */
    virtual bool isActive() const = 0;

    /*!
     * @brief Sets the type attribute in the User Class.
     * * @param newType which will be set to the current user.
     */
    virtual void setType(UserType newType) = 0;

    //metodo virtual puro
    /*!
     * @brief Pure virtual method to deactivate the user.
     * * Must be implemented by subclasses to set the active attribute to false.
     */
    virtual void deactivate() = 0;
};

#endif
