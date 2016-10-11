#ifndef _TRACK_H
#define _TRACK_H


/* Estrutura do tipo PISTA */
typedef struct _track {
    /* Guarda as posicoes dos ciclistas no trecho */
    int *stretch;
} Track;


/* Variavel global para pista */
Track *track;

/* Cria um nova pista */
void new_track(int track_distance, int num_cyclists);

#endif