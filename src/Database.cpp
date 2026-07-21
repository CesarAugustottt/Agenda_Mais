#include "Database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QCoreApplication>
#include <QDebug>

Database& Database::instance() {
    static Database instance;
    return instance;
}

bool Database::open() {
    if (opened) return true; // idempotente: se já foi aberto, não reabre

    db = QSqlDatabase::addDatabase("QSQLITE");
    QString path = QCoreApplication::applicationDirPath() + "/agenda.db";
    db.setDatabaseName(path);

    if (!db.open()) {
        qWarning() << "[Database] Falha ao abrir" << path << ":" << db.lastError().text();
        return false;
    }

    QSqlQuery pragma(db);
    pragma.exec("PRAGMA foreign_keys = ON");

    opened = initSchema();
    return opened;
}

bool Database::initSchema() {
    QSqlQuery query(db);
    bool ok = true;

    ok &= query.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "cpf TEXT PRIMARY KEY,"
        "name TEXT NOT NULL,"
        "email TEXT,"
        "password TEXT,"
        "type INTEGER NOT NULL,"
        "active INTEGER NOT NULL DEFAULT 1"
        ")");
    if (!ok) qWarning() << "[Database] Erro criando 'users':" << query.lastError().text();

    ok &= query.exec(
        "CREATE TABLE IF NOT EXISTS medications ("
        "name TEXT PRIMARY KEY,"
        "quantity INTEGER NOT NULL,"
        "requires_prescription INTEGER NOT NULL"
        ")");
    if (!ok) qWarning() << "[Database] Erro criando 'medications':" << query.lastError().text();

    ok &= query.exec(
        "CREATE TABLE IF NOT EXISTS appointments ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "patient_cpf TEXT,"
        "doctor_cpf TEXT,"
        "date TEXT,"
        "time TEXT,"
        "status INTEGER NOT NULL,"
        "specialty INTEGER NOT NULL,"
        "justificativa TEXT"
        ")");
    if (!ok) qWarning() << "[Database] Erro criando 'appointments':" << query.lastError().text();

    ok &= query.exec(
        "CREATE TABLE IF NOT EXISTS reservations ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "patient_cpf TEXT,"
        "medication_name TEXT,"
        "quantity INTEGER NOT NULL,"
        "prescription_path TEXT,"
        "status INTEGER NOT NULL,"
        "justification TEXT"
        ")");
    if (!ok) qWarning() << "[Database] Erro criando 'reservations':" << query.lastError().text();

    return ok;
}

QSqlDatabase& Database::connection() {
    return db;
}