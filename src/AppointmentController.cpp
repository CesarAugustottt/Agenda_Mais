#include "AppointmentController.h"

void AppointmentController::createAppointment(const std::string& patientName, const std::string& doctorName,
                                              const std::string& date, const std::string& time,
                                              Specialty appointmentType) {

    // Agora passamos os 6 parâmetros exatos exigidos pelo seu AppointmentImpl.
    // Como é uma criação, o status inicial é sempre PENDING.
    AppointmentHandle newAppointment(patientName, doctorName, date, time, Status::PENDING, appointmentType);
    appointments.push_back(newAppointment);
}

std::vector<AppointmentHandle> AppointmentController::getAppointmentsByDoctor(const std::string& doctorName) const {
    std::vector<AppointmentHandle> filtered;
    for (const auto& app : appointments) {
        if (app.getDoctorName() == doctorName) {
            filtered.push_back(app);
        }
    }
    return filtered;
}

std::vector<AppointmentHandle> AppointmentController::getAppointmentsByPatient(const std::string& patientName) const {
    std::vector<AppointmentHandle> filtered;
    for (const auto& app : appointments) {
        if (app.getPatientName() == patientName) {
            filtered.push_back(app);
        }
    }
    return filtered;
}

std::vector<AppointmentHandle> AppointmentController::getAllAppointments() const {
    return appointments;
}

void AppointmentController::updateAppointmentStatus(size_t index, Status newStatus) {
    if (index < appointments.size()) {
        appointments[index].setStatus(newStatus);
    }
}