#include "funcional_tests.h"
#include <iostream>
#include <cassert>

void test_user_management() {
    System* sistema = System::createSystem();
    assert(sistema != nullptr);

    // Teste Paciente
    User* paciente = sistema->createUser("Fulano", "123.456.789-00", "fulano@ufop.edu.br", "senha123", UserType::PATIENT);
    assert(paciente != nullptr);
    assert(paciente->getCpf() == "123.456.789-00");
    assert(paciente->isActive() == true);

    // Teste Médico
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

    // Mudança de estado da consulta
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

    // Retirada válida
    bool estoqueReduzido = remedio->decreaseStock(10);
    assert(estoqueReduzido == true);
    assert(remedio->getQuantity() == 40);

    // Retirada inválida (acima do estoque)
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

    // Remoção bem-sucedida
    bool removidoComSucesso = sistema->deleteAppointment(consulta);
    assert(removidoComSucesso == true);

    // Tentativa duplicada de remoção
    bool removeDuplicado = sistema->deleteAppointment(consulta);
    assert(removeDuplicado == false);

    // Remoção de usuário pelo identificador (CPF)
    bool usuarioRemovido = sistema->deleteUser("123.456.789-00");
    assert(usuarioRemovido == true);

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

    std::cout << "\nTodos os testes funcionais passaram com sucesso! 🎉" << std::endl;
}