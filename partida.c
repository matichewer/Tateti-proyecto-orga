#include "partida.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static int estado_de_partida(tTablero t);

/**
Inicializa una nueva partida, indicando:
 - Modo de partida (Usuario vs. Usuario o Usuario vs. Agente IA).
 - Jugador que comienza la partida (Jugador 1, Jugador 2, o elección al azar).
 - Nombre que representa al Jugador 1.
 - Nombre que representa al Jugador 2.
**/
void nueva_partida(tPartida * p, int modo_partida, int comienza, char * j1_nombre, char * j2_nombre){

    int i, j;

    // Reservo memoria para la Partida
    (*p) = (tPartida) malloc(sizeof(struct partida));
    if(*p == NULL) exit(PART_ERROR_MEMORIA);

    // Reservo memoria para el Tablero
    (*p)->tablero = malloc(sizeof(struct tablero));
    if((*p)->tablero == NULL) exit(PART_ERROR_MEMORIA);

    // Seteo el tablero con lugares disponibles
    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
            (*p)->tablero->grilla[i][j] = PART_SIN_MOVIMIENTO;

    // Modo de juego al azar
    if(comienza == PART_JUGADOR_RANDOM){
        if(rand()%100 < 50)
            (*p)->turno_de = PART_JUGADOR_1;
        else
            (*p)->turno_de = PART_JUGADOR_2;
    }

    // Asigno los parámetros
    (*p)->modo_partida = modo_partida;
    (*p)->turno_de = comienza;
    (*p)->estado = PART_EN_JUEGO;
    strcpy((*p)->nombre_jugador_1, j1_nombre);
    strcpy((*p)->nombre_jugador_2, j2_nombre);

}

/**
Actualiza, si corresponde, el estado de la partida considerando que el jugador al que le corresponde jugar, decide hacerlo en la posición indicada (X,Y).
En caso de que el movimiento a dicha posición sea posible, retorna PART_MOVIMIENTO_OK; en caso contrario, retorna PART_MOVIMIENTO_ERROR.
Las posiciones (X,Y) deben corresponderse al rango [0-2]; X representa el número de fila, mientras Y el número de columna.
**/
int nuevo_movimiento(tPartida p, int mov_x, int mov_y){
    int toReturn = PART_MOVIMIENTO_OK;

    // Chequeo que la posicion (X,Y) sea correcta, esté libre para poner una ficha, y que la partida esté en juego
    if( mov_x<0 || mov_x>2 || mov_y<0 || mov_y>2
            || p->tablero->grilla[mov_x][mov_y] != PART_SIN_MOVIMIENTO
            || p->estado != PART_EN_JUEGO){
        toReturn = PART_MOVIMIENTO_ERROR;
    } else {
        // Si es el turno del jugador 1, actualizo el tablero con su ficha y le cedo el turno al jugador 2
        if(p->turno_de == PART_JUGADOR_1){
            p->tablero->grilla[mov_x][mov_y] = PART_JUGADOR_1;
            p->turno_de = PART_JUGADOR_2;
        } else {
            // Si es el turno del jugador 2, actualizo el tablero y le cedo el turno al jugador 1
            if(p->turno_de == PART_JUGADOR_2){
                p->tablero->grilla[mov_x][mov_y] = PART_JUGADOR_2;
                p->turno_de = PART_JUGADOR_1;
            }
        }
            // Actualizo el estado de la partida
        p->estado = estado_de_partida(p->tablero);
    }
    return toReturn;
}

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




// ===============================================================================================================
// FUNCIONES Y PROCEDEMIENTOS AUXILIARES
// ===============================================================================================================


static int estado_de_partida(tTablero t){
    int i, j;
    int toReturn = PART_EMPATE;

    // Primero analizo todas las combinaciones posibles estando parado en 0,0
    if(t->grilla[0][0]==t->grilla[0][1] && t->grilla[0][0]==t->grilla[0][2] && t->grilla[0][0]!=PART_SIN_MOVIMIENTO){
        if(t->grilla[0][0]==PART_JUGADOR_1)
            toReturn = PART_GANA_JUGADOR_1;
        if(t->grilla[0][0]==PART_JUGADOR_2)
            toReturn = PART_GANA_JUGADOR_2;
    } else
        if(t->grilla[0][0]==t->grilla[1][0] && t->grilla[0][0]==t->grilla[2][0] && t->grilla[0][0]!=PART_SIN_MOVIMIENTO){
            if(t->grilla[0][0]==PART_JUGADOR_1)
                toReturn = PART_GANA_JUGADOR_1;
            if(t->grilla[0][0]==PART_JUGADOR_2)
                toReturn = PART_GANA_JUGADOR_2;
        } else
            if(t->grilla[0][0]==t->grilla[1][1] && t->grilla[0][0]==t->grilla[2][2] && t->grilla[0][0]!=PART_SIN_MOVIMIENTO){
                if(t->grilla[0][0]==PART_JUGADOR_1)
                    toReturn = PART_GANA_JUGADOR_1;
                if(t->grilla[0][0]==PART_JUGADOR_2)
                    toReturn = PART_GANA_JUGADOR_2;
            } else
                // Luego analizo todas las combinaciones posibles estando parado en 1,1
                if(t->grilla[1][1]==t->grilla[1][0] && t->grilla[1][1]==t->grilla[1][2] && t->grilla[1][1]!=PART_SIN_MOVIMIENTO){
                    if(t->grilla[1][1]==PART_JUGADOR_1)
                        toReturn = PART_GANA_JUGADOR_1;
                    if(t->grilla[1][1]==PART_JUGADOR_2)
                        toReturn = PART_GANA_JUGADOR_2;
                } else
                    if(t->grilla[1][1]==t->grilla[0][1] && t->grilla[1][1]==t->grilla[2][1] && t->grilla[1][1]!=PART_SIN_MOVIMIENTO){
                        if(t->grilla[1][1]==PART_JUGADOR_1)
                            toReturn = PART_GANA_JUGADOR_1;
                        if(t->grilla[1][1]==PART_JUGADOR_2)
                            toReturn = PART_GANA_JUGADOR_2;
                    } else
                        if(t->grilla[1][1]==t->grilla[0][2] && t->grilla[1][1]==t->grilla[2][0] && t->grilla[1][1]!=PART_SIN_MOVIMIENTO){
                            if(t->grilla[1][1]==PART_JUGADOR_1)
                                toReturn = PART_GANA_JUGADOR_1;
                            if(t->grilla[1][1]==PART_JUGADOR_2)
                                toReturn = PART_GANA_JUGADOR_2;
                        } else
                            // Luego analizo todas las combinaciones posibles estando parado en 2,2
                            if(t->grilla[2][2]==t->grilla[1][2] && t->grilla[2][2]==t->grilla[0][2] && t->grilla[2][2]!=PART_SIN_MOVIMIENTO){
                                if(t->grilla[2][2]==PART_JUGADOR_1)
                                    toReturn = PART_GANA_JUGADOR_1;
                                if(t->grilla[2][2]==PART_JUGADOR_2)
                                    toReturn = PART_GANA_JUGADOR_2;
                            } else
                                if(t->grilla[2][2]==t->grilla[2][1] && t->grilla[2][2]==t->grilla[2][0] && t->grilla[2][2]!=PART_SIN_MOVIMIENTO){
                                    if(t->grilla[2][2]==PART_JUGADOR_1)
                                        toReturn = PART_GANA_JUGADOR_1;
                                    if(t->grilla[2][2]==PART_JUGADOR_2)
                                        toReturn = PART_GANA_JUGADOR_2;
                                }
                                else
                                    // Reviso si la partida aun le quedan jugadas
                                    for(i=0; i<3; i++)
                                        for(j=0; j<3; j++)
                                            if(t->grilla[i][j]==PART_SIN_MOVIMIENTO)
                                                toReturn = PART_EN_JUEGO;
    return toReturn;
}



