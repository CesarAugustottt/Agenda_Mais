#include "UserRepository.h"
#include "Database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QString>
#include <QDebug>

bool UserRepository::insertUser(const std::string& name, const std::string& cpf, const std::string& email,
                                 const std::string& password, UserType type, bool active) {
    QSqlQuery query(Database::instance().connection());
    query.prepare("INSERT OR REPLACE INTO users (cpf, name, email, password, type, active) "
                  "VALUES (:cpf, :name, :email, :password, :type, :active)");
    query.bindValue(":cpf", QString::fromStdString(cpf));
    query.bindValue(":name", QString::fromStdString(name));
    query.bindValue(":email", QString::fromStdString(email));
    query.bindValue(":password", QString::fromStdString(password));
    query.bindValue(":type", static_cast<int>(type));
    query.bindValue(":active", active ? 1 : 0);

    if (!query.exec()) {
        qWarning() << "[UserRepository] insertUser falhou:" << query.lastError().text();
        return false;
    }
    return true;
}

bool UserRepository::updateUser(const std::string& cpf, const std::string& name, const std::string& email,
                                 UserType type, bool active) {
    QSqlQuery query(Database::instance().connection());
    query.prepare("UPDATE users SET name = :name, email = :email, type = :type, active = :active "
                  "WHERE cpf = :cpf");
    query.bindValue(":name", QString::fromStdString(name));
    query.bindValue(":email", QString::fromStdString(email));
    query.bindValue(":type", static_cast<int>(type));
    query.bindValue(":active", active ? 1 : 0);
    query.bindValue(":cpf", QString::fromStdString(cpf));

    if (!query.exec()) {
        qWarning() << "[UserRepository] updateUser falhou:" << query.lastError().text();
        return false;
    }
    return true;
}

bool UserRepository::deleteUser(const std::string& cpf) {
    QSqlQuery query(Database::instance().connection());
    query.prepare("DELETE FROM users WHERE cpf = :cpf");
    query.bindValue(":cpf", QString::fromStdString(cpf));

    if (!query.exec()) {
        qWarning() << "[UserRepository] deleteUser falhou:" << query.lastError().text();
        return false;
    }
    return true;
}

std::vector<UserRecord> UserRepository::loadAll() {
    std::vector<UserRecord> records;
    QSqlQuery query("SELECT cpf, name, email, password, type, active FROM users",
                     Database::instance().connection());

    while (query.next()) {
        UserRecord r;
        r.cpf = query.value(0).toString().toStdString();
        r.name = query.value(1).toString().toStdString();
        r.email = query.value(2).toString().toStdString();
        r.password = query.value(3).toString().toStdString();
        r.type = static_cast<UserType>(query.value(4).toInt());
        r.active = query.value(5).toInt() != 0;
        records.push_back(r);
    }
    return records;
}