#ifndef _UTIL_H
#define _UTIL_H


/* Constantes */
enum {FALSE,TRUE};
enum {false, true};

/* Structs  */
typedef struct timespec Timer;



void help(const char *program_name);

float diff_time_s (Timer finish, Timer start);

void get_time(Timer *t);

void msleep(int ms);

#endif
