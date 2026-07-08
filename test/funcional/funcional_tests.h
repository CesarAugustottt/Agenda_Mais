#ifndef FUNCIONAL_TESTS_H
#define FUNCIONAL_TESTS_H

#include "../../src/System.h"

// Função fábrica global que cria a instância do sistema
extern System* createSystem();

// Cenários de Testes Isolados
void test_user_management();
void test_appointment_flow();
void test_medication_stock();
void test_reservation_flow();
void test_system_deletes();

// Função master que roda toda a suite de testes funcionais
void run_all_functional_tests();

#endif // FUNCTIONAL_TESTS_H