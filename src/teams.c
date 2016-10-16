#include "teams.h"

/**
 Scripts que cuidam das equipes 
*/


/*
    Cria uma equipe de ciclistas 
    Rece @num_cyclists que sera o numero de cada ciclista em cada equipe 
*/
Teams *teams_new(int num_cyclists, int track_distance, int init_speed) {

    static Teams teams[2];
    int i, j, position;

    for(i = 0; i < 2; i++) {

        teams[i].total_cyclists = num_cyclists;
        teams[i].cyclists = malloc(sizeof(Cyclist) * teams[i].total_cyclists);

        for(j = 0; j < teams[i].total_cyclists; j++) {
            teams[i].cyclists[j] = malloc(sizeof(Cyclist));
           
            /* Verifica que time pertence e seta posicao inicial */
            position = i == 0 ? 1 : track_distance / 2;
        
            teams[i].cyclists[j] = cyclist_new(i, init_speed, position);
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


int teams_get_last(Teams *teams, int id_team) {
    
    int i;
    int last = 0;
    int total = teams[id_team].total_cyclists;
    int p1;

    for(i = 0; i < total; i++) {
        if(teams[id_team].cyclists[i]->is_break) continue;
        p1 = teams_get_position(teams, id_team, i);
        break;
    }

    for(i = 0; i < total; i++)  {
        
        if(teams[id_team].cyclists[i]->is_break) continue;
        
        int p2 = teams_get_position(teams, id_team, i);

        if(p2 > p1) {
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
void teams_print(Teams *teams, int team_id) {

    int i;

    for(i = 0; i <  teams[team_id].total_cyclists; i++) {

        if(!teams[team_id].cyclists[i]->is_break) {

            printf("Ciclista: %d\n", teams[team_id].cyclists[i]->id);
            printf("Time: %d\n", team_id);
            printf("Velocidade: %d\n", teams[team_id].cyclists[i]->speed);
            printf("Posicao: %d\n", teams_get_position(teams, team_id, i));
            printf("\n");
        }

    }
   
}


int teams_get_position(Teams *teams, int team_id, int cyclist_key) {

    int i = 0;
    int position = 1;
    int my_position = teams[team_id].cyclists[cyclist_key]->position;

    for(i = 0; i < teams[team_id].total_cyclists; i++) 
        if(teams[team_id].cyclists[i]->position > my_position)
            position++;


    return position;

}

