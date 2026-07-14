#ifndef UNIT_TESTS_H
#define UNIT_TESTS_H

#include "../../src/System.h"
#include "../../src/MedicationsController.h"
#include <cassert>
#include <iostream>

//! Unit tests header
/**
 * Testes unitários da Agenda+. Ao contrário dos testes funcionais (que validam
 * fluxos completos), aqui cada teste isola uma única unidade de comportamento:
 * um getter/setter específico, uma regra de negócio pontual, um caso de borda.
 */

// ---- Appointment ----
void test_appointment_default_status_is_pending();
void test_appointment_setStatus_changes_status();
void test_appointment_setJustificativa_stores_text();
void test_appointment_justificativa_default_is_empty();

// ---- Medication ----
void test_medication_decreaseStock_exact_amount();
void test_medication_decreaseStock_insufficient_returns_false();
void test_medication_decreaseStock_zero_amount();
void test_medication_setQuantity_overwrites_value();

// ---- Reservation ----
void test_reservation_default_status_is_pending();
void test_reservation_setStatus_changes_status();
void test_reservation_setJustification_stores_text();

// ---- User ----
void test_user_created_active_by_default();
void test_user_type_is_stored_correctly();

// ---- MedicationsController ----
void test_controller_requestMedication_decreases_stock();
void test_controller_requestMedication_fails_when_stock_insufficient();
void test_controller_refuseReservation_returns_stock();
void test_controller_approveReservation_does_not_change_stock();

void run_all_unit_tests();

#endif // UNIT_TESTS_H