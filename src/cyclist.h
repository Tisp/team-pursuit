#ifndef _CYCLIST_H
#define _CYLIST_H



/* Estrutura de um ciclista */
typedef struct _cyclist {
    
    int id; /* id do ciclista*/
    int team_id; /* ID do time do ciclista */
    int speed; /* Sua velocidade */
    int is_break; /* Esta quebrado */
    pthread_t thread;

} Cyclist;

/*Cria um novo ciclista com o id da equipe especifica */
Cyclist *new_cyclist(int team_idm, int speed);

#endif