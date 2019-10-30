#include "partida.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
Inicializa una nueva partida, indicando:
 - Modo de partida (Usuario vs. Usuario o Usuario vs. Agente IA).
 - Jugador que comienza la partida (Jugador 1, Jugador 2, o elección al azar).
 - Nombre que representa al Jugador 1.
 - Nombre que representa al Jugador 2.
**/
void nueva_partida(tPartida * p, int modo_partida, int comienza, char * j1_nombre, char * j2_nombre){

    int i, j;

    (*p) = (tPartida) malloc(sizeof(struct partida));
    if(*p == NULL) exit(PART_ERROR_MEMORIA);


    // está bien reservar memoria para el tablero así ???
    (*p)->tablero = malloc(sizeof(struct tablero));
    if((*p)->tablero == NULL) exit(PART_ERROR_MEMORIA);


    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
            (*p)->tablero->grilla[i][j] = PART_SIN_MOVIMIENTO;


    (*p)->modo_partida = modo_partida;
    (*p)->turno_de = comienza;
    strcpy((*p)->nombre_jugador_1, j1_nombre);
    strcpy((*p)->nombre_jugador_2, j2_nombre);

}

/**
Actualiza, si corresponde, el estado de la partida considerando que el jugador al que le corresponde jugar, decide hacerlo en la posición indicada (X,Y).
En caso de que el movimiento a dicha posición sea posible, retorna PART_MOVIMIENTO_OK; en caso contrario, retorna PART_MOVIMIENTO_ERROR.
Las posiciones (X,Y) deben corresponderse al rango [0-2]; X representa el número de fila, mientras Y el número de columna.
**/
int nuevo_movimiento(tPartida p, int mov_x, int mov_y);

/**
Finaliza la partida referenciada por P, liberando toda la memoria utilizada.
**/
void finalizar_partida(tPartida * p){

    // Libero espacio del Tablero
    free((*p)->tablero);
    (*p)->tablero = NULL;


    // Libero espacio de la Partida
    free(*p);
    (*p) = NULL;

}