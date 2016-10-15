
#include "simulator.h"


int start = FALSE;


/* Inicia a simulacao */
void simulator_start(int track_distance, int num_cyclists) {

    int i, j;

    /* Numero total de voltas de cada equipe*/
    int laps[2] = {0,};

    /* Cria a pista */
    track_new(track_distance, num_cyclists);

    /* Cria times */
    Teams *teams = teams_new(num_cyclists, track_distance);

    //  teams_print(teams);

    /* Cria as threads */
    for(i = 0; i < 2; i++) {
        for(j = 0; j < teams[i].total_cyclists; j++)
             pthread_create(&teams[i].cyclists[j]->thread, NULL, cyclist_run, (void *) teams[i].cyclists[j]);
    }


    simulator_start_running(teams);

    while(laps[0] != MAX_LAPS && laps[1] != MAX_LAPS) {
       
       start = TRUE;
       msleep(SLEEP);
       track_print_positions();

       for(i = 0; i < 2; i++) {
           int last = teams_get_last(teams, i, track.size);

           printf("%d\n", teams[i].cyclists[last]->id );
           
           if(teams[i].cyclists[last]->position == teams[i].cyclists[last]->init_position) laps[i]++;
       }

       printf("Volta Time 1: %d \n", laps[0]);
       printf("Volta Time 2: %d \n", laps[1]);
       
    }

     //teams_destroy(teams);
}


/* Simula a largada, sorteado aleatoriamente quem corre mais */
void simulator_start_running(Teams *teams) {
    
    int i, j;
    
    /* Organiza largada, sorteado quem ira comecar  */
    for(i = 0; i < 2; i++) {
       
        int total = teams[i].total_cyclists - 1;
        int raf[total];
        
        /* Coloca todos verores de raf como false */
        for(j = 0; j < total; j++) raf[j] = FALSE;
        
        int s = total;
        
        while(s > 0) {
            int r = randmax(total);
            if(!raf[r]) {
                 teams[i].cyclists[r]->position += total;
                 raf[r] = TRUE;
                 s--;
            }
        }
    }

    msleep(SLEEP);
}



