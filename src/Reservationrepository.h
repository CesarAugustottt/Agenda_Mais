#ifndef RESERVATIONREPOSITORY_H
#define RESERVATIONREPOSITORY_H

#include <string>
#include <vector>

/*!
 * @brief Linha da tabela reservations trazida de volta para o SystemBody.
 */
struct ReservationRecord {
    int id;
    std::string patientCpf;
    std::string medicationName; // referencia o medicamento pelo nome (chave natural de medications)
    int quantity;
    std::string prescriptionPath;
    int status; // corresponde ao enum ReservationStatus
    std::string justification;
};

/*!
 * @class ReservationRepository
 * @brief Isola todo o SQL da tabela "reservations". Assim como Appointment,
 * usa id autoincrement do SQLite para update/delete.
 */
class ReservationRepository {
public:
    int insertReservation(const std::string& patientCpf, const std::string& medicationName, int quantity,
                           const std::string& prescriptionPath, int status, const std::string& justification);

    bool updateReservation(int id, const std::string& patientCpf, const std::string& medicationName, int quantity,
                            const std::string& prescriptionPath, int status, const std::string& justification);

    bool deleteReservation(int id);

    std::vector<ReservationRecord> loadAll();
};

#endif // RESERVATIONREPOSITORY_H