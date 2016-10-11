#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "config.h"
#include "util.h"
#include "track.h"
#include "cyclist.h"
#include "simulator.h"


int start = FALSE;

/* Inicia a simulacao */
void start_simulation(int track_distance, int num_cyclists) {

    int i;
    int total_cyclists = num_cyclists * 2;
    Cyclist *cyclists[total_cyclists] = create_cyclists(num_cyclists); 

    /* Cria a pista */
    new_track(track_distance, num_cyclists);

    for(i = 0; i < total_cyclists; i++) {
        cyclists[i] = new_cyclist(i % 2, V1);
    }

}


Cyclist **cyclists_create(int num_cyclists) {

    int total_cyclists = num_cyclists * 2;
    Cyclist *cyclists[total_cyclists]; 

    for(i = 0; i < total_cyclists; i++) 
        cyclists[i] = new_cyclist(i % 2, V1);

    return cyclists;
}

void cyclists_destroy(int num_cyclists) {
    
}
