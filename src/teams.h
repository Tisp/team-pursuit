#ifndef _TEAMS_H
#define _TEAMS_H

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "util.h"
#include "cyclist.h"


/* Estrutura de que guarda os times */
typedef struct _teams {
    int total_cyclists; /* id do ciclista*/
    Cyclist **cyclists;
} Teams;

Teams *teams_new(int num_cyclists, int track_distance);

void teams_destroy(Teams *teams);

void teams_print(Teams *teams);

void teams_change_speed(Teams *teams, int id_team, int speed);

int teams_get_last(Teams *teams, int id_team, int track_size);

int teams_get_position(Teams *teams, int team_id, int cyclist_key);



#endif