#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "util.h"
#include "cyclist.h"


int serial_cyclist = 0;

/*Cria um novo ciclista com o id da equipe especifica */
Cyclist *new_cyclist(int team_id, int speed) {

    Cyclist *cyclist = malloc(sizeof(Cyclist));
    cyclist->id = serial_cyclist++;
    cyclist->team_id = team_id;
    cyclist->speed = speed;
    cyclist->is_break = FALSE;

    return cyclist;
}


void cyclist_destroy(Cyclist *cyclist) {
    free(cyclist);
}
