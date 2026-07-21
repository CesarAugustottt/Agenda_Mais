#ifndef SYSTEMIMPL_H
#define SYSTEMIMPL_H

#include "System.h"
#include "handleBody.h"
#include "UserRepository.h"
#include "MedicationRepository.h"
#include "AppointmentRepository.h"
#include "ReservationRepository.h"
#include <vector>
#include <map>

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

    // Repositories: cada um isola o SQL de uma tabela do banco SQLite.
    UserRepository userRepo;
    MedicationRepository medicationRepo;
    AppointmentRepository appointmentRepo;
    ReservationRepository reservationRepo;

    // Appointment e Reservation não têm chave natural, então rastreamos o id
    // do SQLite associado a cada ponteiro em memória, usado no update/delete.
    std::map<Appointment*, int> appointmentIds;
    std::map<Reservation*, int> reservationIds;

    /*!
     * @brief Abre a conexão SQLite (se necessário) e carrega todos os registros salvos
     * para dentro dos vectors em memória, reconstruindo os objetos via Handle/Body.
     */
    void loadFromDatabase();

public:
    // construtores e destrutor
    /*!
     * @brief This is the default constructor for the SystemBody Class.
     */
    SystemBody();

    /*!
     * @brief This is the default destructor for the SystemBody Class.
     */
    virtual ~SystemBody();

    // Métodos do ciclo de vida
    User* createUser(const std::string& name, const std::string& cpf, const std::string& email, const std::string& password, UserType type);
    Appointment* createAppointment(User* patient, User* doctor, const std::string& date, const std::string& time, Specialty esp);
    Medication* createMedication(const std::string& name, int quantity, bool requiresPrescription);
    Reservation* createReservation(const std::string& patientCpf, Medication* medication, int quantity, const std::string& prescriptionPath);
    std::vector<Appointment*> getAllAppointments() const;
    std::vector<Medication*> getAllMedications() const;
    std::vector<Reservation*> getAllReservations() const;

    void addUser(User* user);
    void addAppointment(Appointment* appointment);
    void addMedication(Medication* medication);
    void addReservation(Reservation* reservation);

    void updateAppointment(Appointment* appointment);
    void updateMedication(Medication* medication);
    void updateReservation(Reservation* reservation);

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
    std::vector<Appointment*> getAllAppointments() const override;
    std::vector<Medication*> getAllMedications() const override;
    std::vector<Reservation*> getAllReservations() const override;

    void addUser(User* user) override;
    void addAppointment(Appointment* appointment) override;
    void addMedication(Medication* medication) override;
    void addReservation(Reservation* reservation) override;

    void updateAppointment(Appointment* appointment) override;
    void updateMedication(Medication* medication) override;
    void updateReservation(Reservation* reservation) override;

    bool deleteUser(const std::string& cpf) override;
    bool deleteAppointment(Appointment* appointment) override;
    bool deleteMedication(const std::string& name) override;
    bool deleteReservation(Reservation* reservation) override;
};

#endif // SYSTEMIMPL_H