
#include "simulator.h"


int start = FALSE;


/* Inicia a simulacao */
void simulator_start(int track_distance, int num_cyclists) {

    int i, j, err;

    /* Numero total de voltas de cada equipe*/
    int laps[2] = {0,};

    /* Cria a pista */
    track_new(track_distance, num_cyclists);

    /* Cria times */
    Teams *teams = teams_new(num_cyclists, track_distance);


    /* Cria as threads */
    for(i = 0; i < 2; i++) {
        for(j = 0; j < teams[i].total_cyclists; j++)
            err = pthread_create(&teams[i].cyclists[j]->thread, 
                                NULL,
                                cyclist_run,
                                (void *) teams[i].cyclists[j]
                                );
            
            /* erro ao criar a thread */
            if(err) {
                 printf("Erro ao criar thread do ciclista %d", teams[i].cyclists[j]->id);
                 exit(1);
             }
    }


    simulator_start_running(teams);

    while(laps[0] != MAX_LAPS && laps[1] != MAX_LAPS) {
       
       start = TRUE;
       //msleep(SLEEP * 10);
    //   //     teams_print(teams);
       msleep(SLEEP);
       track_print_positions();



       for(i = 0; i < 2; i++) {
           int last = teams_get_last(teams, i, track.size);

           if(teams[i].cyclists[last]->position == teams[i].cyclists[last]->start_position) {
                
                /* Ultimo cruzou a chegada */
                laps[i]++;
                
                /* Sorteia um ciclista para quebrar  */
               // if((laps[i] % 2) == 1) {
                    
                    int id_break = simulator_break_cyclist(teams, i);
                    
                    /* Quebrou */
                    if(id_break >= 0) {
                        printf("Ciclista %d quebrou na volta %d e estava na posicao %d\n ", teams[i].cyclists[id_break]->id, laps[i], teams_get_position(teams, i, id_break));
                        msleep(SLEEP * 10);
                    } 
                //}
           } 
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
       
        int total = teams[i].total_cyclists;
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

/* Retorna o id do ciclista quebrado ou -1 caso nao houve quebra */
int simulator_break_cyclist(Teams *teams, int team_id) {
    int total = teams[team_id].total_cyclists;
    int i;
    int break_cyclists = 0;

    for(i = 0; i < total; i++) 
        if(!teams[team_id].cyclists[i]->is_break) break_cyclists++;
    

    if(break_cyclists > 3) {
        /* 10% de chance de quebrar */
        int r = randmax(10);

        if (r == 5)  {
            /* Procuro um ciclista que nao esteja quebrado */
            while(TRUE) {
                int i = randmax(total);
                /* Nao esta quebrado */
                if(!teams[team_id].cyclists[i]->is_break) {
                    teams[team_id].cyclists[i]->is_break = TRUE;
                    return i;
                }
            }
        }
    }

    return -1;
}

