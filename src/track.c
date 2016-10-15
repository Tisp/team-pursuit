#include "track.h"


int laps;
/* Cria um nova pista
   Utiliza a variavel global track
*/
void track_new(int track_distance, int num_cyclists) {

    int i, j;

    /* Aloca memoria para pista */
    track.size = track_distance;
    track.position = calloc(track_distance, sizeof(track));

    for(i = 0; i < track_distance; i++) {
        track.position[i].stretch = calloc(MAX_CYCLIST_SIDE, sizeof(int));
        for(j = 0; j < MAX_CYCLIST_SIDE; j++)
             track.position[i].stretch[j] = -1;
    }
}


void track_print_positions() {
    int i, j;

    for(j = 0; j < MAX_CYCLIST_SIDE; j++) {
        for(i = 0; i < track.size; i++) {
            if(track.position[i].stretch[j] < 0) {
                printf("_");
             } else {
                printf("[%d]", track.position[i].stretch[j]);
             }
        }
        printf("\n");
  }
}