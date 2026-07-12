# BDD - Desenvolvimento Orientado a Comportamento {#tests_bdd}

Este documento apresenta as Histórias de Usuário e os Cenários de Teste no formato BDD (Behavior-Driven Development) para as funcionalidades mapeadas no Sprint Backlog do sistema **Agenda Mais**.

---

## História de Usuário: Solicitar Agendamento de Consulta

### Solicitação de Agendamento pelo Paciente
* **Como um** Paciente  
* **Eu quero** selecionar uma especialidade médica, uma data e um horário na interface  
* **Para que** eu possa solicitar uma consulta com o médico disponível.

###Cenários de Teste:

#### Cenário 1: Solicitação com sucesso
* **Dado** que eu sou um Paciente logado no sistema e estou na tela de agendamentos.
* **Quando** eu seleciono a especialidade `"Dentista"`, escolho a data `"20/11/2026"` e clico no horário `"13:30"`.
* **Então** o sistema deve instanciar uma nova entidade de agendamento com status `PENDING`, vinculada ao meu usuário e ao médico disponível, exibindo a mensagem `"Consulta Solicitada!"`.

#### Cenário 2: Horário indisponível por concorrência de Médicos
* **Dado** que o médico da especialidade selecionada já possui uma consulta marcada e confirmada no dia `"20/11/2026"` às `"13:30"`.
* **Quando** eu tento clicar e confirmar o agendamento para esse mesmo dia, especialidade e horário.
* **Então** o sistema deve bloquear a ação na interface gráfica e exibir a mensagem de aviso `"Horário indisponível"`.

#### Cenário 3: Tentativa de agendamento em data retroativa
* **Dado** que eu sou um Paciente logado e a data atual do sistema é `"20/11/2026"`.
* **Quando** eu tento selecionar uma data passada, como `"19/11/2026"`, para qualquer horário.
* **Então** o sistema deve desabilitar os horários correspondentes na interface.
