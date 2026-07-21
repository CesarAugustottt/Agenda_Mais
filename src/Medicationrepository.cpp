#include "MedicationRepository.h"
#include "Database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QString>
#include <QDebug>

bool MedicationRepository::insertMedication(const std::string& name, int quantity, bool requiresPrescription) {
    QSqlQuery query(Database::instance().connection());
    query.prepare("INSERT OR REPLACE INTO medications (name, quantity, requires_prescription) "
                  "VALUES (:name, :quantity, :requires_prescription)");
    query.bindValue(":name", QString::fromStdString(name));
    query.bindValue(":quantity", quantity);
    query.bindValue(":requires_prescription", requiresPrescription ? 1 : 0);

    if (!query.exec()) {
        qWarning() << "[MedicationRepository] insertMedication falhou:" << query.lastError().text();
        return false;
    }
    return true;
}

bool MedicationRepository::updateMedication(const std::string& name, int quantity, bool requiresPrescription) {
    QSqlQuery query(Database::instance().connection());
    query.prepare("UPDATE medications SET quantity = :quantity, requires_prescription = :requires_prescription "
                  "WHERE name = :name");
    query.bindValue(":quantity", quantity);
    query.bindValue(":requires_prescription", requiresPrescription ? 1 : 0);
    query.bindValue(":name", QString::fromStdString(name));

    if (!query.exec()) {
        qWarning() << "[MedicationRepository] updateMedication falhou:" << query.lastError().text();
        return false;
    }
    return true;
}

bool MedicationRepository::deleteMedication(const std::string& name) {
    QSqlQuery query(Database::instance().connection());
    query.prepare("DELETE FROM medications WHERE name = :name");
    query.bindValue(":name", QString::fromStdString(name));

    if (!query.exec()) {
        qWarning() << "[MedicationRepository] deleteMedication falhou:" << query.lastError().text();
        return false;
    }
    return true;
}

std::vector<MedicationRecord> MedicationRepository::loadAll() {
    std::vector<MedicationRecord> records;
    QSqlQuery query("SELECT name, quantity, requires_prescription FROM medications",
                     Database::instance().connection());

    while (query.next()) {
        MedicationRecord r;
        r.name = query.value(0).toString().toStdString();
        r.quantity = query.value(1).toInt();
        r.requiresPrescription = query.value(2).toInt() != 0;
        records.push_back(r);
    }
    return records;
}