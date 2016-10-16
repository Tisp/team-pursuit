/*******
Autor: Thiago Ivan Silva Pereira
*******/
#ifndef _ERROR_H
#define _ERROR_H

#include <stdio.h>
#include <stdlib.h>

enum {
        ARGC_ERR, /* Erro para o numero total de argumentos */
        ARGV_ERR  /* Erro para entrada de argumetnos */
        };

void error(int error);
#endif