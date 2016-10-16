/*******
Autor: Thiago Ivan Silva Pereira
*******/


#ifndef _CONFIG_H
#define _CONFIG_H

/**
Define algumas macros de configuracao do programa
*/


/* Define que velocidade variadas seram usadas */
#define V_RANDOM 0

/* Define que velocidade uniformes seram usadas */
#define  V_UNIFORM 1

/* Numero total de voltas */
#define MAX_LAPS 16

/*Em milisegundos*/
#define SLEEP 60 

/* Define tamanho minimo da pista */
#define MIN_TRACK_DISTANCE 250

/* Define minimo de ciclistas */
#define MIN_CYCLISTAS 4

/* Numero maximo de ciclistas lado a lado */
#define MAX_CYCLIST_SIDE 2

/* Define velocidades permitidas (Km/h) */
enum{
    V1=30,
    V2=60
};

#endif

