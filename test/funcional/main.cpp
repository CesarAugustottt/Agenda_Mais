#include "funcional_tests.h"

int main() {
    // Roda todos os testes divididos em subfunções
    run_all_functional_tests();
    return 0;
}


int numHandleCreated = 0;
int numHandleDeleted = 0;
int numBodyCreated = 0;
int numBodyDeleted = 0;

/*
make clean
make
make run_funcional
make run_unit
*/