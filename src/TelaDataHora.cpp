#include "TelaDataHora.h"
#include "System.h"
#include "TelaEspecialidade.h"
#include <QMessageBox>

TelaDataHora::TelaDataHora(QWidget *parent, Specialty esp, System* sys)
    : QWidget(parent), sistema(sys), espSelecionada(esp), pacienteAtual(nullptr)
{
    this->resize(360, 640);
    this->setWindowTitle("Data");

    layoutPrincipal = new QVBoxLayout(this);

    calendarioWidget = new QCalendarWidget(this); //calendario
    calendarioWidget->setMinimumDate(QDate::currentDate()); //bloqueia dias q ja passaram
    layoutPrincipal->addWidget(calendarioWidget);

    btnHora1330 = new QPushButton("13:30", this);
    btnHora1400 = new QPushButton("14:00", this);
    btnHora1430 = new QPushButton("14:30", this);
    btnHora1500 = new QPushButton("15:00", this);
    btnVoltar   = new QPushButton("Voltar", this);

    //adiciona botões ao layout
    layoutPrincipal->addWidget(btnHora1330);
    layoutPrincipal->addWidget(btnHora1400);
    layoutPrincipal->addWidget(btnHora1430);
    layoutPrincipal->addWidget(btnHora1500);
    layoutPrincipal->addWidget(btnVoltar);

    //conecta clique ao slot
    connect(btnHora1330, &QPushButton::clicked, this, &TelaDataHora::on_btnHora1330_clicked);
    connect(btnHora1400, &QPushButton::clicked, this, &TelaDataHora::on_btnHora1400_clicked);
    connect(btnHora1430, &QPushButton::clicked, this, &TelaDataHora::on_btnHora1430_clicked);
    connect(btnHora1500, &QPushButton::clicked, this, &TelaDataHora::on_btnHora1500_clicked);
    connect(btnVoltar,   &QPushButton::clicked, this, &TelaDataHora::on_btnVoltar_clicked);
}

TelaDataHora::~TelaDataHora() {}

User* TelaDataHora::getOrCreatePacienteTeste() {
    if (!pacienteAtual && sistema) {
        pacienteAtual = sistema->createUser("Paciente Teste", "111.111.111-11", "paciente@teste.com", "123456", UserType::PATIENT);
    }
    return pacienteAtual;
}

void TelaDataHora::processarAgendamento(const std::string& horario, User* patient) {
    std::string dataStr = calendarioWidget->selectedDate().toString("dd/MM/yyyy").toStdString();
    std::string nomeMedico = "";

    if (espSelecionada == Specialty::DENTIST) {
        nomeMedico = "Dr. Fulano (Dentista)";
    } else if (espSelecionada == Specialty::NEUROLOGIST) {
        nomeMedico = "Dra. Fulana (Neurologista)";
    } else if (espSelecionada == Specialty::PSYCHOLOGIST) {
        nomeMedico = "Dr. Fulano (Psicologo)";
    } else if (espSelecionada == Specialty::CARDIOLOGIST) {
        nomeMedico = "Dra. Fulana (Cadiologista)";
    } else if (espSelecionada == Specialty::NUTRITIONIST) {
        nomeMedico = "Dr. Fulano (Nutricionista)";
    } else if (espSelecionada == Specialty::DERMATOLOGIST) {
        nomeMedico = "Dra. Fulana (Dermatologista)";
    }

    if (!sistema) {
        QMessageBox::critical(this, "Erro", "O sistema não foi transmitido corretamente para esta janela.");
        return;
    }

    User* doctor = sistema->createUser(nomeMedico, "000.000.000-00", "doctor@agendamais.com", "123456", UserType::DOCTOR);

    Appointment* novoAgendamento = sistema->createAppointment(
        patient, doctor, dataStr, horario, espSelecionada
        );

    QString msg = QString::fromStdString("Consulta Solicitada!\n\nCom: " + nomeMedico + "\nData: " + dataStr + "\nHora: " + horario);
    QMessageBox::information(this, "Sucesso", msg);

    this->close();
}

void TelaDataHora::on_btnHora1330_clicked() {
    if (!sistema) {
        QMessageBox::critical(this, "Erro", "O sistema não foi transmitido corretamente para esta janela.");
        return;
    }
    processarAgendamento("13:30", getOrCreatePacienteTeste());
}

void TelaDataHora::on_btnHora1400_clicked() {
    if (!sistema) {
        QMessageBox::critical(this, "Erro", "O sistema não foi transmitido corretamente para esta janela.");
        return;
    }
    processarAgendamento("14:00", getOrCreatePacienteTeste());
}

void TelaDataHora::on_btnHora1430_clicked() {
    if (!sistema) {
        QMessageBox::critical(this, "Erro", "O sistema não foi transmitido corretamente para esta janela.");
        return;
    }
    processarAgendamento("14:30", getOrCreatePacienteTeste());
}

void TelaDataHora::on_btnHora1500_clicked() {
    if (!sistema) {
        QMessageBox::critical(this, "Erro", "O sistema não foi transmitido corretamente para esta janela.");
        return;
    }
    processarAgendamento("15:00", getOrCreatePacienteTeste());
}

//se apertar em voltar, abre a tela anterior
void TelaDataHora::on_btnVoltar_clicked() {
    TelaEspecialidade *tela = new TelaEspecialidade(nullptr, sistema);
    tela->setAttribute(Qt::WA_DeleteOnClose);
    tela->show();
    this->close();
}