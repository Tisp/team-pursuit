#include "teams.h"

/**
 Scripts que cuidam das equipes 
*/


/*
    Cria uma equipe de ciclistas 
    Rece @num_cyclists que sera o numero de cada ciclista em cada equipe 
*/
Teams teams_new(int num_cyclists, int track_distance) {

    Teams teams;
    teams.total_cyclists = num_cyclists * 2;
    teams.cyclists = malloc(sizeof(Cyclist) * teams.total_cyclists);
    int i, team_id, position;

    for(i = 0; i < teams.total_cyclists; i++) {
        teams.cyclists[i] = malloc(sizeof(Cyclist));
        
        team_id = i % 2;
        position = team_id == 0 ? 0 : track_distance / 2;
       
        teams.cyclists[i] = cyclist_new(team_id, V1, position);
    }
        
    return teams;
}

/* Libera memoria de um time */
void teams_destroy(Teams teams) {
    int i = 0;

    for(i = 0; i < teams.total_cyclists; i++) 
        free(teams.cyclists[i]);
}


void teams_print(Teams teams) {

    int i;

    for(i = 0; i <  teams.total_cyclists; i++) {
        printf("Ciclista: %d\n", teams.cyclists[i]->id);
        printf("Time: %d\n", teams.cyclists[i]->team_id);
        printf("Velocidade: %d\n", teams.cyclists[i]->speed);
        printf("Posicao: %d\n", teams.cyclists[i]->position);
        printf("Quebrado: %s\n", teams.cyclists[i]->is_break ? "Sim" : "Nao");
        printf("\n");
    }

}

