#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "config.h"
#include "util.h"
#include "track.h"
#include "cyclist.h"
#include "teams.h"
#include "simulator.h"


int start = FALSE;
int laps;


/* Inicia a simulacao */
void start_simulation(int track_distance, int num_cyclists) {

    int i, j;

    /* Cria a pista */
    track_new(track_distance, num_cyclists);

    /* Cria times */
    Teams teams = teams_new(num_cyclists, track_distance);

    teams_print(teams);

    /* Cria as threds */
    for(i = 0; i < teams.total_cyclists; i++)
        pthread_create(&teams.cyclists[i]->thread, NULL, cyclist_run, (void *) teams.cyclists[i]);

    while(laps < MAX_LAPS) {
       start = TRUE;
       track_print_positions();
       printf("Volta: %d \n", laps);
       
    }




  teams_destroy(teams);
    
}



