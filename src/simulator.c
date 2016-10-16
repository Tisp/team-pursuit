/*******
Autor: Thiago Ivan Silva Pereira
*******/
#include "simulator.h"


int start = FALSE;
int laps[2] = {0,};
pthread_mutex_t mutex;
int debug;

/* Inicia a simulacao */
void simulator_start(int track_distance, int num_cyclists, int speed_type) {

    int i, j, new_speed;

    /* Times */
    Timer t_start,
          t_finish,
          t_start_d,
          t_finish_d;

    /* Numero total de voltas de cada equipe*/
    int atual_laps[2] = {0,};

    /* Cria a pista */
    track_new(track_distance, num_cyclists);


    int init_speed = speed_type == V_UNIFORM ? V2 : V1;

    /* Cria times */
    Teams *teams = teams_new(num_cyclists, track_distance, init_speed);

    /* Croa as threads */
    simulator_create_threads(teams);

    /* Guarda o instante de tempo inicial */
    get_time(&t_start);

    /* Time para debug */
    get_time(&t_start_d);

    /* Inicia a largada */
    simulator_start_running(teams);

    /* Arruma as posicoes */
    simulator_update_positions(teams, track.size);

    /* Inicia a prova */
    start = TRUE;

    while(TRUE) {

        /* Debug ativado */
        if(debug) {
             get_time(&t_finish_d);
             if((diff_time_s(t_finish_d, t_start_d)) > 0.06) {
                  track_print_positions();
                  get_time(&t_start_d);
             }
        }

       for(i = 0; i < 2; i++) {

           /* Cruzou a largada */
           if(atual_laps[i] != laps[i]) {

                /* Atualiza o numero da volta */
                atual_laps[i] = laps[i];
                
                int last = teams_get_last(teams, i);     
                
                /* Pega o tempo da cruzada */
                get_time(&t_finish);

                /* Imprime qual volta esta */
                printf("Volta: %d do time %d\n\n", laps[i], i);
                
                /* Imprime o corredor e o tempo que ele cruzou*/
                printf("Ciclista %d cruzou a largada em %lf\n\n", 
                    teams[i].cyclists[last]->id, 
                    diff_time_s(t_finish, t_start)
                );

                /* Imprime os dados dos ciclistas */
                teams_print(teams, i);

                /* Sorteia um ciclista para quebrar  */
               if((laps[i] % 4) == 3) {
                    
                    int id_break = simulator_break_cyclist(teams, i);
                    
                    /* Quebrou */
                    if(id_break >= 0) {
                        printf("Ciclista %d quebrou na volta %d e estava na posicao %d\n ", teams[i].cyclists[id_break]->id, laps[i], teams_get_position(teams, i, id_break));
                    } 
                }
                
                /* Ve se precisa mudar a velocidade */
                if(laps[i] > 1 && speed_type == V_RANDOM) {
                    new_speed = simulator_change_speed(teams, i);
                }

                msleep(SLEEP / 4);
                /* Atualiza as posicoes */
                pthread_mutex_lock(&mutex);
                    simulator_update_positions(teams, track.size);

                    /* Ve se precisa mudar a velocidade */
                    if(laps[i] > 1 && speed_type == V_RANDOM) 
                        teams_change_speed(teams, i, new_speed);
                     
                pthread_mutex_unlock(&mutex);
                
           } 
       }

        /* Terminou a corrida */
        if(laps[0] == MAX_LAPS || laps[1] == MAX_LAPS) break;
    }

    /* Imprime quem venceu */
    if(laps[0] == laps[1]) {
        printf("As equipes empataram\n");
    } else if(laps[0] > laps[1]) {
        printf("A equipe 0 venceu\n");
    } else {
        printf("A equipe 1 venceu\n ");
    }

     pthread_mutex_destroy(&mutex);
     teams_destroy(teams);
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
                 teams[i].cyclists[r]->position += s;
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



/* Retorna o id do ciclista quebrado ou -1 caso nao houve quebra */
int simulator_change_speed(Teams *teams, int team_id) {
    
    int total = teams[team_id].total_cyclists;
    int speed = (randmax(2) == 0) ? V1 : V2;

    /* Procuro um ciclista que nao esteja quebrado */
    while(TRUE) {
        int i = randmax(total);
        /* procura um ciclista nao quebrado */
        if(!teams[team_id].cyclists[i]->is_break) {
            teams[team_id].cyclists[i]->speed = speed;
            return speed;
        }
    }

}


void simulator_create_threads(Teams *teams) {
    
    int i, j, err;
    
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
}


void simulator_update_positions(Teams *teams, int track_size) {

    int i, j;

    for(i = 0; i < 2; i++) {
            for(j = 0; j < teams[i].total_cyclists; j++) {
            int position = teams_get_position(teams, i, j);
            teams[i].cyclists[j]->team_position = position;
            teams[i].cyclists[j]->is_last = FALSE;
        }

         int last = teams_get_last(teams, i);
         teams[i].cyclists[last]->is_last = TRUE;
    }

}
