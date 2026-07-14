#include "funcional_tests.h"
#include <iostream>
#include <cassert>

void test_user_management() {
    System* sistema = System::createSystem();
    assert(sistema != nullptr);

    User* paciente = sistema->createUser("Fulano", "123.456.789-00", "fulano@ufop.edu.br", "senha123", UserType::PATIENT);
    assert(paciente != nullptr);
    assert(paciente->getCpf() == "123.456.789-00");
    assert(paciente->isActive() == true);

    User* medico = sistema->createUser("Dr. Rey", "987.654.321-11", "rey@hospital.com", "med123", UserType::DOCTOR);
    assert(medico != nullptr);
    assert(medico->getType() == UserType::DOCTOR);

    delete sistema;
}

void test_appointment_flow() {
    System* sistema = System::createSystem();

    User* paciente = sistema->createUser("Fulano", "123.456.789-00", "fulano@ufop.edu.br", "senha123", UserType::PATIENT);
    User* medico = sistema->createUser("Dr. Rey", "987.654.321-11", "rey@hospital.com", "med123", UserType::DOCTOR);

    Appointment* consulta = sistema->createAppointment(paciente, medico, "15/07/2026", "14:30", Specialty::CARDIOLOGIST);
    assert(consulta != nullptr);
    assert(consulta->getDate() == "15/07/2026");
    assert(consulta->getTime() == "14:30");
    assert(consulta->getStatus() == Status::PENDING);
    assert(consulta->getAppointmentType() == Specialty::CARDIOLOGIST);

    consulta->setStatus(Status::CONFIRMED);
    assert(consulta->getStatus() == Status::CONFIRMED);

    delete sistema;
}

void test_medication_stock() {
    System* sistema = System::createSystem();

    Medication* remedio = sistema->createMedication("Amoxicilina 500mg", 50, true);
    assert(remedio != nullptr);
    assert(remedio->getQuantity() == 50);
    assert(remedio->requiresPrescription() == true);

    bool estoqueReduzido = remedio->decreaseStock(10);
    assert(estoqueReduzido == true);
    assert(remedio->getQuantity() == 40);

    bool estoqueInvalido = remedio->decreaseStock(100);
    assert(estoqueInvalido == false);
    assert(remedio->getQuantity() == 40);

    delete sistema;
}

void test_reservation_flow() {
    System* sistema = System::createSystem();

    User* paciente = sistema->createUser("Fulano", "123.456.789-00", "fulano@ufop.edu.br", "senha123", UserType::PATIENT);
    Medication* remedio = sistema->createMedication("Amoxicilina 500mg", 50, true);

    Reservation* reserva = sistema->createReservation(paciente->getCpf(), remedio, 2, "/path/to/prescription.pdf");
    assert(reserva != nullptr);
    assert(reserva->getPatientCpf() == "123.456.789-00");
    assert(reserva->getMedication() == remedio);
    assert(reserva->getQuantity() == 2);

    delete sistema;
}

void test_system_deletes() {
    System* sistema = System::createSystem();

    User* paciente = sistema->createUser("Fulano", "123.456.789-00", "fulano@ufop.edu.br", "senha123", UserType::PATIENT);
    User* medico = sistema->createUser("Dr. Rey", "987.654.321-11", "rey@hospital.com", "med123", UserType::DOCTOR);
    Appointment* consulta = sistema->createAppointment(paciente, medico, "15/07/2026", "14:30", Specialty::CARDIOLOGIST);

    bool removidoComSucesso = sistema->deleteAppointment(consulta);
    assert(removidoComSucesso == true);

    bool removeDuplicado = sistema->deleteAppointment(consulta);
    assert(removeDuplicado == false);

    bool usuarioRemovido = sistema->deleteUser("123.456.789-00");
    assert(usuarioRemovido == true);

    delete sistema;
}

// Função auxiliar que reproduz a mesma lógica de filtro usada em
// TelaStatusAgendamento::carregarStatus, testada aqui sem depender de QWidget.
static std::vector<Appointment*> filtrarPorCpf(const std::vector<Appointment*>& todas, const std::string& cpf) {
    if (cpf.empty()) return todas;

    std::vector<Appointment*> filtradas;
    for (auto consulta : todas) {
        User* paciente = consulta->getPatient();
        if (paciente && paciente->getCpf() == cpf) {
            filtradas.push_back(consulta);
        }
    }
    return filtradas;
}

void test_status_tracking_pending() {
    System* sistema = System::createSystem();

    User* paciente = sistema->createUser("Paciente Um", "111.111.111-11", "p1@teste.com", "123456", UserType::PATIENT);
    User* medico = sistema->createUser("Dr. Fulano", "000.000.000-00", "medico@teste.com", "123456", UserType::DOCTOR);

    Appointment* consulta = sistema->createAppointment(paciente, medico, "20/11/2026", "13:30", Specialty::DENTIST);

    assert(consulta->getStatus() == Status::PENDING);
    assert(consulta->getJustificativa().empty());

    delete sistema;
}

void test_status_tracking_confirmed() {
    System* sistema = System::createSystem();

    User* paciente = sistema->createUser("Paciente Dois", "222.222.222-22", "p2@teste.com", "123456", UserType::PATIENT);
    User* medico = sistema->createUser("Dr. Fulano", "000.000.000-00", "medico@teste.com", "123456", UserType::DOCTOR);

    Appointment* consulta = sistema->createAppointment(paciente, medico, "21/11/2026", "14:00", Specialty::CARDIOLOGIST);
    consulta->setStatus(Status::CONFIRMED);

    assert(consulta->getStatus() == Status::CONFIRMED);
    assert(consulta->getJustificativa().empty());

    delete sistema;
}

void test_status_tracking_rejected_with_justification() {
    System* sistema = System::createSystem();

    User* paciente = sistema->createUser("Paciente Tres", "333.333.333-33", "p3@teste.com", "123456", UserType::PATIENT);
    User* medico = sistema->createUser("Dr. Fulano", "000.000.000-00", "medico@teste.com", "123456", UserType::DOCTOR);

    Appointment* consulta = sistema->createAppointment(paciente, medico, "22/11/2026", "15:00", Specialty::NEUROLOGIST);
    consulta->setStatus(Status::REJECTED);
    consulta->setJustificativa("Medico indisponivel nesse horario");

    assert(consulta->getStatus() == Status::REJECTED);
    assert(consulta->getJustificativa() == "Medico indisponivel nesse horario");

    delete sistema;
}

void test_status_tracking_search_all() {
    System* sistema = System::createSystem();

    User* paciente1 = sistema->createUser("Paciente A", "111.111.111-11", "a@teste.com", "123456", UserType::PATIENT);
    User* paciente2 = sistema->createUser("Paciente B", "222.222.222-22", "b@teste.com", "123456", UserType::PATIENT);
    User* medico = sistema->createUser("Dr. Fulano", "000.000.000-00", "medico@teste.com", "123456", UserType::DOCTOR);

    sistema->createAppointment(paciente1, medico, "20/11/2026", "13:30", Specialty::DENTIST);
    sistema->createAppointment(paciente2, medico, "20/11/2026", "14:00", Specialty::CARDIOLOGIST);

    std::vector<Appointment*> todas = sistema->getAllAppointments();
    std::vector<Appointment*> resultado = filtrarPorCpf(todas, "");

    assert(resultado.size() == todas.size());

    delete sistema;
}

void test_status_tracking_search_by_cpf() {
    System* sistema = System::createSystem();

    User* paciente1 = sistema->createUser("Paciente A", "111.111.111-11", "a@teste.com", "123456", UserType::PATIENT);
    User* paciente2 = sistema->createUser("Paciente B", "222.222.222-22", "b@teste.com", "123456", UserType::PATIENT);
    User* medico = sistema->createUser("Dr. Fulano", "000.000.000-00", "medico@teste.com", "123456", UserType::DOCTOR);

    sistema->createAppointment(paciente1, medico, "20/11/2026", "13:30", Specialty::DENTIST);
    sistema->createAppointment(paciente2, medico, "20/11/2026", "14:00", Specialty::CARDIOLOGIST);

    std::vector<Appointment*> todas = sistema->getAllAppointments();
    std::vector<Appointment*> resultado = filtrarPorCpf(todas, "111.111.111-11");

    assert(resultado.size() == 1);
    assert(resultado[0]->getPatient()->getCpf() == "111.111.111-11");

    delete sistema;
}

void run_all_functional_tests() {
    std::cout << "Iniciando bateria de testes funcionais estruturados..." << std::endl;

    test_user_management();
    std::cout << " -> Teste de Gerenciamento de Usuários: OK!" << std::endl;

    test_appointment_flow();
    std::cout << " -> Teste de Fluxo de Agendamentos: OK!" << std::endl;

    test_medication_stock();
    std::cout << " -> Teste de Controle de Estoque de Medicamentos: OK!" << std::endl;

    test_reservation_flow();
    std::cout << " -> Teste de Fluxo de Reservas: OK!" << std::endl;

    test_system_deletes();
    std::cout << " -> Teste de Remoções e Deleções: OK!" << std::endl;

    test_status_tracking_pending();
    std::cout << " -> Teste de Acompanhamento (Pendente): OK!" << std::endl;

    test_status_tracking_confirmed();
    std::cout << " -> Teste de Acompanhamento (Confirmada): OK!" << std::endl;

    test_status_tracking_rejected_with_justification();
    std::cout << " -> Teste de Acompanhamento (Recusada com justificativa): OK!" << std::endl;

    test_status_tracking_search_all();
    std::cout << " -> Teste de Acompanhamento (Busca sem CPF): OK!" << std::endl;

    test_status_tracking_search_by_cpf();
    std::cout << " -> Teste de Acompanhamento (Busca com CPF): OK!" << std::endl;

    std::cout << "\nTodos os testes funcionais passaram com sucesso!" << std::endl;
}