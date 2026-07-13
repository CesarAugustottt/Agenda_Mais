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

## História de Usuário: Acompanhar Status do Agendamento

### Consulta de Status pelo Paciente
* **Como um** Paciente
* **Eu quero** visualizar o status das minhas consultas solicitadas (pendente, confirmada ou recusada)
* **Para que** eu saiba se preciso aguardar, já posso comparecer, ou preciso remarcar.



#### Cenário 1: Consulta recém-criada aparece como Pendente
* **Dado** que eu solicitei uma consulta e nenhuma secretária/médico ainda avaliou o pedido.
* **Quando** eu abro a tela de acompanhamento e busco pelo meu CPF.
* **Então** o sistema deve exibir a consulta com status `"Pendente"` e justificativa `"-"`.

#### Cenário 2: Consulta confirmada
* **Dado** que minha consulta teve o status alterado para `CONFIRMED` pela secretária.
* **Quando** eu busco pelo meu CPF na tela de acompanhamento.
* **Então** o sistema deve exibir o status `"Confirmada"` e justificativa `"-"`.

#### Cenário 3: Consulta recusada com justificativa
* **Dado** que minha consulta teve o status alterado para `REJECTED` com a justificativa `"Médico indisponível nesse horário"`.
* **Quando** eu busco pelo meu CPF na tela de acompanhamento.
* **Então** o sistema deve exibir o status `"Recusada"` e a justificativa `"Médico indisponível nesse horário"`.

#### Cenário 4: Busca sem CPF mostra todas as consultas
* **Dado** que existem consultas de múltiplos pacientes cadastradas no sistema.
* **Quando** eu deixo o campo de CPF vazio e clico em `"Buscar"`.
* **Então** o sistema deve exibir todas as consultas de todos os pacientes, com a coluna `"Paciente"` identificando cada uma.

#### Cenário 5: Busca com CPF filtra apenas o paciente informado
* **Dado** que existem consultas de mais de um paciente cadastradas no sistema.
* **Quando** eu digito o CPF de um paciente específico e clico em `"Buscar"`.
* **Então** o sistema deve exibir somente as consultas vinculadas àquele CPF.