#ifndef _CYCLIST_H
#define _CYCLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#include "util.h"

/* Estrutura de um ciclista */
typedef struct _cyclist {
    int id; /* id do ciclista*/
    int team_id; /* ID do time do ciclista */
    int speed; /* Sua velocidade */
    int is_break; /* Esta quebrado */
    int position; /* Guarda a posicao */
    pthread_t thread;
} Cyclist;

/*Cria um novo ciclista com o id da equipe especifica */
Cyclist *cyclist_new(int team_idm, int speed, int position);


/* Destroi um ciclista */
void cyclista_destroy(Cyclist *cyclist);

/* Funcao para thread */
void *cyclist_run(void *args);


#endif