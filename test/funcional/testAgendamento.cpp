#include "testAgendamento.h"
#include "../../interface/tela_agendamentos/TelaEspecialidade.h"
#include "../../interface/tela_agendamentos/TelaDataHora.h"

void TestAgendamento::testFluxoAgendamentoCompleto() {
    //TESTANDO A TELA DE ESPECIALIDADE
    TelaEspecialidade telaEsp;
    telaEsp.show();
    QVERIFY(telaEsp.isVisible()); //valida se abriu

    QTest::qWait(1500);//congela a tela por 1.5s

    // Buscando o botão de Dentista na interface (1° botao)
    //QPushButton* btnDentista = telaEsp.findChild<QPushButton*>();
    
    //lista de botaoes
    QList<QPushButton*> botoes = telaEsp.findChildren<QPushButton*>();
    QPushButton* btnAlvo = nullptr;
    for (QPushButton* btn : botoes) { //buscar botao dentista
        if (btn->text() == "Dentista") {
            btnAlvo = btn;
            break;
        }
    }
    
    //verificar se existe o botao de dentista
    QVERIFY2(btnAlvo != nullptr, "Botão Dentista não foi encontrado na tela.");

    // Simula o clique do usuário no botão de Dentista
    QTest::mouseClick(btnAlvo, Qt::LeftButton);

    //TESTANDO A PROXIMA TELA (Data e Hora)
    // Vamos instanciar diretamente para testar os componentes internos
    TelaDataHora telaDataHora(nullptr, Specialty::DENTIST);
    telaDataHora.show();
    QVERIFY(telaDataHora.isVisible()); //valida se abriu

    QTest::qWait(1500);

    // Localizando o calendário e os botões de hora
    QCalendarWidget* calendario = telaDataHora.findChild<QCalendarWidget*>();
    QVERIFY(calendario != nullptr); //valida se tem o calendario

    QList<QPushButton*> botoesHora = telaDataHora.findChildren<QPushButton*>();
    QPushButton* btnHora = nullptr;
    for (QPushButton* btn : botoesHora) { //buscar botão de 13h30
        if (btn->text() == "13:30") {
            btnHora = btn;
            break;
        }
    }
    QVERIFY2(btnHora != nullptr, "Botão de horário 13:30 não foi encontrado.");

    // agendar um fechamento automático dele em 1 segundo para o teste não travar no vídeo!
    QTimer::singleShot(1000, []() {
        QWidget* activeModal = QApplication::activeModalWidget();
        if (activeModal) {
            activeModal->close(); //fechar tela de mensagem apos ok
        }
    });

    // Simular o clique no horário para disparar a função "processarAgendamento"
    QTest::mouseClick(btnHora, Qt::LeftButton);

    // Verifica se a tela fechou após o agendamento concluído
    QTest::qWait(1500); // Aguarda o modal sumir
    QVERIFY(!telaDataHora.isVisible());
}