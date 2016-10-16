/*******
Autor: Thiago Ivan Silva Pereira
*******/

#ifndef _CYCLIST_H
#define _CYCLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#include "util.h"
#include "track.h"

/* Estrutura de um ciclista */
typedef struct _cyclist {
    int id; /* id do ciclista*/
    int team_id; /* id do time */
    int speed; /* Sua velocidade */
    int is_break; /* Esta quebrado */
    int position; /* Guarda a posicao */
    int team_position; /* Posicao relativa no time*/
    int start_position; /*Posicao inicial*/
    int is_last; /* Guarda se o ciclista e o ultimo*/
    pthread_t thread; /* thread */
} Cyclist;

/*Cria um novo ciclista com o id da equipe especifica */
Cyclist *cyclist_new(int id_team, int speed, int position);

/* Destroi um ciclista */
void cyclista_destroy(Cyclist *cyclist);

/* Funcao para thread */
void *cyclist_run(void *args);


#endif