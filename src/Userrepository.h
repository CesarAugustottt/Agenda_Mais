#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include "User.h"
#include <string>
#include <vector>

/*!
 * @brief Struct simples usada para trazer uma linha da tabela users de volta para o SystemBody.
 */
struct UserRecord {
    std::string name;
    std::string cpf;
    std::string email;
    std::string password;
    UserType type;
    bool active;
};

/*!
 * @class UserRepository
 * @brief Isola todo o SQL da tabela "users". Não conhece Handle/Body, só dados primitivos.
 */
class UserRepository {
public:
    bool insertUser(const std::string& name, const std::string& cpf, const std::string& email,
                     const std::string& password, UserType type, bool active = true);
    bool updateUser(const std::string& cpf, const std::string& name, const std::string& email,
                     UserType type, bool active);
    bool deleteUser(const std::string& cpf);

    /*!
     * @brief Carrega todos os usuários salvos, usado na inicialização do sistema.
     */
    std::vector<UserRecord> loadAll();
};

#endif // USERREPOSITORY_H