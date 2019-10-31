#include <stdlib.h>
#include <stdio.h>

#include "lista.h"
#include "arbol.h"
#include "partida.h"
#include "ia.h"




// Barra \ para compu rota que no le anda ese botón


void asignar_modo_de_juego(int * modo){

    // Imprimo opciones
    printf("Ingrese el modo de juego:\n");
    printf("  1. Humano vs Humano\n");
    printf("  2. Humano vs Maquina\n");
    scanf("%i", modo);
    printf("\n\n");

    // Computo el valor
    if(*modo == 1)
        *modo = PART_MODO_USUARIO_VS_USUARIO;
    else
        *modo = PART_MODO_USUARIO_VS_AGENTE_IA;

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
}



//void mostrarTablero(){}


int main(){

    tPartida partida;
    tTablero tablero;
    char nombreJugador1[50];
    char nombreJugador2[50];
    int turno;
    int modo;


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


    asignar_modo_de_juego(&modo);

    asignar_nombre_jugador1(nombreJugador1);
    if(modo == PART_MODO_USUARIO_VS_USUARIO)
        asignar_nombre_jugador2(nombreJugador2);
    else
        nombreJugador2 = "maquina";

    asignar_turno(&turno);


    return 0;
}


