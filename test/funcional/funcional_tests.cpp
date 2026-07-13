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