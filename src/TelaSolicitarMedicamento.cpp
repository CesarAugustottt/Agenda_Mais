#include "TelaSolicitarMedicamento.h"
#include <QMessageBox>

TelaSolicitarMedicamento::TelaSolicitarMedicamento(QWidget *parent, MedicationsController* controller)
    : QWidget(parent), controller(controller)
{
    this->resize(420, 420);
    this->setWindowTitle("Solicitar Medicamento");

    layoutPrincipal = new QVBoxLayout(this);

    lblCpf = new QLabel("CPF do Paciente:", this);
    txtCpf = new QLineEdit(this);
    layoutPrincipal->addWidget(lblCpf);
    layoutPrincipal->addWidget(txtCpf);

    lblMedicamento = new QLabel("Medicamento:", this);
    cbxMedicamento = new QComboBox(this);
    layoutPrincipal->addWidget(lblMedicamento);
    layoutPrincipal->addWidget(cbxMedicamento);

    lblEstoqueDisponivel = new QLabel(this);
    lblExigeReceita = new QLabel(this);
    layoutPrincipal->addWidget(lblEstoqueDisponivel);
    layoutPrincipal->addWidget(lblExigeReceita);

    lblQuantidade = new QLabel("Quantidade:", this);
    spinQuantidade = new QSpinBox(this);
    spinQuantidade->setMinimum(1);
    layoutPrincipal->addWidget(lblQuantidade);
    layoutPrincipal->addWidget(spinQuantidade);

    lblReceita = new QLabel("Caminho da Receita (obrigatório se exigir receita):", this);
    txtCaminhoReceita = new QLineEdit(this);
    layoutPrincipal->addWidget(lblReceita);
    layoutPrincipal->addWidget(txtCaminhoReceita);

    btnSolicitar = new QPushButton("Solicitar", this);
    btnVoltar = new QPushButton("Voltar", this);
    layoutPrincipal->addWidget(btnSolicitar);
    layoutPrincipal->addWidget(btnVoltar);

    connect(cbxMedicamento, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &TelaSolicitarMedicamento::on_cbxMedicamento_currentIndexChanged);
    connect(btnSolicitar, &QPushButton::clicked, this, &TelaSolicitarMedicamento::on_btnSolicitar_clicked);
    connect(btnVoltar, &QPushButton::clicked, this, &TelaSolicitarMedicamento::on_btnVoltar_clicked);

    carregarMedicamentos();
}

TelaSolicitarMedicamento::~TelaSolicitarMedicamento() {}

void TelaSolicitarMedicamento::carregarMedicamentos() {
    if (!controller) {
        QMessageBox::critical(this, "Erro", "Controlador de medicamentos não inicializado.");
        return;
    }

    medicamentosDisponiveis = controller->getAllMedications();
    cbxMedicamento->clear();

    for (auto med : medicamentosDisponiveis) {
        cbxMedicamento->addItem(QString::fromStdString(med->getName()));
    }

    atualizarInfoMedicamento();
}

void TelaSolicitarMedicamento::atualizarInfoMedicamento() {
    int index = cbxMedicamento->currentIndex();
    if (index < 0 || index >= (int)medicamentosDisponiveis.size()) {
        lblEstoqueDisponivel->setText("Estoque disponível: -");
        lblExigeReceita->setText("Exige receita: -");
        return;
    }

    Medication* med = medicamentosDisponiveis[index];
    lblEstoqueDisponivel->setText(QString("Estoque disponível: %1").arg(med->getQuantity()));
    lblExigeReceita->setText(med->requiresPrescription() ? "Exige receita: Sim" : "Exige receita: Não");
    spinQuantidade->setMaximum(med->getQuantity() > 0 ? med->getQuantity() : 1);
}

void TelaSolicitarMedicamento::on_cbxMedicamento_currentIndexChanged(int index) {
    Q_UNUSED(index);
    atualizarInfoMedicamento();
}

void TelaSolicitarMedicamento::on_btnSolicitar_clicked() {
    if (!controller) {
        QMessageBox::critical(this, "Erro", "Controlador de medicamentos não inicializado.");
        return;
    }

    std::string cpf = txtCpf->text().toStdString();
    if (cpf.empty()) {
        QMessageBox::warning(this, "Atenção", "Informe o CPF do paciente.");
        return;
    }

    int index = cbxMedicamento->currentIndex();
    if (index < 0 || index >= (int)medicamentosDisponiveis.size()) {
        QMessageBox::warning(this, "Atenção", "Selecione um medicamento.");
        return;
    }

    Medication* medicamentoSelecionado = medicamentosDisponiveis[index];
    int quantidade = spinQuantidade->value();
    std::string caminhoReceita = txtCaminhoReceita->text().toStdString();

    if (medicamentoSelecionado->requiresPrescription() && caminhoReceita.empty()) {
        QMessageBox::warning(this, "Atenção", "Este medicamento exige receita. Informe o caminho do arquivo da receita.");
        return;
    }

    if (medicamentoSelecionado->getQuantity() < quantidade) {
        QMessageBox::warning(this, "Estoque insuficiente", "Não há estoque suficiente para essa quantidade.");
        return;
    }

    Reservation* reserva = controller->requestMedication(cpf, medicamentoSelecionado, quantidade, caminhoReceita);
    if (!reserva) {
        QMessageBox::critical(this, "Erro", "Não foi possível registrar a solicitação.");
        return;
    }

    QMessageBox::information(this, "Sucesso", "Solicitação de medicamento enviada! Aguarde a avaliação da secretária.");

    carregarMedicamentos(); // atualiza a tela com o estoque já descontado
    txtCpf->clear();
    txtCaminhoReceita->clear();
    spinQuantidade->setValue(1);
}

void TelaSolicitarMedicamento::on_btnVoltar_clicked() {
    this->close();
}