#include "TelaStatusAgendamento.h"
#include "User.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QAbstractItemView>

TelaStatusAgendamento::TelaStatusAgendamento(QWidget *parent, System* sys)
    : QWidget(parent), sistema(sys)
{
    this->resize(680, 480);
    this->setWindowTitle("Acompanhar Status do Agendamento");

    layoutPrincipal = new QVBoxLayout(this);

    // linha de busca por CPF
    layoutBusca = new QHBoxLayout();
    lblCpf = new QLabel("CPF do Paciente (deixe vazio para ver todos):", this);
    txtCpf = new QLineEdit(this);
    btnBuscar = new QPushButton("Buscar", this);
    layoutBusca->addWidget(lblCpf);
    layoutBusca->addWidget(txtCpf);
    layoutBusca->addWidget(btnBuscar);
    layoutPrincipal->addLayout(layoutBusca);

    // tabela de resultados
    tabela = new QTableWidget(this);
    tabela->setColumnCount(6);
    QStringList headers;
    headers << "Paciente" << "Data" << "Hora" << "Especialidade" << "Status" << "Justificativa";
    tabela->setHorizontalHeaderLabels(headers);
    tabela->horizontalHeader()->setStretchLastSection(true);
    tabela->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tabela->setSelectionBehavior(QAbstractItemView::SelectRows);
    layoutPrincipal->addWidget(tabela);

    btnVoltar = new QPushButton("Voltar", this);
    layoutPrincipal->addWidget(btnVoltar);

    connect(btnBuscar, &QPushButton::clicked, this, &TelaStatusAgendamento::on_btnBuscar_clicked);
    connect(btnVoltar, &QPushButton::clicked, this, &TelaStatusAgendamento::on_btnVoltar_clicked);

    // já carrega TODAS as consultas de TODOS os pacientes ao abrir a tela
    carregarStatus("");
}

TelaStatusAgendamento::~TelaStatusAgendamento() {}

void TelaStatusAgendamento::carregarStatus(const std::string& cpfPaciente) {
    if (!sistema) {
        QMessageBox::critical(this, "Erro", "Sistema não inicializado.");
        return;
    }

    std::vector<Appointment*> todas = sistema->getAllAppointments();

    // se o CPF estiver vazio, mostra TODAS as consultas de TODOS; senão, filtra por paciente
    std::vector<Appointment*> filtradas;
    if (cpfPaciente.empty()) {
        filtradas = todas;
    } else {
        for (auto consulta : todas) {
            User* paciente = consulta->getPatient();
            if (paciente && paciente->getCpf() == cpfPaciente) {
                filtradas.push_back(consulta);
            }
        }
    }

    tabela->setRowCount(static_cast<int>(filtradas.size()));

    for (size_t i = 0; i < filtradas.size(); ++i) {
        Appointment* consulta = filtradas[i];

        QString nomePaciente = consulta->getPatient() ? QString::fromStdString(consulta->getPatient()->getName()) : "-";

        tabela->setItem(static_cast<int>(i), 0, new QTableWidgetItem(nomePaciente));
        tabela->setItem(static_cast<int>(i), 1, new QTableWidgetItem(QString::fromStdString(consulta->getDate())));
        tabela->setItem(static_cast<int>(i), 2, new QTableWidgetItem(QString::fromStdString(consulta->getTime())));
        tabela->setItem(static_cast<int>(i), 3, new QTableWidgetItem(especialidadeToString(consulta->getAppointmentType())));
        tabela->setItem(static_cast<int>(i), 4, new QTableWidgetItem(statusToString(consulta->getStatus())));

        QString justificativa;
        if (consulta->getStatus() == Status::REJECTED) {
            std::string just = consulta->getJustificativa();
            justificativa = just.empty() ? "Sem justificativa registrada" : QString::fromStdString(just);
        } else {
            justificativa = "-";
        }
        tabela->setItem(static_cast<int>(i), 5, new QTableWidgetItem(justificativa));
    }

    if (filtradas.empty() && !cpfPaciente.empty()) {
        QMessageBox::information(this, "Nenhum resultado", "Nenhuma consulta encontrada para esse CPF.");
    }
}

QString TelaStatusAgendamento::especialidadeToString(Specialty esp) {
    switch (esp) {
    case Specialty::DENTIST:       return "Dentista";
    case Specialty::NEUROLOGIST:   return "Neurologista";
    case Specialty::PSYCHOLOGIST:  return "Psicólogo";
    case Specialty::CARDIOLOGIST:  return "Cardiologista";
    case Specialty::NUTRITIONIST:  return "Nutricionista";
    case Specialty::DERMATOLOGIST: return "Dermatologista";
    }
    return "Desconhecida";
}

QString TelaStatusAgendamento::statusToString(Status status) {
    switch (status) {
    case Status::PENDING:   return "Pendente";
    case Status::CONFIRMED: return "Confirmada";
    case Status::REJECTED:  return "Recusada";
    }
    return "Desconhecido";
}

void TelaStatusAgendamento::on_btnBuscar_clicked() {
    std::string cpf = txtCpf->text().toStdString();
    carregarStatus(cpf); // vazio = mostra todas, preenchido = filtra por esse paciente
}

void TelaStatusAgendamento::on_btnVoltar_clicked() {
    this->close();
}