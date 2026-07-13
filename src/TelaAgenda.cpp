#include "TelaAgenda.h"
#include "User.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QAbstractItemView>

TelaAgenda::TelaAgenda(QWidget *parent, System* sys)
    : QWidget(parent), sistema(sys)
{
    this->resize(640, 480);
    this->setWindowTitle("Agenda de Atendimentos");

    layoutPrincipal = new QVBoxLayout(this);

    tabela = new QTableWidget(this);
    tabela->setColumnCount(6);
    QStringList headers;
    headers << "Paciente" << "Médico" << "Data" << "Hora" << "Especialidade" << "Status";
    tabela->setHorizontalHeaderLabels(headers);
    tabela->horizontalHeader()->setStretchLastSection(true);
    tabela->setEditTriggers(QAbstractItemView::NoEditTriggers); // só leitura
    tabela->setSelectionBehavior(QAbstractItemView::SelectRows);
    layoutPrincipal->addWidget(tabela);

    btnAtualizar = new QPushButton("Atualizar", this);
    btnVoltar = new QPushButton("Voltar", this);
    layoutPrincipal->addWidget(btnAtualizar);
    layoutPrincipal->addWidget(btnVoltar);

    connect(btnAtualizar, &QPushButton::clicked, this, &TelaAgenda::on_btnAtualizar_clicked);
    connect(btnVoltar, &QPushButton::clicked, this, &TelaAgenda::on_btnVoltar_clicked);

    carregarAgenda();
}

TelaAgenda::~TelaAgenda() {}

void TelaAgenda::carregarAgenda() {
    if (!sistema) {
        QMessageBox::critical(this, "Erro", "Sistema não inicializado.");
        return;
    }

    std::vector<Appointment*> consultas = sistema->getAllAppointments();
    tabela->setRowCount(static_cast<int>(consultas.size()));

    for (size_t i = 0; i < consultas.size(); ++i) {
        Appointment* consulta = consultas[i];

        QString nomePaciente = consulta->getPatient() ? QString::fromStdString(consulta->getPatient()->getName()) : "-";
        QString nomeMedico   = consulta->getDoctor()  ? QString::fromStdString(consulta->getDoctor()->getName())  : "-";

        tabela->setItem(static_cast<int>(i), 0, new QTableWidgetItem(nomePaciente));
        tabela->setItem(static_cast<int>(i), 1, new QTableWidgetItem(nomeMedico));
        tabela->setItem(static_cast<int>(i), 2, new QTableWidgetItem(QString::fromStdString(consulta->getDate())));
        tabela->setItem(static_cast<int>(i), 3, new QTableWidgetItem(QString::fromStdString(consulta->getTime())));
        tabela->setItem(static_cast<int>(i), 4, new QTableWidgetItem(especialidadeToString(consulta->getAppointmentType())));
        tabela->setItem(static_cast<int>(i), 5, new QTableWidgetItem(statusToString(consulta->getStatus())));
    }
}

QString TelaAgenda::especialidadeToString(Specialty esp) {
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

QString TelaAgenda::statusToString(Status status) {
    switch (status) {
        case Status::PENDING:   return "Pendente";
        case Status::CONFIRMED: return "Confirmada";
        case Status::REJECTED:  return "Rejeitada";
    }
    return "Desconhecido";
}

void TelaAgenda::on_btnAtualizar_clicked() {
    carregarAgenda();
}

void TelaAgenda::on_btnVoltar_clicked() {
    this->close();
}