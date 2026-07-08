#ifndef FUNCTIONAL_TESTS_H
#define FUNCTIONAL_TESTS_H

#include "../../src/System.h"
#include <cassert>
#include <iostream>

//! Functional tests header
/**
 * Prototypes for the functional tests of the Agenda+.
 * This file declares the test cases responsible for validating the lifecycle,
 * resource allocation, and core entities like Users, Appointments, Medications, and Reservations.
 */


/*!
  Function prototype for the user management functional test.
*/
void test_user_management();

/*!
  Function prototype for the appointment workflow functional test.
*/
void test_appointment_flow();

/*!
  Function prototype for the medication stock control functional test.
*/
void test_medication_stock();

/*!
  Function prototype for the medicine reservation flow functional test.
*/
void test_reservation_flow();

/*!
  Function prototype for the system entities safe deletions functional test.
*/
void test_system_deletes();

/*!
  Function prototype to run the complete suite of functional tests.
*/
void run_all_functional_tests();

#endif // FUNCTIONAL_TESTS_H