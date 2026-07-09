#ifndef SYSTEMIMPL_H
#define SYSTEMIMPL_H

#include "System.h"
#include "handleBody.h"
#include <vector>

/*!
 * @class SystemBody
 * @brief This class represents the concrete implementation of a System.
 */
class SystemBody : public Body {
protected:
    /*! This attribute contains the vector list of all system users. */
    std::vector<User*> users;
    /*! This attribute contains the vector list of all medical appointments. */
    std::vector<Appointment*> appointments;
    /*! This attribute contains the vector list of all stocked medications. */
    std::vector<Medication*> medications;
    /*! This attribute contains the vector list of all pending and approved reservations. */
    std::vector<Reservation*> reservations;

public:
    // construtores e destrutor
    /*!
     * @brief This is the default constructor for the SystemBody Class.
     */
    SystemBody() {}

    /*!
     * @brief This is the default destructor for the SystemBody Class.
     */
    virtual ~SystemBody();

    // Métodos do ciclo de vida
    User* createUser(const std::string& name, const std::string& cpf, const std::string& email, const std::string& password, UserType type);
    Appointment* createAppointment(User* patient, User* doctor, const std::string& date, const std::string& time, Specialty esp);
    Medication* createMedication(const std::string& name, int quantity, bool requiresPrescription);
    Reservation* createReservation(const std::string& patientCpf, Medication* medication, int quantity, const std::string& prescriptionPath);

    void addUser(User* user);
    void addAppointment(Appointment* appointment);
    void addMedication(Medication* medication);
    void addReservation(Reservation* reservation);

    bool deleteUser(const std::string& cpf);
    bool deleteAppointment(Appointment* appointment);
    bool deleteMedication(const std::string& name);
    bool deleteReservation(Reservation* reservation);
};

/*!
 * @class SystemHandle
 * @brief This class represents the handle of a System.
 */
class SystemHandle : public System, public Handle<SystemBody> {
public:
    // construtores e destrutor
    /*!
     * @brief This is the default constructor for the SystemHandle Class.
     */
    SystemHandle();

    /*!
     * @brief This is the default destructor for the SystemHandle Class.
     */
    virtual ~SystemHandle();

    User* createUser(const std::string& name, const std::string& cpf, const std::string& email, const std::string& password, UserType type) override;
    Appointment* createAppointment(User* patient, User* doctor, const std::string& date, const std::string& time, Specialty esp) override;
    Medication* createMedication(const std::string& name, int quantity, bool requiresPrescription) override;
    Reservation* createReservation(const std::string& patientCpf, Medication* medication, int quantity, const std::string& prescriptionPath) override;

    void addUser(User* user) override;
    void addAppointment(Appointment* appointment) override;
    void addMedication(Medication* medication) override;
    void addReservation(Reservation* reservation) override;

    bool deleteUser(const std::string& cpf) override;
    bool deleteAppointment(Appointment* appointment) override;
    bool deleteMedication(const std::string& name) override;
    bool deleteReservation(Reservation* reservation) override;
};

#endif // SYSTEMIMPL_H