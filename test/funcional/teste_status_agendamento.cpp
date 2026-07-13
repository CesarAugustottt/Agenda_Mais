#include "System.h"
#include "User.h"
#include <iostream>
#include <cassert>
#include <vector>

// Função auxiliar que reproduz a MESMA lógica de filtro usada em
// TelaStatusAgendamento::carregarStatus, só que sem depender de QWidget/QTableWidget.
// Isso permite testar a regra de negócio isoladamente.
std::vector<Appointment*> filtrarPorCpf(const std::vector<Appointment*>& todas, const std::string& cpf) {
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

void testeCenario1_ConsultaPendente() {
    System* sys = System::createSystem();

    User* paciente = sys->createUser("Paciente Um", "111.111.111-11", "p1@teste.com", "123456", UserType::PATIENT);
    User* medico    = sys->createUser("Dr. Fulano", "000.000.000-00", "medico@teste.com", "123456", UserType::DOCTOR);

    Appointment* consulta = sys->createAppointment(paciente, medico, "20/11/2026", "13:30", Specialty::DENTIST);

    assert(consulta->getStatus() == Status::PENDING);
    assert(consulta->getJustificativa().empty());

    std::cout << "[OK] Cenario 1: consulta recem-criada esta Pendente, sem justificativa.\n";

    delete sys;
}

void testeCenario2_ConsultaConfirmada() {
    System* sys = System::createSystem();

    User* paciente = sys->createUser("Paciente Dois", "222.222.222-22", "p2@teste.com", "123456", UserType::PATIENT);
    User* medico    = sys->createUser("Dr. Fulano", "000.000.000-00", "medico@teste.com", "123456", UserType::DOCTOR);

    Appointment* consulta = sys->createAppointment(paciente, medico, "21/11/2026", "14:00", Specialty::CARDIOLOGIST);

    consulta->setStatus(Status::CONFIRMED);

    assert(consulta->getStatus() == Status::CONFIRMED);
    assert(consulta->getJustificativa().empty());

    std::cout << "[OK] Cenario 2: consulta confirmada corretamente.\n";

    delete sys;
}

void testeCenario3_ConsultaRecusadaComJustificativa() {
    System* sys = System::createSystem();

    User* paciente = sys->createUser("Paciente Tres", "333.333.333-33", "p3@teste.com", "123456", UserType::PATIENT);
    User* medico    = sys->createUser("Dr. Fulano", "000.000.000-00", "medico@teste.com", "123456", UserType::DOCTOR);

    Appointment* consulta = sys->createAppointment(paciente, medico, "22/11/2026", "15:00", Specialty::NEUROLOGIST);

    consulta->setStatus(Status::REJECTED);
    consulta->setJustificativa("Medico indisponivel nesse horario");

    assert(consulta->getStatus() == Status::REJECTED);
    assert(consulta->getJustificativa() == "Medico indisponivel nesse horario");

    std::cout << "[OK] Cenario 3: consulta recusada com justificativa registrada.\n";

    delete sys;
}

void testeCenario4_BuscaSemCpfMostraTodas() {
    System* sys = System::createSystem();

    User* paciente1 = sys->createUser("Paciente A", "111.111.111-11", "a@teste.com", "123456", UserType::PATIENT);
    User* paciente2 = sys->createUser("Paciente B", "222.222.222-22", "b@teste.com", "123456", UserType::PATIENT);
    User* medico     = sys->createUser("Dr. Fulano", "000.000.000-00", "medico@teste.com", "123456", UserType::DOCTOR);

    sys->createAppointment(paciente1, medico, "20/11/2026", "13:30", Specialty::DENTIST);
    sys->createAppointment(paciente2, medico, "20/11/2026", "14:00", Specialty::CARDIOLOGIST);

    std::vector<Appointment*> todas = sys->getAllAppointments();
    std::vector<Appointment*> resultado = filtrarPorCpf(todas, ""); // cpf vazio

    assert(resultado.size() == todas.size());

    std::cout << "[OK] Cenario 4: busca com CPF vazio retorna todas as consultas.\n";

    delete sys;
}

void testeCenario5_BuscaComCpfFiltraPaciente() {
    System* sys = System::createSystem();

    User* paciente1 = sys->createUser("Paciente A", "111.111.111-11", "a@teste.com", "123456", UserType::PATIENT);
    User* paciente2 = sys->createUser("Paciente B", "222.222.222-22", "b@teste.com", "123456", UserType::PATIENT);
    User* medico     = sys->createUser("Dr. Fulano", "000.000.000-00", "medico@teste.com", "123456", UserType::DOCTOR);

    sys->createAppointment(paciente1, medico, "20/11/2026", "13:30", Specialty::DENTIST);
    sys->createAppointment(paciente2, medico, "20/11/2026", "14:00", Specialty::CARDIOLOGIST);

    std::vector<Appointment*> todas = sys->getAllAppointments();
    std::vector<Appointment*> resultado = filtrarPorCpf(todas, "111.111.111-11");

    assert(resultado.size() == 1);
    assert(resultado[0]->getPatient()->getCpf() == "111.111.111-11");

    std::cout << "[OK] Cenario 5: busca por CPF filtra apenas o paciente correto.\n";

    delete sys;
}

int main() {
    testeCenario1_ConsultaPendente();
    testeCenario2_ConsultaConfirmada();
    testeCenario3_ConsultaRecusadaComJustificativa();
    testeCenario4_BuscaSemCpfMostraTodas();
    testeCenario5_BuscaComCpfFiltraPaciente();

    std::cout << "\nTodos os cenarios passaram!\n";
    return 0;
}