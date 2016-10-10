#ifndef _CYCLIST_H
#define _CYLIST_H


typedef struct _cyclist {

    int team_id;
    int speed;
    int is_break;
    pthread_t thread;

} Cyclist;

#endif