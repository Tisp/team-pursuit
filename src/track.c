#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "config.h"
#include "util.h"
#include "track.h"



/* Cria um nova pista
   Utiliza a variavel global track
*/
void new_track(int track_distance, int num_cyclists) {

    int i;

    /* Aloca memoria para pista */
    track = calloc(track_distance, sizeof(track));

    for(i = 0; i < track_distance; i++) 
        track[i].stretch = calloc(MAX_CYCLIST_SIDE, sizeof(int));
}
