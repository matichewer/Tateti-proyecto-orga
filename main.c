#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lista.h"
#include "arbol.h"
#include "partida.h"
#include "ia.h"


void asignar_modo_de_juego(int * modo){
    // Imprimo opciones
    printf("Ingrese el modo de juego:\n");
    printf("  1. Humano vs Humano\n");
    printf("  2. Humano vs Maquina\n");
    scanf("%i", modo);
    printf("\n\n");

    // Computo el valor
    if((*modo) == 1)
        (*modo) = PART_MODO_USUARIO_VS_USUARIO;
    else
        (*modo) = PART_MODO_USUARIO_VS_AGENTE_IA;
}

void asignar_turno(int * turno, char * nombreJugador1, char * nombreJugador2){
    printf("Ingrese quien comienza primero:\n");
    printf(" 1. \033[0;31m%s\033[0m\n", nombreJugador1);
    printf(" 2. \033[0;32m%s\033[0m\n", nombreJugador2);
    printf(" 3. Al azar\n");
    scanf("%i", turno);
    printf("\n");

    if((*turno) == 1)
        (*turno) = PART_JUGADOR_1;
    else
        if((*turno) == 2)
            (*turno) = PART_JUGADOR_2;
        else
            (*turno) = PART_JUGADOR_RANDOM;
}


void mostrar_tablero(tTablero tablero){
    int i, j;
    char ficha[8];
    printf("\n-------------\n");
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            if(tablero->grilla[i][j] == PART_JUGADOR_1)
                strcpy(ficha, "X");
            else if(tablero->grilla[i][j] == PART_JUGADOR_2)
                    strcpy(ficha, "O");
                else{
                    if(i==0 && j==0)
                        strcpy(ficha, "1");
                    else if(i==0 && j==1)
                        strcpy(ficha, "2");
                        else if(i==0 && j==2)
                            strcpy(ficha, "3");
                            else if(i==1 && j==0)
                                strcpy(ficha, "4");
                                else if(i==1 && j==1)
                                    strcpy(ficha, "5");
                                    else if(i==1 && j==2)
                                        strcpy(ficha, "6");
                                        else if(i==2 && j==0)
                                            strcpy(ficha, "7");
                                            else if(i==2 && j==1)
                                                strcpy(ficha, "8");
                                                else if(i==2 && j==2)
                                                    strcpy(ficha, "9");
                }

            if(strcmp(ficha, "X")==0){  // Seteo color rojo para las fichas X
                if(j==1)
                    printf("\033[1;31m %s \033[0m", ficha);
                else
                    printf("|\033[1;31m %s \033[0m|", ficha);
                //printf("\033[0m");
            } else if(strcmp(ficha, "O")==0){   // Seteo color verde para las fichas O
                    if(j==1)
                        printf("\033[1;32m %s \033[0m", ficha);
                    else
                        printf("|\033[1;32m %s \033[0m|", ficha);
                } else
                    if(j==1)
                        printf(" %s ", ficha);
                    else
                        printf("| %s |", ficha);
        }
        printf("\n-------------\n");
    }
    printf("\n");
}



int main(){

    // Declaro variables.
    tPartida partida;
    tTablero tablero;
    tBusquedaAdversaria busquedaAdversaria;
    char nombreJugador1[50];
    char nombreJugador2[50];
    int turno, modo;
    int estadoDePartida, opcionValida;
    int posFicha, fila, columna;


    // Inicializo y reservo memoria para las variables.
    partida = (tPartida) malloc(sizeof(struct partida));
    if(partida == NULL) {
        printf("El juego no pudo ser cargado. Memoria insuficiente.");
        exit(PART_ERROR_MEMORIA);
    }

    tablero = (tTablero) malloc(sizeof(struct tablero));
    if(tablero == NULL) {
        printf("El juego no pudo ser cargado. Memoria insuficiente.");
        exit(PART_ERROR_MEMORIA);
    }


    // Asigno modo de juego.
    asignar_modo_de_juego(&modo);


    // Asigno nombre de jugadores.
    printf("Ingrese el nombre del \033[0;31mJugador 1\033[0m: ");
    scanf("%s", nombreJugador1);
    if(modo == PART_MODO_USUARIO_VS_USUARIO){
        printf("Ingrese el nombre del \033[0;32mJugador 2\033[0m: ");
        scanf("%s", nombreJugador2);
    } else
        strcpy(nombreJugador2, "Maquina");
    printf("\n\n");


    // Asigno quien empieza.
    asignar_turno(&turno, nombreJugador1, nombreJugador2);


    // Creo nueva partida.
    nueva_partida(&partida, modo, turno, nombreJugador1, nombreJugador2);
    tablero = partida->tablero;
    mostrar_tablero(tablero);


    // Inicio una partida Usuario vs Usuario
    if(modo == PART_MODO_USUARIO_VS_USUARIO){
        while(partida->estado == PART_EN_JUEGO){

            if(partida->turno_de == PART_JUGADOR_1)
                printf("\033[0;31m%s\033[0m indique dónde quiere poner su ficha (numero entre 1 y 9).\n", nombreJugador1);
            else
                printf("\033[0;32m%s\033[0m indique dónde quiere poner su ficha (numero entre 1 y 9).\n", nombreJugador2);

            opcionValida = 0;
            while(!opcionValida){
                scanf("%i", &posFicha);
                if(posFicha<1 || posFicha>9)
                    printf("Error: debes elegir una posicion entre 1 y 9.\n");
                else{
                    switch(posFicha){
                        case 1: fila = 0; columna = 0; break;
                        case 2: fila = 0; columna = 1; break;
                        case 3: fila = 0; columna = 2; break;
                        case 4: fila = 1; columna = 0; break;
                        case 5: fila = 1; columna = 1; break;
                        case 6: fila = 1; columna = 2; break;
                        case 7: fila = 2; columna = 0; break;
                        case 8: fila = 2; columna = 1; break;
                        case 9: fila = 2; columna = 2; break;
                    }
                estadoDePartida = nuevo_movimiento(partida, fila, columna);
                if(estadoDePartida == PART_MOVIMIENTO_ERROR)
                    printf("Error: debes elegir un casillero vacío.\n");
                else
                    opcionValida = 1;
                }
            }
            mostrar_tablero(tablero);

        }
    }
    // Inicio una partida Usuario vs IA
    else
        if(modo == PART_MODO_USUARIO_VS_AGENTE_IA){
            while(partida->estado == PART_EN_JUEGO){

                if(partida->turno_de == PART_JUGADOR_1){
                    printf("\033[0;31m%s\033[0m indique dónde quiere poner su ficha (numero entre 1 y 9).\n", nombreJugador1);
                    opcionValida = 0;
                    while(!opcionValida){
                        scanf("%i", &posFicha);
                        if(posFicha<1 || posFicha>9)
                            printf("Error: debes elegir una posicion entre 1 y 9.\n");
                        else {
                            switch(posFicha){
                                case 1: fila = 0; columna = 0; break;
                                case 2: fila = 0; columna = 1; break;
                                case 3: fila = 0; columna = 2; break;
                                case 4: fila = 1; columna = 0; break;
                                case 5: fila = 1; columna = 1; break;
                                case 6: fila = 1; columna = 2; break;
                                case 7: fila = 2; columna = 0; break;
                                case 8: fila = 2; columna = 1; break;
                                case 9: fila = 2; columna = 2; break;
                            }
                            estadoDePartida = nuevo_movimiento(partida, fila, columna);
                            if(estadoDePartida == PART_MOVIMIENTO_ERROR)
                                printf("Error: debes elegir un casillero vacío.\n");
                            else
                                opcionValida = 1;
                        }
                    }
                } else {
                    if(partida->turno_de==PART_JUGADOR_2 && (estadoDePartida==PART_MOVIMIENTO_OK || partida->estado==PART_EN_JUEGO)){
                        printf("Turno de %s\n", partida->nombre_jugador_2);
                        crear_busqueda_adversaria(&busquedaAdversaria, partida);
                        proximo_movimiento(busquedaAdversaria, &fila, &columna);
                        nuevo_movimiento(partida,fila,columna);
                        destruir_busqueda_adversaria(&busquedaAdversaria);
                    }
                }
            mostrar_tablero(tablero);
        }
    }


    if(partida->estado == PART_GANA_JUGADOR_1)
        printf("\033[0;31mHa ganado %s\033[0m\n\n", nombreJugador1);
    else if(partida->estado == PART_GANA_JUGADOR_2)
            printf("\033[0;32mHa ganado %s\033[0m\n\n",nombreJugador2);
        else if(partida->estado  == PART_EMPATE)
                printf("\033[0;36mLa partida ha terminado en empate.\033[0m\n\n");

    finalizar_partida(&partida);
    return 0;
}


