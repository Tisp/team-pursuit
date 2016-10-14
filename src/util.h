#ifndef _UTIL_H
#define _UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* Constantes boleanas  */
enum {FALSE,TRUE};
enum {false, true};


/* Glabais */

/* Define variavel global para debug */
int debug;

/* Structs  */
typedef struct timespec Timer;

void help(const char *program_name);

float diff_time_s (Timer finish, Timer start);

void get_time(Timer *t);

void msleep(int ms);

#endif
