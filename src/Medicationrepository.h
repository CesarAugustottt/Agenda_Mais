#ifndef MEDICATIONREPOSITORY_H
#define MEDICATIONREPOSITORY_H

#include <string>
#include <vector>

/*!
 * @brief Linha da tabela medications trazida de volta para o SystemBody.
 */
struct MedicationRecord {
    std::string name;
    int quantity;
    bool requiresPrescription;
};

/*!
 * @class MedicationRepository
 * @brief Isola todo o SQL da tabela "medications". Usa o nome como chave natural,
 * assim como já era feito em SystemBody::deleteMedication.
 */
class MedicationRepository {
public:
    bool insertMedication(const std::string& name, int quantity, bool requiresPrescription);
    bool updateMedication(const std::string& name, int quantity, bool requiresPrescription);
    bool deleteMedication(const std::string& name);

    std::vector<MedicationRecord> loadAll();
};

#endif // MEDICATIONREPOSITORY_H