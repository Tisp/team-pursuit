#include "teams.h"

/**
 Scripts que cuidam das equipes 
*/


/*
    Cria uma equipe de ciclistas 
    Rece @num_cyclists que sera o numero de cada ciclista em cada equipe 
*/
Teams *teams_new(int num_cyclists, int track_distance) {

    static Teams teams[2];
    int i, j, position;

    for(i = 0; i < 2; i++) {
        teams[i].total_cyclists = num_cyclists;
        teams[i].cyclists = malloc(sizeof(Cyclist) * teams[i].total_cyclists);

        for(j = 0; j < teams[i].total_cyclists; j++) {
            teams[i].cyclists[j] = malloc(sizeof(Cyclist));
           
            /* Verifica que time pertence e seta posicao inicial */
            position = i == 0 ? 0 : track_distance / 2;
        
            teams[i].cyclists[j] = cyclist_new(i, V1, position);
        }
    }
       
    return teams;
}

/* Libera memoria de um time */
void teams_destroy(Teams *teams) {
    int i, j;

    for(j = 0; j < 2; j++) {
        for(i = 0; i < teams[j].total_cyclists; i++) 
            free(teams[j].cyclists[i]);
    }

    free(teams);
    
}


int teams_get_last(Teams *teams, int id_team, int track_size) {
    
    int i;
    int last = 0;
    int p1 = (teams[id_team].cyclists[0]->position +  teams[id_team].total_cyclists) % track_size;

    for(i = 1; i < teams[id_team].total_cyclists; i++)  {

        int p2 = (teams[id_team].cyclists[i]->position +  teams[id_team].total_cyclists) % track_size;

        if(p2 < p1) {
            p1 = p2;
            last = i;
        }

    }

    return last;
}

/* Muda a velocidade de todo o time */
void teams_change_speed(Teams *teams, int id_team, int speed) {
    int i;

    for(i = 0; i <  teams[id_team].total_cyclists; i++) 
            teams[id_team].cyclists[i]->speed = speed;
}


/* Printa os dados de todos os ciclistas */
void teams_print(Teams *teams) {

    int i, j;

    for(i = 0; i < 2; i++) {
        for(j = 0; j <  teams[i].total_cyclists; j++) {
            printf("Ciclista: %d\n", teams[i].cyclists[j]->id);
            printf("Time: %d\n", i);
            printf("Velocidade: %d\n", teams[i].cyclists[j]->speed);
            printf("Posicao: %d\n", teams[i].cyclists[j]->position);
            printf("Quebrado: %s\n", teams[i].cyclists[j]->is_break ? "Sim" : "Nao");
            printf("\n");
        }
   }

}

