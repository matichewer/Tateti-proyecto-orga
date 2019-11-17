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

void asignar_nombre_jugador1(char * nombre){
    printf("Ingrese el nombre del jugador 1: ");
    scanf("%s", nombre);
    printf("\n\n");
}

void asignar_nombre_jugador2(char * nombre){
    printf("Ingrese el nombre del jugador 2: ");
    scanf("%s", nombre);
    printf("\n\n");
}

void asignar_turno(int * turno){
    printf("Ingrese quien comienza primero:\n");
    printf(" 1. Jugador 1\n");
    printf(" 2. Jugador 2\n");
    printf(" 3. Al azar\n");
    scanf("%i",turno);
    printf("\n\n");

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
                else
                    strcpy(ficha, " ");
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
    char nombreJugador1[50];
    char nombreJugador2[50];
    int turno, modo;
    int estadoDePartida, opcionValida;
    int fila, columna;


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
    asignar_nombre_jugador1(nombreJugador1);
    if(modo == PART_MODO_USUARIO_VS_USUARIO)
        asignar_nombre_jugador2(nombreJugador2);
    else
        strcpy(nombreJugador2, "Maquina");


    // Asigno quien empieza.
    asignar_turno(&turno);


    // Creo nueva partida.
    nueva_partida(&partida, modo, turno, nombreJugador1, nombreJugador2);
    tablero = partida->tablero;
    mostrar_tablero(tablero);


    // Inicio una partida Usuario vs Usuario
    if(modo == PART_MODO_USUARIO_VS_USUARIO){
        while(partida->estado == PART_EN_JUEGO){

            if(turno == PART_JUGADOR_1)
                printf("%s indicá tu movimiento (entre 1 y 3 inclusive).\n", nombreJugador1);
            else
                printf("%s indicá tu movimiento (entre 1 y 3 inclusive).\n", nombreJugador2);

            opcionValida = 0;
            while(!opcionValida){
                printf("Fila: ");
                scanf("%i", &fila);
                printf("Columna: ");
                scanf("%i", &columna);
                if(fila<1 || fila>3 || columna<1 || columna>3)
                    printf("Error: debes elegir una fila y una columna entre 1, 2 y 3.\n");
                else
                    opcionValida = 1;
            }

            estadoDePartida = nuevo_movimiento(partida, fila-1, columna-1);
            if(estadoDePartida == PART_MOVIMIENTO_ERROR)
                printf("Error: debes elegir un casillero vacío.\n");
            mostrar_tablero(tablero);
            printf("%i", partida->estado == PART_EN_JUEGO);
        }
    }
    // Inicio una partida Usuario vs IA
    else
        if(modo == PART_MODO_USUARIO_VS_AGENTE_IA){

            // aca hay que implementar el modo HUMANO vs IA

        }





    if(estadoDePartida == PART_GANA_JUGADOR_1)
        printf("¡¡ Ganó %s!!", nombreJugador1);
    else if(estadoDePartida == PART_GANA_JUGADOR_2)
            printf("¡¡ Ganó %s!!",nombreJugador2);
        else if(estadoDePartida  == PART_EMPATE)
                printf("La partida terminó en empate");

    finalizar_partida(&partida);
    return 0;
}


