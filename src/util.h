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

void msleep(int ms);


int randmax(int max);

#endif
