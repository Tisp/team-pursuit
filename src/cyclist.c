#include "cyclist.h"

/* Variavel global para criacao de ids dos ciclistas */
int serial_cyclist = 0;

int start;
Track track;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int laps;

/*Cria um novo ciclista com o id da equipe especifica */
Cyclist *cyclist_new(int team_id, int speed, int position) {

    Cyclist *cyclist = malloc(sizeof(Cyclist));
    cyclist->id = serial_cyclist++;
    cyclist->team_id = team_id;
    cyclist->speed = speed;
    cyclist->position = position;
    cyclist->is_break = FALSE;
    cyclist->init_position = position;

    return cyclist;
}

/* Destroi um ciclista */
void cyclist_destroy(Cyclist *cyclist) {
    free(cyclist);
}


/* Funcao para thread */
void *cyclist_run(void *args) {

    Cyclist *cyclist = args;

    while(TRUE) {

        /* Espera a prova iniciar */
        if(!start) continue;
        
        /* SECAO CRITICA */
        pthread_mutex_lock(&mutex);

            int i = 0;

            /* Caso andou apenas meio metro, dormir metade */
            if(cyclist->speed == V1) msleep(SLEEP / 2);
            
            /* Calcula nova posicao */
            int my_position = (cyclist->position + 1) % track.size;
        
            /* Vejo se aquele local ta pista esta vazio */
            for(i = 0; i < MAX_CYCLIST_SIDE; i++) {
                /* Posicao vazia */
                if(track.position[my_position].stretch[i] == -1) {
                    
                    /* Adiciona a posicao nova */
                    track.position[my_position].stretch[i] = cyclist->id;

                    /* Remove a posicao antiga */
                    track.position[cyclist->position].stretch[i] = -1;

                    break;
                }
                    
            }

            cyclist->position = my_position;    

            if(my_position == cyclist->init_position) laps++;

            
        pthread_mutex_unlock(&mutex);
        /* FIM DA SECAO CRITICA */

        /* Se a velocidade for a menor dormir apenas metade, pois ja dormiu */
        cyclist->speed == V1 ? msleep(SLEEP / 2) : msleep(SLEEP);        

    }

}