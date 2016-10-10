#include <stdio.h>
#include <stdlib.h>

#include "error.h"

void error(int error) {

    switch(error) {
        case ARGC_ERR: printf("Erro %d: Numero de argumentos invalido\n", error); break;
        case ARGV_ERR: printf("Erro %d: Valores de argumentos invalido\n", error); break;
        default: printf("Erro!");
    }
}