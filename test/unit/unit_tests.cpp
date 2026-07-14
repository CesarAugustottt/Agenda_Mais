#include "unit_tests.h"

// =========================================================
// Appointment
// =========================================================

void test_appointment_default_status_is_pending() {
    System* sistema = System::createSystem();
    User* paciente = sistema->createUser("Paciente", "111.111.111-11", "p@teste.com", "123456", UserType::PATIENT);
    User* medico = sistema->createUser("Medico", "000.000.000-00", "m@teste.com", "123456", UserType::DOCTOR);

    Appointment* consulta = sistema->createAppointment(paciente, medico, "01/01/2027", "10:00", Specialty::DENTIST);

    assert(consulta->getStatus() == Status::PENDING);

    delete sistema;
}

void test_appointment_setStatus_changes_status() {
    System* sistema = System::createSystem();
    User* paciente = sistema->createUser("Paciente", "111.111.111-11", "p@teste.com", "123456", UserType::PATIENT);
    User* medico = sistema->createUser("Medico", "000.000.000-00", "m@teste.com", "123456", UserType::DOCTOR);

    Appointment* consulta = sistema->createAppointment(paciente, medico, "01/01/2027", "10:00", Specialty::DENTIST);
    consulta->setStatus(Status::CONFIRMED);

    assert(consulta->getStatus() == Status::CONFIRMED);

    delete sistema;
}

void test_appointment_setJustificativa_stores_text() {
    System* sistema = System::createSystem();
    User* paciente = sistema->createUser("Paciente", "111.111.111-11", "p@teste.com", "123456", UserType::PATIENT);
    User* medico = sistema->createUser("Medico", "000.000.000-00", "m@teste.com", "123456", UserType::DOCTOR);

    Appointment* consulta = sistema->createAppointment(paciente, medico, "01/01/2027", "10:00", Specialty::DENTIST);
    consulta->setJustificativa("Conflito de horario");

    assert(consulta->getJustificativa() == "Conflito de horario");

    delete sistema;
}

void test_appointment_justificativa_default_is_empty() {
    System* sistema = System::createSystem();
    User* paciente = sistema->createUser("Paciente", "111.111.111-11", "p@teste.com", "123456", UserType::PATIENT);
    User* medico = sistema->createUser("Medico", "000.000.000-00", "m@teste.com", "123456", UserType::DOCTOR);

    Appointment* consulta = sistema->createAppointment(paciente, medico, "01/01/2027", "10:00", Specialty::DENTIST);

    assert(consulta->getJustificativa().empty());

    delete sistema;
}

// =========================================================
// Medication
// =========================================================

void test_medication_decreaseStock_exact_amount() {
    System* sistema = System::createSystem();
    Medication* remedio = sistema->createMedication("Dipirona", 10, false);

    bool ok = remedio->decreaseStock(10); // retira exatamente tudo que tem
    assert(ok == true);
    assert(remedio->getQuantity() == 0);

    delete sistema;
}

void test_medication_decreaseStock_insufficient_returns_false() {
    System* sistema = System::createSystem();
    Medication* remedio = sistema->createMedication("Dipirona", 5, false);

    bool ok = remedio->decreaseStock(6); // pede mais do que existe
    assert(ok == false);
    assert(remedio->getQuantity() == 5); // estoque não deve ter sido alterado

    delete sistema;
}

void test_medication_decreaseStock_zero_amount() {
    System* sistema = System::createSystem();
    Medication* remedio = sistema->createMedication("Dipirona", 5, false);

    bool ok = remedio->decreaseStock(0); // caso de borda: retirar zero
    assert(ok == true);
    assert(remedio->getQuantity() == 5);

    delete sistema;
}

void test_medication_setQuantity_overwrites_value() {
    System* sistema = System::createSystem();
    Medication* remedio = sistema->createMedication("Dipirona", 5, false);

    remedio->setQuantity(100);
    assert(remedio->getQuantity() == 100);

    delete sistema;
}

// =========================================================
// Reservation
// =========================================================

void test_reservation_default_status_is_pending() {
    System* sistema = System::createSystem();
    Medication* remedio = sistema->createMedication("Dipirona", 10, false);

    Reservation* reserva = sistema->createReservation("111.111.111-11", remedio, 2, "");

    assert(reserva->getStatus() == ReservationStatus::PENDING);

    delete sistema;
}

void test_reservation_setStatus_changes_status() {
    System* sistema = System::createSystem();
    Medication* remedio = sistema->createMedication("Dipirona", 10, false);

    Reservation* reserva = sistema->createReservation("111.111.111-11", remedio, 2, "");
    reserva->setStatus(ReservationStatus::APPROVED);

    assert(reserva->getStatus() == ReservationStatus::APPROVED);

    delete sistema;
}

void test_reservation_setJustification_stores_text() {
    System* sistema = System::createSystem();
    Medication* remedio = sistema->createMedication("Dipirona", 10, false);

    Reservation* reserva = sistema->createReservation("111.111.111-11", remedio, 2, "");
    reserva->setJustification("Sem receita anexada");

    assert(reserva->getJustification() == "Sem receita anexada");

    delete sistema;
}

// =========================================================
// User
// =========================================================

void test_user_created_active_by_default() {
    System* sistema = System::createSystem();
    User* usuario = sistema->createUser("Fulano", "123.456.789-00", "f@teste.com", "senha", UserType::PATIENT);

    assert(usuario->isActive() == true);

    delete sistema;
}

void test_user_type_is_stored_correctly() {
    System* sistema = System::createSystem();
    User* medico = sistema->createUser("Dr. Fulano", "123.456.789-00", "f@teste.com", "senha", UserType::DOCTOR);

    assert(medico->getType() == UserType::DOCTOR);

    delete sistema;
}

// =========================================================
// MedicationsController
// =========================================================

void test_controller_requestMedication_decreases_stock() {
    System* sistema = System::createSystem();
    MedicationsController controller(sistema);

    Medication* remedio = sistema->createMedication("Ibuprofeno", 20, false);
    Reservation* reserva = controller.requestMedication("111.111.111-11", remedio, 5, "");

    assert(reserva != nullptr);
    assert(remedio->getQuantity() == 15); // 20 - 5

    delete sistema;
}

void test_controller_requestMedication_fails_when_stock_insufficient() {
    System* sistema = System::createSystem();
    MedicationsController controller(sistema);

    Medication* remedio = sistema->createMedication("Ibuprofeno", 3, false);
    Reservation* reserva = controller.requestMedication("111.111.111-11", remedio, 10, "");

    assert(reserva == nullptr); // não deve criar a reserva
    assert(remedio->getQuantity() == 3); // estoque não deve ter sido alterado

    delete sistema;
}

void test_controller_refuseReservation_returns_stock() {
    System* sistema = System::createSystem();
    MedicationsController controller(sistema);

    Medication* remedio = sistema->createMedication("Ibuprofeno", 20, false);
    controller.requestMedication("111.111.111-11", remedio, 5, ""); // estoque vira 15

    auto pendentes = controller.getPendingReservations();
    size_t indexNovaReserva = pendentes.size() - 1; // a última é a que acabamos de criar

    controller.refuseReservation(indexNovaReserva, "Motivo de teste");

    assert(remedio->getQuantity() == 20); // estoque deve voltar ao original

    delete sistema;
}

void test_controller_approveReservation_does_not_change_stock() {
    System* sistema = System::createSystem();
    MedicationsController controller(sistema);

    Medication* remedio = sistema->createMedication("Ibuprofeno", 20, false);
    controller.requestMedication("111.111.111-11", remedio, 5, ""); // estoque vira 15

    auto pendentes = controller.getPendingReservations();
    size_t indexNovaReserva = pendentes.size() - 1;

    controller.approveReservation(indexNovaReserva);

    assert(remedio->getQuantity() == 15); // estoque já tinha sido descontado, aprovar não muda nada

    delete sistema;
}

// =========================================================
// Executor
// =========================================================

void run_all_unit_tests() {
    std::cout << "Iniciando bateria de testes unitarios..." << std::endl;

    test_appointment_default_status_is_pending();
    std::cout << " -> Appointment: status padrao Pendente: OK!" << std::endl;

    test_appointment_setStatus_changes_status();
    std::cout << " -> Appointment: setStatus altera status: OK!" << std::endl;

    test_appointment_setJustificativa_stores_text();
    std::cout << " -> Appointment: setJustificativa armazena texto: OK!" << std::endl;

    test_appointment_justificativa_default_is_empty();
    std::cout << " -> Appointment: justificativa padrao vazia: OK!" << std::endl;

    test_medication_decreaseStock_exact_amount();
    std::cout << " -> Medication: decreaseStock quantidade exata: OK!" << std::endl;

    test_medication_decreaseStock_insufficient_returns_false();
    std::cout << " -> Medication: decreaseStock insuficiente retorna false: OK!" << std::endl;

    test_medication_decreaseStock_zero_amount();
    std::cout << " -> Medication: decreaseStock zero: OK!" << std::endl;

    test_medication_setQuantity_overwrites_value();
    std::cout << " -> Medication: setQuantity sobrescreve valor: OK!" << std::endl;

    test_reservation_default_status_is_pending();
    std::cout << " -> Reservation: status padrao Pendente: OK!" << std::endl;

    test_reservation_setStatus_changes_status();
    std::cout << " -> Reservation: setStatus altera status: OK!" << std::endl;

    test_reservation_setJustification_stores_text();
    std::cout << " -> Reservation: setJustification armazena texto: OK!" << std::endl;

    test_user_created_active_by_default();
    std::cout << " -> User: criado ativo por padrao: OK!" << std::endl;

    test_user_type_is_stored_correctly();
    std::cout << " -> User: tipo armazenado corretamente: OK!" << std::endl;

    test_controller_requestMedication_decreases_stock();
    std::cout << " -> MedicationsController: requestMedication desconta estoque: OK!" << std::endl;

    test_controller_requestMedication_fails_when_stock_insufficient();
    std::cout << " -> MedicationsController: requestMedication falha com estoque insuficiente: OK!" << std::endl;

    test_controller_refuseReservation_returns_stock();
    std::cout << " -> MedicationsController: refuseReservation devolve estoque: OK!" << std::endl;

    test_controller_approveReservation_does_not_change_stock();
    std::cout << " -> MedicationsController: approveReservation nao altera estoque: OK!" << std::endl;

    std::cout << "\nTodos os testes unitarios passaram com sucesso!" << std::endl;
}