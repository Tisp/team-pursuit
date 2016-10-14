#include "cyclist.h"

/* Variavel global para criacao de ids dos ciclistas */
int serial_cyclist = 0;

int start;

/*Cria um novo ciclista com o id da equipe especifica */
Cyclist *cyclist_new(int team_id, int speed, int position) {

    Cyclist *cyclist = malloc(sizeof(Cyclist));
    cyclist->id = serial_cyclist++;
    cyclist->team_id = team_id;
    cyclist->speed = speed;
    cyclist->position = position;
    cyclist->is_break = FALSE;

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

        if(!start) continue;

        printf("Iniciei, sou o ciclista %d\n\n", cyclist->id);
        return NULL;

    }

}