#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

/*!
 * @class Database
 * @brief Singleton responsável pela conexão SQLite única usada pela aplicação
 * e pela criação do schema (tabelas) na primeira execução.
 */
class Database {
public:
    /*!
     * @brief Retorna a instância única do Database (Meyers' singleton).
     */
    static Database& instance();

    /*!
     * @brief Abre o arquivo agenda.db (criando-o se não existir) e garante o schema.
     * @return true se a conexão e o schema foram criados/validados com sucesso.
     */
    bool open();

    /*!
     * @brief Retorna a conexão QSqlDatabase já aberta, para uso pelos Repositories.
     */
    QSqlDatabase& connection();

private:
    Database() = default;
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    bool initSchema();

    QSqlDatabase db;
    bool opened = false;
};

#endif // DATABASE_H