# Agenda_Mais

**Nome:** César Augusto Tiago Totô  
**Matrícula:** 24.1.4038  

**Nome:** Luiz Fernando Modesto Freitas Rezende  
**Matrícula:** 24.2.4038 

**Nome:** Pedro Vitor Silva Cruz   
**Matrícula:** 24.2.4086

**Nome:** Rafael Araújo Granato     
**Matrícula:** 24.2.4085

## Descrição do Projeto
O **Agenda+** é um sistema web para agendamento de pacientes, desenvolvido especificamente para otimizar e organizar a marcação de consultas em clínicas e consultórios médicos. O projeto visa facilitar a comunicação entre pacientes, recepcionistas e médicos, centralizando a gestão de horários, usuários e estoques de medicamentos.

## Tecnologias Utilizadas
* Linguagem C++
* Compilador G++ / Make
* Git e GitHub (GitFlow)
* QT 

## Estrutura do Repositório
* `src/`: Código fonte (.cpp) com as implementações das funcionalidades e cabeçalhos (.h).
* `bin/`: Binários e executáveis.
* `test/`: Testes funcionais e regressivos.
* `doc/`: Documentação técnica.

## Como Compilar e Executar
Para compilar todo o projeto:
```bash
make all
```

Para rodar os testes funcionais:
```bash
make run_funcional
```

Para rodar os testes unitários:
```bash
make run_unit
```

## Fluxo de Desenvolvimento
O projeto segue um padrão rigoroso de ramificações para garantir a estabilidade e a qualidade do código:

1.  **master:** Código estável e pronto para produção (versão final).
2.  **staging:** Ambiente de pré-produção para testes finais.
3.  **develop:** Integração de novas funcionalidades que já passaram nos testes de regressão.
4.  **feat-:** Ramos temporários para desenvolvimento de funcionalidades específicas
