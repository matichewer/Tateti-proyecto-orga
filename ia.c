#include <stdlib.h>

#include "lista.h"
#include "arbol.h"
#include "ia.h"

// Prototipos de funciones auxiliares.
static void ejecutar_min_max(tBusquedaAdversaria b);
static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min);
static int valor_utilidad(tEstado e, int jugador_max);
static tLista estados_sucesores(tEstado e, int ficha_jugador);
static void diferencia_estados(tEstado anterior, tEstado nuevo, int * x, int * y);
static tEstado clonar_estado(tEstado e);

// Funciones extras implementadas al final:
static void fEliminar(tElemento e);
static void fNoEliminar(tElemento e);
static int max(int x, int y);
static int min(int x, int y);


void crear_busqueda_adversaria(tBusquedaAdversaria * b, tPartida p){
    int i, j;
    tEstado estado;

    (*b) = (tBusquedaAdversaria) malloc(sizeof(struct busqueda_adversaria));
    if ((*b) == NULL) exit(IA_ERROR_MEMORIA);

    estado = (tEstado) malloc(sizeof(struct estado));
    if (estado == NULL) exit(IA_ERROR_MEMORIA);

    // Se clona el estado del tablero de la partida, al estado inicial de la búsqueda adversaria.
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            estado->grilla[i][j] = p->tablero->grilla[i][j];
        }
    }

	// Se asume que el estado de la partida es PART_EN_JUEGO por lo que, la utilidad del estado
	// inicialmente es IA_NO_TERMINO
    estado->utilidad = IA_NO_TERMINO;

    // Inicializa los valores que representarán a los jugadores MAX y MIN respectivamente.
    (*b)->jugador_max = p->turno_de;
    (*b)->jugador_min = (p->turno_de == PART_JUGADOR_1) ? PART_JUGADOR_2 : PART_JUGADOR_1;

    // Inicializa un árbol para la búsqueda adversaria inicialmente vacío.
    crear_arbol(&((*b)->arbol_busqueda));

    // Inicializa la raíz del árbol de búsqueda con el estado del tablero T.
    crear_raiz((*b)->arbol_busqueda, estado);

    // Ejecuta algoritmo Min-Max con podas Alpha-Beta.
    ejecutar_min_max((*b));
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
*/
void proximo_movimiento(tBusquedaAdversaria b, int * x, int * y){

    tEstado estadoPadre, estadoActual;
    tNodo nodoActual, nodoMejorSucesor;
    tLista listaSucesores;
    tPosicion posActual, posFin;
    int mejorValor;


    // Obtengo el estado actual y su lista de sucesores
    estadoPadre = a_recuperar(b->arbol_busqueda, a_raiz(b->arbol_busqueda));
    listaSucesores = a_hijos(b->arbol_busqueda, a_raiz(b->arbol_busqueda));
    posActual = l_primera(listaSucesores);
    posFin = l_fin(listaSucesores);
    mejorValor = IA_INFINITO_NEG;


    while(posActual != posFin){
        nodoActual = l_recuperar(listaSucesores, posActual);
        estadoActual =  a_recuperar(b->arbol_busqueda, nodoActual);
        if(mejorValor < estadoActual->utilidad){
            nodoMejorSucesor = nodoActual;
            mejorValor = estadoActual->utilidad;
        }
        posActual = l_siguiente(listaSucesores, posActual);
    }

    estadoActual = a_recuperar(b->arbol_busqueda, nodoMejorSucesor);
    diferencia_estados(estadoPadre, estadoActual, x, y);
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
**/
void destruir_busqueda_adversaria(tBusquedaAdversaria * b){
    a_destruir(&((*b)->arbol_busqueda), &fEliminar);
    free(*b);
    (*b) = NULL;
}

// ===============================================================================================================
// FUNCIONES Y PROCEDEMIENTOS AUXILIARES
// ===============================================================================================================

/**
Ordena la ejecución del algoritmo Min-Max para la generación del árbol de búsqueda adversaria, considerando como
estado inicial el estado de la partida almacenado en el árbol almacenado en B.
**/
static void ejecutar_min_max(tBusquedaAdversaria b){
    tArbol a = b->arbol_busqueda;
    tNodo r = a_raiz(a);
    int jugador_max = b->jugador_max;
    int jugador_min = b->jugador_min;

    printf("IA.ejecutar_min_max\n");
    crear_sucesores_min_max(a, r, 1, IA_INFINITO_NEG, IA_INFINITO_POS, jugador_max, jugador_min);
    printf("fin ejecutar min max\n");
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
Implementa la estrategia del algoritmo Min-Max con podas Alpha-Beta, a partir del estado almacenado en N.
- A referencia al árbol de búsqueda adversaria.
- N referencia al nodo a partir del cual se construye el subárbol de búsqueda adversaria.
- ES_MAX indica si N representa un nodo MAX en el árbol de búsqueda adversaria.
- ALPHA y BETA indican sendos valores correspondientes a los nodos ancestros a N en el árbol de búsqueda A.
- JUGADOR_MAX y JUGADOR_MIN indican las fichas con las que juegan los respectivos jugadores.
**/
static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min){

    tEstado estadoActual;
    int mejorValorSucesores;
    tLista listaSucesores;
    tPosicion posActual, posFin;
    tEstado estadoSucesor;
    tNodo nodoInsertado;

    estadoActual = n->elemento;
    estadoActual->utilidad = valor_utilidad(estadoActual, jugador_max);

    if(estadoActual->utilidad == IA_NO_TERMINO){

        if(es_max){
            mejorValorSucesores = IA_INFINITO_NEG;
            listaSucesores = estados_sucesores(estadoActual, jugador_max);
            posActual = l_primera(listaSucesores);
            posFin = l_fin(listaSucesores);

            while( beta<alpha && posActual!=posFin){
                estadoSucesor = (tEstado) l_recuperar(listaSucesores, posActual);
                nodoInsertado = a_insertar(a, n, NULL, estadoSucesor);
                crear_sucesores_min_max(a, nodoInsertado, 0, alpha, beta, jugador_max, jugador_min);
                mejorValorSucesores = max( mejorValorSucesores, estadoSucesor->utilidad);
                alpha = max(alpha, mejorValorSucesores);
                posActual = l_siguiente(listaSucesores, posActual);
            }
            estadoActual->utilidad = mejorValorSucesores;

        } else {
            mejorValorSucesores = IA_INFINITO_POS;
            listaSucesores = estados_sucesores(estadoActual, jugador_min);
            posActual = l_primera(listaSucesores);
            posFin = l_fin(listaSucesores);

            while(beta>alpha && posActual!=posFin){
                estadoSucesor = l_recuperar(listaSucesores, posActual);
                nodoInsertado = a_insertar(a, n, NULL, estadoSucesor);
                crear_sucesores_min_max(a, nodoInsertado, 1, alpha, beta, jugador_max, jugador_min);
                mejorValorSucesores = min(mejorValorSucesores, estadoSucesor->utilidad);
                //beta = min(beta, mejorValorSucesores);
                alpha = min(alpha, mejorValorSucesores);
                posActual = l_siguiente(listaSucesores, posActual);
            }
            estadoActual->utilidad = mejorValorSucesores;
        }

        // Eliminamos estados que no fueron utilizados
        while(posActual!=posFin)
            l_eliminar(listaSucesores, l_ultima(listaSucesores), &fEliminar);

        // Se destruye la lista sin eliminar los estados que sí usamos.
        l_destruir(&listaSucesores, &fNoEliminar);
    }
}



/**
>>>>>  A IMPLEMENTAR   <<<<<
Computa el valor de utilidad correspondiente al estado E, y la ficha correspondiente al JUGADOR_MAX, retornado:
- IA_GANA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX ganó la partida.
- IA_EMPATA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX empató la partida.
- IA_PIERDE_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX perdió la partida.
- IA_NO_TERMINO en caso contrario.
**/
static int valor_utilidad(tEstado e, int jugador_max){
    int i, j;
    int toReturn = IA_EMPATA_MAX;

    // Primero analizo todas las combinaciones posibles estando parado en 0,0
    if(e->grilla[0][0]==e->grilla[0][1] && e->grilla[0][0]==e->grilla[0][2] && e->grilla[0][0]!=PART_SIN_MOVIMIENTO)
        if(e->grilla[0][0]==jugador_max)
            toReturn = IA_GANA_MAX;
        else
            toReturn = IA_PIERDE_MAX;
    else
        if(e->grilla[0][0]==e->grilla[1][0] && e->grilla[0][0]==e->grilla[2][0] && e->grilla[0][0]!=PART_SIN_MOVIMIENTO)
            if(e->grilla[0][0]==jugador_max)
                toReturn = IA_GANA_MAX;
            else
                toReturn = IA_PIERDE_MAX;
        else
            if(e->grilla[0][0]==e->grilla[1][1] && e->grilla[0][0]==e->grilla[2][2] && e->grilla[0][0]!=PART_SIN_MOVIMIENTO)
                if(e->grilla[0][0]==jugador_max)
                    toReturn = IA_GANA_MAX;
                else
                    toReturn = IA_PIERDE_MAX;
            else
                // Luego analizo todas las combinaciones posibles estando parado en 1,1
                if(e->grilla[1][1]==e->grilla[1][0] && e->grilla[1][1]==e->grilla[1][2] && e->grilla[1][1]!=PART_SIN_MOVIMIENTO)
                    if(e->grilla[1][1]==jugador_max)
                        toReturn = IA_GANA_MAX;
                    else
                        toReturn = IA_PIERDE_MAX;
                else
                    if(e->grilla[1][1]==e->grilla[0][1] && e->grilla[1][1]==e->grilla[2][1] && e->grilla[1][1]!=PART_SIN_MOVIMIENTO)
                        if(e->grilla[1][1]==jugador_max)
                            toReturn = IA_GANA_MAX;
                        else
                            toReturn = IA_PIERDE_MAX;
                    else
                        if(e->grilla[1][1]==e->grilla[0][2] && e->grilla[1][1]==e->grilla[2][0] && e->grilla[1][1]!=PART_SIN_MOVIMIENTO)
                            if(e->grilla[1][1]==jugador_max)
                                toReturn = IA_GANA_MAX;
                            else
                                toReturn = IA_PIERDE_MAX;
                        else
                            // Luego analizo todas las combinaciones posibles estando parado en 2,2
                            if(e->grilla[2][2]==e->grilla[1][2] && e->grilla[2][2]==e->grilla[0][2] && e->grilla[2][2]!=PART_SIN_MOVIMIENTO)
                                if(e->grilla[2][2]==jugador_max)
                                    toReturn = IA_GANA_MAX;
                                else
                                    toReturn = IA_PIERDE_MAX;
                            else
                                if(e->grilla[2][2]==e->grilla[2][1] && e->grilla[2][2]==e->grilla[2][0] && e->grilla[2][2]!=PART_SIN_MOVIMIENTO)
                                    if(e->grilla[2][2]==jugador_max)
                                        toReturn = IA_GANA_MAX;
                                    else
                                        toReturn = IA_PIERDE_MAX;
                                else
                                    // Reviso si la partida aun le quedan jugadas
                                    for(i=0; i<3; i++)
                                        for(j=0; j<3; j++)
                                            if(e->grilla[i][j]==PART_SIN_MOVIMIENTO)
                                                toReturn = IA_NO_TERMINO;

    return toReturn;
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
Computa y retorna una lista con aquellos estados que representan estados sucesores al estado E.
Un estado sucesor corresponde a la clonación del estado E, junto con la incorporación de un nuevo movimiento
realizado por el jugador cuya ficha es FICHA_JUGADOR por sobre una posición que se encuentra libre en el estado E.
La lista de estados sucesores se debe ordenar de forma aleatoria, de forma tal que una doble invocación de la función
estados_sucesores(estado, ficha) retornaría dos listas L1 y L2 tal que:
- L1 y L2 tienen exactamente los mismos estados sucesores de ESTADO a partir de jugar FICHA.
- El orden de los estado en L1 posiblemente sea diferente al orden de los estados en L2.
**/
static tLista estados_sucesores(tEstado e, int ficha_jugador){

    int i, j;
    tEstado toAdd;
    tLista toReturn;

    crear_lista(&toReturn);

    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
            if(e->grilla[i][j] == PART_SIN_MOVIMIENTO){
                toAdd = clonar_estado(e);
                toAdd->grilla[i][j] = ficha_jugador;
                if(rand()%2)
                    l_insertar(toReturn, l_primera(toReturn), toAdd);
                else
                    l_insertar(toReturn, l_fin(toReturn), toAdd);
            }
    return toReturn;
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
Inicializa y retorna un nuevo estado que resulta de la clonación del estado E.
Para esto copia en el estado a retornar los valores actuales de la grilla del estado E, como su valor
de utilidad.
**/
static tEstado clonar_estado(tEstado e){
    int i, j;
    tEstado toReturn;

    toReturn = (tEstado) malloc(sizeof(struct estado));
    if (toReturn == NULL) exit(IA_ERROR_MEMORIA);

    toReturn->utilidad = e->utilidad;
    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
            toReturn->grilla[i][j] = e->grilla[i][j];

    return toReturn;
}

/**
Computa la diferencia existente entre dos estados.
Se asume que entre ambos existe sólo una posición en el que la ficha del estado anterior y nuevo difiere.
La posición en la que los estados difiere, es retornada en los parámetros *X e *Y.
**/
static void diferencia_estados(tEstado anterior, tEstado nuevo, int * x, int * y){
    int i,j, hallado = 0;
    for(i=0; i<3 && !hallado; i++){
        for(j=0; j<3 && !hallado; j++){
            if (anterior->grilla[i][j] != nuevo->grilla[i][j]){
                *x = i;
                *y = j;
                hallado = 1;
            }
        }
    }
}


// FUNCIONES EXTRAS:


/**
Elimina el elemento pasado por parámetro y libera la memoria.
**/
void fEliminar(tElemento e){
    free(e);
    e = NULL;
}

/**
Retorna el máximo valor entre los dos parámetros recibidos.
**/
static int max(int x, int y){
    return x>y ? x : y;
}

/**
Retorna el mínimo valor entre los dos parámetros recibidos.
**/
static int min(int x, int y){
    return x<y ? x : y;
}

/**
No elimina el estado pasado por parámetro.
**/
static void fNoEliminar(tElemento e){}

