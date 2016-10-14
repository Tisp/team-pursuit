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

/* Inicia a simulacao */
void start_simulation(int track_distance, int num_cyclists) {


    int i;

    /* Cria a pista */
    track_new(track_distance, num_cyclists);

    /* Cria times */
    Teams teams = teams_new(num_cyclists, track_distance);

    teams_print(teams);

    for(i = 0; i < teams.total_cyclists; i++)
        pthread_create(&teams.cyclists[i]->thread, NULL, cyclist_run, (void *) teams.cyclists[i]);

    printf("esperando, jaja inicio as threads\n");
    start = TRUE;


    msleep(5000);

  // teams_destroy(teams);
    
}



