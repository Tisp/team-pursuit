/*******
Autor: Thiago Ivan Silva Pereira
*******/
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <math.h>

#include "config.h"
#include "util.h"
#include "error.h"
#include "cyclist.h"
#include "track.h"


/* Define variavel global para debug */
int debug = FALSE;

int main(int argc, char **argv) {

    /* Verifica o numero total de argumentos */
    if(argc < 4 || argc > 5) {
        help(argv[0]);
        error(ARGC_ERR);
        exit(-1);
    }
    
    /* Tamanho total da pista */
    int track_distance = atoi(argv[1]);

    /* Quantidade maxima de ciclistas por equipe (em metros) */
    int qtd_distance =  (int)ceil((float)track_distance / 4);

    /* Numero de ciclistas */ 
    int num_cyclists = atoi(argv[2]); 
    
    /* Tipo de velocidade simulada */
    int speed_type = (strcmp("v", argv[3]) == 0) ? V_RANDOM : V_UNIFORM;

    /* Verifica se o debug foi acionado */
    debug = (argc == 5 && strcmp("d", argv[4]) == 0) ? TRUE : FALSE;

    /* Verifica se os valores do argumentos e valido */
    if(track_distance < MIN_TRACK_DISTANCE || num_cyclists < MIN_CYCLISTAS) {
        help(argv[0]);
        error(ARGV_ERR);
        exit(-1);
    }

    /* Gera uma semente para o programa */
    srand((unsigned)time(NULL));

    /* Inicia a simulacao */
    simulator_start(track_distance, num_cyclists, speed_type);

    return 0;
}