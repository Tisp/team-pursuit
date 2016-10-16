#include "cyclist.h"

/* Variavel global para criacao de ids dos ciclistas */
int serial_cyclist = 0;
int laps[2];
int start;
Track track;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*Cria um novo ciclista com o id da equipe especifica */
Cyclist *cyclist_new(int id_team, int speed, int position) {

    Cyclist *cyclist = malloc(sizeof(Cyclist));
    cyclist->id = serial_cyclist++;
    cyclist->team_id = id_team;
    cyclist->speed = speed;
    cyclist->position = position;
    cyclist->team_position = 0;
    cyclist->is_break = FALSE;
    cyclist->is_last = FALSE;
    cyclist->start_position = position;

    return cyclist;
}

/* Destroi um ciclista */
void cyclist_destroy(Cyclist *cyclist) {
    free(cyclist);
}


/* Funcao para thread */
void *cyclist_run(void *args) {

    Cyclist *cyclist = args;
    int i = 0;

    while(TRUE) {

        /* Espera a prova iniciar */
        if(!start) continue;

        /* Ciclista quebrou, destroi a thread  */
        if(cyclist->is_break) {
            track.position[cyclist->position].stretch[0] = -1;
            return NULL;
        }

        int runned = FALSE;

        /* Caso andou apenas meio metro, dormir metade */
        if(cyclist->speed == V1) msleep(SLEEP / 2);
        
        /* Calcula nova posicao */
        int new_position = (cyclist->position + 1) % track.size;
    
        while(!runned) {
    
            /* Posicao vazia */
            if(track.position[new_position].stretch[i] == -1) {
                           
                 /* SECAO CRITICA */
                pthread_mutex_lock(&mutex);
    
                    /* Adiciona a posicao nova */
                    track.position[new_position].stretch[i] = cyclist->id;

                    /* Remove a posicao antiga */
                    track.position[cyclist->position].stretch[i] = -1;

                    cyclist->position = new_position;  

                    /* Completou uma volta */
                    if(cyclist->position == cyclist->start_position && cyclist->is_last) {
                        laps[cyclist->team_id]++;
                    } 
         
                /* FIM DA SESSAO CRITICA  */
                pthread_mutex_unlock(&mutex);

                runned = TRUE;

                
            } 
        }
  

        /* Se a velocidade for a menor dormir apenas metade, pois ja dormiu */
        cyclist->speed == V1 ? msleep(SLEEP / 2) : msleep(SLEEP);        

    }
 
}