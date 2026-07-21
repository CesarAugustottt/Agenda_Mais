#include "ReservationRepository.h"
#include "Database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QString>
#include <QDebug>

int ReservationRepository::insertReservation(const std::string& patientCpf, const std::string& medicationName,
                                              int quantity, const std::string& prescriptionPath,
                                              int status, const std::string& justification) {
    QSqlQuery query(Database::instance().connection());
    query.prepare("INSERT INTO reservations (patient_cpf, medication_name, quantity, prescription_path, status, justification) "
                  "VALUES (:patient_cpf, :medication_name, :quantity, :prescription_path, :status, :justification)");
    query.bindValue(":patient_cpf", QString::fromStdString(patientCpf));
    query.bindValue(":medication_name", QString::fromStdString(medicationName));
    query.bindValue(":quantity", quantity);
    query.bindValue(":prescription_path", QString::fromStdString(prescriptionPath));
    query.bindValue(":status", status);
    query.bindValue(":justification", QString::fromStdString(justification));

    if (!query.exec()) {
        qWarning() << "[ReservationRepository] insertReservation falhou:" << query.lastError().text();
        return -1;
    }
    return query.lastInsertId().toInt();
}

bool ReservationRepository::updateReservation(int id, const std::string& patientCpf, const std::string& medicationName,
                                               int quantity, const std::string& prescriptionPath,
                                               int status, const std::string& justification) {
    QSqlQuery query(Database::instance().connection());
    query.prepare("UPDATE reservations SET patient_cpf = :patient_cpf, medication_name = :medication_name, "
                  "quantity = :quantity, prescription_path = :prescription_path, status = :status, "
                  "justification = :justification WHERE id = :id");
    query.bindValue(":patient_cpf", QString::fromStdString(patientCpf));
    query.bindValue(":medication_name", QString::fromStdString(medicationName));
    query.bindValue(":quantity", quantity);
    query.bindValue(":prescription_path", QString::fromStdString(prescriptionPath));
    query.bindValue(":status", status);
    query.bindValue(":justification", QString::fromStdString(justification));
    query.bindValue(":id", id);

    if (!query.exec()) {
        qWarning() << "[ReservationRepository] updateReservation falhou:" << query.lastError().text();
        return false;
    }
    return true;
}

bool ReservationRepository::deleteReservation(int id) {
    QSqlQuery query(Database::instance().connection());
    query.prepare("DELETE FROM reservations WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qWarning() << "[ReservationRepository] deleteReservation falhou:" << query.lastError().text();
        return false;
    }
    return true;
}

std::vector<ReservationRecord> ReservationRepository::loadAll() {
    std::vector<ReservationRecord> records;
    QSqlQuery query("SELECT id, patient_cpf, medication_name, quantity, prescription_path, status, justification "
                     "FROM reservations", Database::instance().connection());

    while (query.next()) {
        ReservationRecord r;
        r.id = query.value(0).toInt();
        r.patientCpf = query.value(1).toString().toStdString();
        r.medicationName = query.value(2).toString().toStdString();
        r.quantity = query.value(3).toInt();
        r.prescriptionPath = query.value(4).toString().toStdString();
        r.status = query.value(5).toInt();
        r.justification = query.value(6).toString().toStdString();
        records.push_back(r);
    }
    return records;
}