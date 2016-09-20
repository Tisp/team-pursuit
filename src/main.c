#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define V_RANDOM  1
#define V_UNIFORM 2
#define MAX_LAPS 16

typedef struct timespec Timer;

/* Estrutura do tipo PISTA */
typedef struct _lane {
    /* Guarda as posicoes dos ciclistas no treco */
    int *stretch;
} Lane;



void help(const char *program_name) {
    printf("Erro ao rodar o simulador\n");
    printf("Tente: %s d n [u|v]\n", program_name);
}


/* Retonar em segundos a diferenca de dois times */
float diff_time_s (Timer finish, Timer start) {
    float elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    return elapsed;
}

void get_time(Timer *t) {
    clock_gettime(CLOCK_MONOTONIC, t);
}


void sleep_60ms() {
    usleep(60000);
}
/* Variavel global para pista */
Lane *lane;

int main(int argc, char **argv) {


    /* Verifica o numero total de argumentos */
    if(argc != 4) {
        help(argv[0]);
        exit(-1);
    }

    int num_cyclists = atoi(argv[1]); /* Numero de ciclistas */ 
    int lane_distance = atoi(argv[2]); /* Tamanho total da pista */
    int speeds = (strcmp("v", argv[3]) == 0) ? V_RANDOM : V_UNIFORM;
    int i, j = 0;
    Timer t_start, t_finish;

    /* Aloca memoria para pista */
    lane = calloc(lane_distance, sizeof(Lane));

    for(i = 0; i < lane_distance; i++) 
        lane[i].stretch = calloc(num_cyclists * 2, sizeof(int));

    get_time(&t_start);
    while(1) {
            sleep_60ms();
            get_time(&t_finish);
            printf("%lf\n", diff_time_s(t_finish, t_start));
    }


    return 0;
}