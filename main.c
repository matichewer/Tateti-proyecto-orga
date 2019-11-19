#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "lista.h"
#include "arbol.h"
#include "partida.h"
#include "ia.h"

 /*
 -------------------------------------------------------------------------------------------------------------------------------
 INTERFAZ CON COLORES
 -------------------------------------------------------------------------------------------------------------------------------
 */

void asignar_modo_de_juego(int * modo){
    int opcionValida = 0;

    // Imprimo opciones
    printf("Ingrese el modo de juego:\n");
    printf("  1. Humano vs Humano\n");
    printf("  2. Humano vs Maquina\n");
    printf("  3. Maquina vs Maquina\n");

    // Computo el valor
    while(!opcionValida){
        scanf("%i", modo);
        if((*modo) == 1){
            (*modo) = PART_MODO_USUARIO_VS_USUARIO;
            opcionValida = 1;
        } else
            if((*modo) == 2){
                (*modo) = PART_MODO_USUARIO_VS_AGENTE_IA;
                opcionValida = 1;
            } else
                if((*modo) == 3){
                    (*modo) = PART_MODO_AGENTE_IA_VS_AGENTE_IA;
                    opcionValida = 1;
                } else
                    printf("Error: el numero elegido debe ser entre 1 y 3. Intente nuevamente.\n");
    }
    printf("\n\n");
}

void asignar_turno(int * turno, char * nombreJugador1, char * nombreJugador2){
    int opcionValida = 0;

    printf("Ingrese quien comienza primero:\n");
    printf(" 1. \033[0;31m%s\033[0m\n", nombreJugador1);
    printf(" 2. \033[0;32m%s\033[0m\n", nombreJugador2);
    printf(" 3. Al azar\n");

    while(!opcionValida){
        scanf("%i", turno);
        if((*turno) == 1){
            (*turno) = PART_JUGADOR_1;
            opcionValida = 1;
        } else
            if((*turno) == 2){
                (*turno) = PART_JUGADOR_2;
                opcionValida = 1;
            } else
                if((*turno) == 3){
                    (*turno) = PART_JUGADOR_RANDOM;
                    opcionValida = 1;
                }
                else
                    printf("Error: el numero elegido debe ser entre 1 y 3. Intente nuevamente.\n");
    }
    printf("\n");
}


void mostrar_tablero(tTablero tablero){
    int i, j;
    char ficha[8];
    printf("\n-------------\n");

    // Obtengo la ficha de cada casillero
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

            // Seteo color ROJO para las fichas X
            if(strcmp(ficha, "X")==0)
                if(j==1)
                    printf("\033[1;31m %s \033[0m", ficha);  // fichas sin marco
                else
                    printf("|\033[1;31m %s \033[0m|", ficha); // ficha con marco de tablero
            else
                // Seteo color VERDE para las fichas O
                if(strcmp(ficha, "O")==0)
                    if(j==1)
                        printf("\033[1;32m %s \033[0m", ficha); // fichas sin marco
                    else
                        printf("|\033[1;32m %s \033[0m|", ficha); // ficha con marco de tablero
                else
                    // Sin color para los numeros del 1 al 9
                    if(j==1)
                        printf(" %s ", ficha); // fichas sin marco
                    else
                        printf("| %s |", ficha); // ficha con marco de tablero
        }
        printf("\n-------------\n");
    }
    printf("\n");
}

// Funcion para poner delay en el programa para el modo IA vs IA
void delay(int milisegundos){
    clock_t inicio = clock();
    while((clock() - inicio) * 1000 / CLOCKS_PER_SEC < milisegundos);
}



int main(){

    tPartida partida;
    tTablero tablero;
    tBusquedaAdversaria busquedaAdversaria;
    char nombreJugador1[50];
    char nombreJugador2[50];
    int turno, modo;
    int estadoDePartida, opcionValida;
    int posFicha, fila, columna;
    int enter;


    // Bienvenida
    printf("\nBienvenido al videojuego TA-TE-TI !!!\n\n\n\n");
    printf("================================= ATENCION ================================= \n\n");
    printf("El juego tiene colores, es probable que solamente funcione en Linux.\n");
    printf("Para ejecutar el juego en Windows, debera quitar todos los colores del juego,\n");
    printf("o bien, lograr que la consola de Windows sea compatible con los colores.\n\n");
    printf("Disculpe las molestias.\n\n");
    printf("============================================================================\n\n\n\n");



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
    if(modo == PART_MODO_USUARIO_VS_USUARIO){
        printf("Ingrese el nombre del \033[0;31mJugador 1\033[0m: ");
        scanf("%s", nombreJugador1);
        printf("Ingrese el nombre del \033[0;32mJugador 2\033[0m: ");
        scanf("%s", nombreJugador2);
    } else{
        if(modo == PART_MODO_USUARIO_VS_AGENTE_IA){
            printf("Ingrese el nombre del \033[0;31mJugador 1\033[0m: ");
            scanf("%s", nombreJugador1);
            strcpy(nombreJugador2, "Maquina");
        } else{
            if(modo == PART_MODO_AGENTE_IA_VS_AGENTE_IA){
                strcpy(nombreJugador1, "Maquina 1");
                strcpy(nombreJugador2, "Maquina 2");
            }
        }
    }
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
                printf("\033[0;31m%s\033[0m indique donde quiere poner su ficha (numero entre 1 y 9).\n", nombreJugador1);
            else
                printf("\033[0;32m%s\033[0m indique donde quiere poner su ficha (numero entre 1 y 9).\n", nombreJugador2);

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
                    printf("Error: debes elegir un casillero vacio.\n");
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
                    printf("\033[0;31m%s\033[0m indique donde quiere poner su ficha (numero entre 1 y 9).\n", nombreJugador1);
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
                                printf("Error: debes elegir un casillero vacio.\n");
                            else
                                opcionValida = 1;
                        }
                    }
                } else {
                    if(partida->turno_de==PART_JUGADOR_2 && (estadoDePartida==PART_MOVIMIENTO_OK || partida->estado==PART_EN_JUEGO)){
                        printf("Turno de \033[0;32m%s\033[0m\n", partida->nombre_jugador_2);
                        crear_busqueda_adversaria(&busquedaAdversaria, partida);
                        proximo_movimiento(busquedaAdversaria, &fila, &columna);
                        nuevo_movimiento(partida,fila,columna);
                        destruir_busqueda_adversaria(&busquedaAdversaria);
                    }
                }
            mostrar_tablero(tablero);
        }
    }
    else{
        // Inicio una partida IA vs IA
        while(partida->estado == PART_EN_JUEGO){
            delay(1200);
            if(partida->turno_de == PART_JUGADOR_1)
                printf("Turno de \033[0;31m%s\033[0m:\n", nombreJugador1);
            else
                printf("Turno de \033[0;32m%s\033[0m:\n", nombreJugador2);
            crear_busqueda_adversaria(&busquedaAdversaria, partida);
            proximo_movimiento(busquedaAdversaria, &fila, &columna);
            nuevo_movimiento(partida, fila, columna);
            destruir_busqueda_adversaria(&busquedaAdversaria);
            delay(2000);
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





/*
 -------------------------------------------------------------------------------------------------------------------------------
 INTERFAZ SIN COLORES
 -------------------------------------------------------------------------------------------------------------------------------
 */

/*
void asignar_modo_de_juego(int * modo){
    int opcionValida = 0;

    // Imprimo opciones
    printf("Ingrese el modo de juego:\n");
    printf("  1. Humano vs Humano\n");
    printf("  2. Humano vs Maquina\n");
    printf("  3. Maquina vs Maquina\n");

    // Computo el valor
    while(!opcionValida){
        scanf("%i", modo);
        if((*modo) == 1){
            (*modo) = PART_MODO_USUARIO_VS_USUARIO;
            opcionValida = 1;
        } else
            if((*modo) == 2){
                (*modo) = PART_MODO_USUARIO_VS_AGENTE_IA;
                opcionValida = 1;
            } else
                if((*modo) == 3){
                    (*modo) = PART_MODO_AGENTE_IA_VS_AGENTE_IA;
                    opcionValida = 1;
                } else
                    printf("Error: el numero elegido debe ser entre 1 y 3. Intente nuevamente.\n");
    }
    printf("\n\n");
}

void asignar_turno(int * turno, char * nombreJugador1, char * nombreJugador2){
    int opcionValida = 0;

    printf("Ingrese quien comienza primero:\n");
    printf(" 1. %s\n", nombreJugador1);
    printf(" 2. %s\n", nombreJugador2);
    printf(" 3. Al azar\n");

    while(!opcionValida){
        scanf("%i", turno);
        if((*turno) == 1){
            (*turno) = PART_JUGADOR_1;
            opcionValida = 1;
        } else
            if((*turno) == 2){
                (*turno) = PART_JUGADOR_2;
                opcionValida = 1;
            } else
                if((*turno) == 3){
                    (*turno) = PART_JUGADOR_RANDOM;
                    opcionValida = 1;
                }
                else
                    printf("Error: el numero elegido debe ser entre 1 y 3. Intente nuevamente.\n");
    }
    printf("\n");
}


void mostrar_tablero(tTablero tablero){
    int i, j;
    char ficha[8];
    printf("\n-------------\n");

    // Obtengo la ficha de cada casillero
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
            if(j==1)
                printf(" %s ", ficha); // fichas sin marco
            else
                printf("| %s |", ficha); // ficha con marco de tablero
        }
        printf("\n-------------\n");
    }
    printf("\n");
}

// Funcion para poner delay en el programa para el modo IA vs IA
void delay(int milisegundos){
    clock_t inicio = clock();
    while((clock() - inicio) * 1000 / CLOCKS_PER_SEC < milisegundos);
}



int main(){

    tPartida partida;
    tTablero tablero;
    tBusquedaAdversaria busquedaAdversaria;
    char nombreJugador1[50];
    char nombreJugador2[50];
    int turno, modo;
    int estadoDePartida, opcionValida;
    int posFicha, fila, columna;

    printf("\nBienvenido al videojuego TA-TE-TI !!!\n\n\n");

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
    if(modo == PART_MODO_USUARIO_VS_USUARIO){
        printf("Ingrese el nombre del Jugador 1: ");
        scanf("%s", nombreJugador1);
        printf("Ingrese el nombre del Jugador 2: ");
        scanf("%s", nombreJugador2);
    } else{
        if(modo == PART_MODO_USUARIO_VS_AGENTE_IA){
            printf("Ingrese el nombre del Jugador 1: ");
            scanf("%s", nombreJugador1);
            strcpy(nombreJugador2, "Maquina");
        } else{
            if(modo == PART_MODO_AGENTE_IA_VS_AGENTE_IA){
                strcpy(nombreJugador1, "Maquina 1");
                strcpy(nombreJugador2, "Maquina 2");
            }
        }
    }
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
                printf("%s indique donde quiere poner su ficha (numero entre 1 y 9).\n", nombreJugador1);
            else
                printf("%s indique donde quiere poner su ficha (numero entre 1 y 9).\n", nombreJugador2);

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
                    printf("Error: debes elegir un casillero vacio.\n");
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
                    printf("%s indique donde quiere poner su ficha (numero entre 1 y 9).\n", nombreJugador1);
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
                                printf("Error: debes elegir un casillero vacio.\n");
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
    else{
        // Inicio una partida IA vs IA
        while(partida->estado == PART_EN_JUEGO){
            delay(1200);
            if(partida->turno_de == PART_JUGADOR_1)
                printf("Turno de %s:\n", nombreJugador1);
            else
                printf("Turno de %s:\n", nombreJugador2);
            crear_busqueda_adversaria(&busquedaAdversaria, partida);
            proximo_movimiento(busquedaAdversaria, &fila, &columna);
            nuevo_movimiento(partida, fila, columna);
            destruir_busqueda_adversaria(&busquedaAdversaria);
            delay(2000);
            mostrar_tablero(tablero);
        }
    }

    if(partida->estado == PART_GANA_JUGADOR_1)
        printf("Ha ganado %s\n\n", nombreJugador1);
    else if(partida->estado == PART_GANA_JUGADOR_2)
            printf("Ha ganado %s\n\n",nombreJugador2);
        else if(partida->estado  == PART_EMPATE)
                printf("La partida ha terminado en empate.\n\n");

    finalizar_partida(&partida);
    return 0;
}
*/
