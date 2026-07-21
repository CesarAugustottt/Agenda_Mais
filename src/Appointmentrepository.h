#ifndef APPOINTMENTREPOSITORY_H
#define APPOINTMENTREPOSITORY_H

#include <string>
#include <vector>

/*!
 * @brief Linha da tabela appointments trazida de volta para o SystemBody.
 */
struct AppointmentRecord {
    int id;
    std::string patientCpf;
    std::string doctorCpf;
    std::string date;
    std::string time;
    int status;     // corresponde ao enum Status
    int specialty;  // corresponde ao enum Specialty
    std::string justificativa;
};

/*!
 * @class AppointmentRepository
 * @brief Isola todo o SQL da tabela "appointments". Como Appointment não tem
 * uma chave natural (paciente+data+hora poderia repetir), usamos o id autoincrement
 * do SQLite para update/delete.
 */
class AppointmentRepository {
public:
    /*!
     * @return o id gerado pelo SQLite para a nova linha, ou -1 em caso de falha.
     */
    int insertAppointment(const std::string& patientCpf, const std::string& doctorCpf,
                           const std::string& date, const std::string& time,
                           int status, int specialty, const std::string& justificativa);

    bool updateAppointment(int id, const std::string& patientCpf, const std::string& doctorCpf,
                            const std::string& date, const std::string& time,
                            int status, int specialty, const std::string& justificativa);

    bool deleteAppointment(int id);

    std::vector<AppointmentRecord> loadAll();
};

#endif // APPOINTMENTREPOSITORY_H