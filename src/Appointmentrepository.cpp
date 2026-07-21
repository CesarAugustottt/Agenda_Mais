#include "AppointmentRepository.h"
#include "Database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QString>
#include <QDebug>

int AppointmentRepository::insertAppointment(const std::string& patientCpf, const std::string& doctorCpf,
                                              const std::string& date, const std::string& time,
                                              int status, int specialty, const std::string& justificativa) {
    QSqlQuery query(Database::instance().connection());
    query.prepare("INSERT INTO appointments (patient_cpf, doctor_cpf, date, time, status, specialty, justificativa) "
                  "VALUES (:patient_cpf, :doctor_cpf, :date, :time, :status, :specialty, :justificativa)");
    query.bindValue(":patient_cpf", QString::fromStdString(patientCpf));
    query.bindValue(":doctor_cpf", QString::fromStdString(doctorCpf));
    query.bindValue(":date", QString::fromStdString(date));
    query.bindValue(":time", QString::fromStdString(time));
    query.bindValue(":status", status);
    query.bindValue(":specialty", specialty);
    query.bindValue(":justificativa", QString::fromStdString(justificativa));

    if (!query.exec()) {
        qWarning() << "[AppointmentRepository] insertAppointment falhou:" << query.lastError().text();
        return -1;
    }
    return query.lastInsertId().toInt();
}

bool AppointmentRepository::updateAppointment(int id, const std::string& patientCpf, const std::string& doctorCpf,
                                               const std::string& date, const std::string& time,
                                               int status, int specialty, const std::string& justificativa) {
    QSqlQuery query(Database::instance().connection());
    query.prepare("UPDATE appointments SET patient_cpf = :patient_cpf, doctor_cpf = :doctor_cpf, "
                  "date = :date, time = :time, status = :status, specialty = :specialty, "
                  "justificativa = :justificativa WHERE id = :id");
    query.bindValue(":patient_cpf", QString::fromStdString(patientCpf));
    query.bindValue(":doctor_cpf", QString::fromStdString(doctorCpf));
    query.bindValue(":date", QString::fromStdString(date));
    query.bindValue(":time", QString::fromStdString(time));
    query.bindValue(":status", status);
    query.bindValue(":specialty", specialty);
    query.bindValue(":justificativa", QString::fromStdString(justificativa));
    query.bindValue(":id", id);

    if (!query.exec()) {
        qWarning() << "[AppointmentRepository] updateAppointment falhou:" << query.lastError().text();
        return false;
    }
    return true;
}

bool AppointmentRepository::deleteAppointment(int id) {
    QSqlQuery query(Database::instance().connection());
    query.prepare("DELETE FROM appointments WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qWarning() << "[AppointmentRepository] deleteAppointment falhou:" << query.lastError().text();
        return false;
    }
    return true;
}

std::vector<AppointmentRecord> AppointmentRepository::loadAll() {
    std::vector<AppointmentRecord> records;
    QSqlQuery query("SELECT id, patient_cpf, doctor_cpf, date, time, status, specialty, justificativa "
                     "FROM appointments", Database::instance().connection());

    while (query.next()) {
        AppointmentRecord r;
        r.id = query.value(0).toInt();
        r.patientCpf = query.value(1).toString().toStdString();
        r.doctorCpf = query.value(2).toString().toStdString();
        r.date = query.value(3).toString().toStdString();
        r.time = query.value(4).toString().toStdString();
        r.status = query.value(5).toInt();
        r.specialty = query.value(6).toInt();
        r.justificativa = query.value(7).toString().toStdString();
        records.push_back(r);
    }
    return records;
}