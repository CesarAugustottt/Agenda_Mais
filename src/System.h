#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>
#include "User.h"
#include "Appointment.h"
#include "Medication.h"
#include "Reservation.h"

/*!
 * @brief This class represents the interface of a System as implemented in this code.
 * * It defines the abstract factory methods and containers management operations.
 */
class System {
public:
    /*!
     * @brief This is the default destructor for the System Class.
     */
    virtual ~System() {}

    //Fabricas
    /*!
     * @brief Static factory method for creating a global system instance.
     * * @return System* - pointer to the created System instance.
     */
    static System* createSystem();

    /*!
     * @brief Pure virtual method to create and register a User.
     * * @param name the name of the User.
     * * @param cpf the cpf of the User.
     * * @param email the email of the User.
     * * @param password the password of the User.
     * * @param type the type of the User.
     * * @return User* - pointer to the created User.
     */
    virtual User* createUser(const std::string& name, const std::string& cpf, const std::string& email, const std::string& password, UserType type) = 0;

    /*!
     * @brief Pure virtual method to create and register an Appointment.
     * * @param patient the patient pointer from the appointment.
     * * @param doctor the doctor pointer from the appointment.
     * * @param date the date of the appointment.
     * * @param time the time of the appointment.
     * * @param esp the type of specialty for the appointment.
     * * @return Appointment* - pointer to the created Appointment.
     */
    virtual Appointment* createAppointment(User* patient, User* doctor, const std::string& date, const std::string& time, Specialty esp) = 0;

    /*!
     * @brief Pure virtual method to create and register a Medication.
     * * @param name the name of the medication.
     * * @param quantity initial quantity in stock.
     * * @param requiresPrescription flag indicating if a prescription is needed.
     * * @return Medication* - pointer to the created Medication.
     */
    virtual Medication* createMedication(const std::string& name, int quantity, bool requiresPrescription) = 0;

    /*!
     * @brief Pure virtual method to create and register a Reservation.
     * * @param patientCpf the cpf of the patient making the reservation.
     * * @param medication the pointer to the medication object.
     * * @param quantity the amount of units requested.
     * * @param prescriptionPath the path string for the attached prescription document.
     * * @return Reservation* - pointer to the created Reservation.
     */
    virtual Reservation* createReservation(const std::string& patientCpf, Medication* medication, int quantity, const std::string& prescriptionPath) = 0;

    // metodos de adicionar
    /*!
     * @brief Adds an existing User pointer to the system database.
     * * @param user pointer to be added.
     */
    virtual void addUser(User* user) = 0;

    /*!
     * @brief Adds an existing Appointment pointer to the system database.
     * * @param appointment pointer to be added.
     */
    virtual void addAppointment(Appointment* appointment) = 0;

    /*!
     * @brief Adds an existing Medication pointer to the system database.
     * * @param medication pointer to be added.
     */
    virtual void addMedication(Medication* medication) = 0;

    /*!
     * @brief Adds an existing Reservation pointer to the system database.
     * * @param reservation pointer to be added.
     */
    virtual void addReservation(Reservation* reservation) = 0;

    /*!
     * @brief Retorna todas as consultas (Appointments) cadastradas no sistema.
     * @return std::vector<Appointment*> - lista de ponteiros para as consultas.
     */

    virtual std::vector<Appointment*> getAllAppointments() const = 0;
    // metodos de delete
    /*!
     * @brief Deletes a User from the system database by its unique cpf identifier.
     * * @param cpf the identifier of the target user.
     * * @return bool - true if successfully deleted, false otherwise.
     */
    virtual bool deleteUser(const std::string& cpf) = 0;

    /*!
     * @brief Deletes a specific Appointment pointer from the system database.
     * * @param appointment pointer to the target appointment.
     * * @return bool - true if successfully deleted, false otherwise.
     */
    virtual bool deleteAppointment(Appointment* appointment) = 0;

    /*!
     * @brief Deletes a Medication from the system database by its unique name identifier.
     * * @param name the identifier of the target medication.
     * * @return bool - true if successfully deleted, false otherwise.
     */
    virtual bool deleteMedication(const std::string& name) = 0;

    /*!
     * @brief Deletes a specific Reservation pointer from the system database.
     * * @param reservation pointer to the target reservation.
     * * @return bool - true if successfully deleted, false otherwise.
     */
    virtual bool deleteReservation(Reservation* reservation) = 0;
};

#endif // SYSTEM_H