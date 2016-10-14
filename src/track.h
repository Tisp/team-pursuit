#ifndef _TRACK_H
#define _TRACK_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "config.h"
#include "util.h"


typedef struct _track_positions {
    /* Guarda as posicoes dos ciclistas no trecho */
    int *stretch;

} TrackPositions;

/* Estrutura do tipo PISTA */
typedef struct _track {
    int size;
    TrackPositions *position;
} Track;


/* Variavel global para pista */
Track track;

/* Cria um nova pista */
void track_new(int track_distance, int num_cyclists);

#endif