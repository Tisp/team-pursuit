/*******
Autor: Thiago Ivan Silva Pereira
*******/
#include "util.h"

void help(const char *program_name) {
    printf("\n### Team Pursuit Simulator ### \n\n");
    printf("Tente: %s d n [u|v] [d]\n\n", program_name);
    printf("Argumentos:\n");
    printf("\t d - Tamanho da pista do velodromo em metros (d > 249)\n");
    printf("\t n - Numero de ciclistas em cada time (n > 4)\n");
    printf("\t v - Usado para definir simulacao com velocidades aleatorias\n");
    printf("\t u - Usado para definir simulacao com velocidades uniformes\n");
    printf("\t d - Ativa o modo debug (OPCIONAL)\n\n");
}

void msleep(int ms) {
    usleep(ms * 1000);
} 

float diff_time_s (Timer finish, Timer start) {
    float elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    return elapsed;
}
 
void get_time(Timer *t) {
     clock_gettime(CLOCK_MONOTONIC, t);
}

int randmax(int max) {
    /* Gera um numero aleatorio de o a max */
    return rand() % max;
}