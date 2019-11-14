#include <stdlib.h>
#include <stdio.h>

#include "lista.h"
#include "arbol.h"
#include "partida.h"
#include "ia.h"

//cambio Juani
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

    if(*turno == 1)
        *turno = PART_JUGADOR_1;
    else
        if(*turno == 2)
            *turno = PART_JUGADOR_2;
        else
            *turno = PART_JUGADOR_RANDOM;
}

void mostrar_ficha_de_primer_y_tercer_columna(tTablero tablero, int fila, int columna){

    if(tablero->grilla[fila][columna] == PART_SIN_MOVIMIENTO)
        printf("    ");

    if(tablero->grilla[fila][columna] == PART_JUGADOR_1)
        printf("  X  ");

    if(tablero->grilla[fila][columna] == PART_JUGADOR_2)
        printf("  O  ");

}

void mostrar_ficha_de_columna_central(tTablero tablero, int fila, int columna){

    if(tablero->grilla[fila][columna] == PART_SIN_MOVIMIENTO)
        printf("|   |");

    if(tablero->grilla[fila][columna] == PART_JUGADOR_1)
        printf("| X |");

    if(tablero->grilla[fila][columna] == PART_JUGADOR_2)
        printf("| O |");

}

void mostrar_tablero(tTablero tablero){
    printf("TABLERO:\n\n");
    mostrar_ficha_de_primer_y_tercer_columna(tablero, 0, 0);
    mostrar_ficha_de_columna_central(tablero, 0, 1);
    mostrar_ficha_de_primer_y_tercer_columna(tablero, 0, 2);
    printf("\n ---|---|--- \n");
    mostrar_ficha_de_primer_y_tercer_columna(tablero, 1, 0);
    mostrar_ficha_de_columna_central(tablero, 1, 1);
    mostrar_ficha_de_primer_y_tercer_columna(tablero, 1, 2);
    printf("\n ---|---|--- \n");
    mostrar_ficha_de_primer_y_tercer_columna(tablero, 2, 0);
    mostrar_ficha_de_columna_central(tablero, 2, 1);
    mostrar_ficha_de_primer_y_tercer_columna(tablero, 2, 2);
    printf("\n");
}


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
    else{
        nombreJugador2[0] = 'M';  // por qué letra por letra ????
        nombreJugador2[1] = 'a';
        nombreJugador2[2] = 'q';
        nombreJugador2[3] = 'u';
        nombreJugador2[4] = 'i';
        nombreJugador2[5] = 'n';
        nombreJugador2[6] = 'a';
    }

    asignar_turno(&turno);

    nueva_partida(&partida, modo, turno, nombreJugador1, nombreJugador2);
    tablero = partida->tablero;
    mostrar_tablero(tablero);

    /*
    if(modo == PART_MODO_USUARIO_VS_USUARIO)
        iniciar_modo_usuario_vs_usuario();    // falta crear e implementar ésta función
    else
        if(modo == PART_MODO_USUARIO_VS_AGENTE_IA)
            iniciar_modo_usuario_vs_ia();  // falta crear e implementar ésta función
*/

    return 0;
}


