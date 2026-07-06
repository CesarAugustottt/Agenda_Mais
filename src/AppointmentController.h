#ifndef APPOINTMENTCONTROLLER_H
#define APPOINTMENTCONTROLLER_H

#include "AppointmentImpl.h"
#include <vector>
#include <string>

class AppointmentController {
private:
    std::vector<AppointmentHandle> appointments; // Simula o banco de dados em memória

public:
    AppointmentController() {}
    virtual ~AppointmentController() {}

    // Alterado para receber o enum Specialty. O Status será definido como PENDING por padrão na criação.
    void createAppointment(const std::string& patientName, const std::string& doctorName,
                           const std::string& date, const std::string& time,
                           Specialty appointmentType);

    // Visão do Médico: Consultar Agenda (apenas os dele)
    std::vector<AppointmentHandle> getAppointmentsByDoctor(const std::string& doctorName) const;

    // Visão do Paciente: Acompanhar Status (apenas os dele)
    std::vector<AppointmentHandle> getAppointmentsByPatient(const std::string& patientName) const;

    // Visão da Secretária: Visão geral da clínica
    std::vector<AppointmentHandle> getAllAppointments() const;

    // Alterado para receber o enum Status diretamente
    void updateAppointmentStatus(size_t index, Status newStatus);
};

#endif // APPOINTMENTCONTROLLER_H