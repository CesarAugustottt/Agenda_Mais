#include "TelaDataHora.h"
#include "AppointmentImpl.h" // Inclui a implementação do Handle-Body
#include "TelaEspecialidade.h"
#include <QMessageBox>

TelaDataHora::TelaDataHora(QWidget *parent, Specialty esp) 
    : QWidget(parent), espSelecionada(esp) 
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

void TelaDataHora::processarAgendamento(const std::string& horario) {
    std::string dataStr = calendarioWidget->selectedDate().toString("dd/MM/yyyy").toStdString();
    std::string nomePaciente = "Paciente Fixo"; // Simulação
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

    // Criando o objeto com a assinatura correta de 6 parâmetros
    Appointment* novoAgendamento = new AppointmentHandle(
        nomePaciente, 
        nomeMedico, 
        dataStr, 
        horario, 
        Status::PENDING, 
        espSelecionada
    );

    QString msg = QString::fromStdString("Consulta Solicitada!\n\nCom: " + nomeMedico + "\nData: " + dataStr + "\nHora: " + horario);
    QMessageBox::information(this, "Sucesso", msg);

    //CORREÇÃO DO MEMORY LEAK
    // Como este agendamento ainda não é guardado no banco de dados em memória do AppointmentController,
    // precisamos de o apagar no final para não sobrecarregar a memória RAM.
    delete novoAgendamento;

    this->close();
}

void TelaDataHora::on_btnHora1330_clicked() { processarAgendamento("13:30"); }
void TelaDataHora::on_btnHora1400_clicked() { processarAgendamento("14:00"); }
void TelaDataHora::on_btnHora1430_clicked() { processarAgendamento("14:30"); }
void TelaDataHora::on_btnHora1500_clicked() { processarAgendamento("15:00"); }

//se apertar em voltar, abre a tela anterior
void TelaDataHora::on_btnVoltar_clicked() {
    TelaEspecialidade *tela = new TelaEspecialidade(nullptr);
    tela->setAttribute(Qt::WA_DeleteOnClose);
    tela->show();
    this->close();
}