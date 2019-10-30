#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

static void destruir_recursivo(tPosicion pos, void (*fEliminar)(tElemento));

/**
 Inicializa una lista vacía.
 Una referencia a la lista creada es referenciada en *L.
**/
void crear_lista(tLista * l){
    (*l) = (tLista) malloc(sizeof(struct celda));
    if ((*l) == NULL)
        exit(LST_ERROR_MEMORIA);
    (*l)->elemento=NULL;
    (*l)->siguiente=NULL;
}


/**
 Inserta el elemento E, en la posición P, en L.
 Con L = A,B,C,D y la posición P direccionando C, luego:
 L' = A,B,E,C,D
**/
void l_insertar(tLista l, tPosicion p, tElemento e){
    tPosicion nuevaPos;
    if (l==NULL || p==NULL)
        exit(LST_POSICION_INVALIDA);
    nuevaPos = (tPosicion) malloc(sizeof(struct celda));
    if (nuevaPos==NULL)
        exit(LST_ERROR_MEMORIA);
    nuevaPos->elemento = e;
    nuevaPos->siguiente = p->siguiente;
    p->siguiente = nuevaPos;
}

/**
 Elimina la celda P de L. El elemento almacenado en la posición P es eliminado mediante la función fEliminar parametrizada.
 Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/
void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento)){
    tPosicion aEliminar;
    // Si P es fin
    if(p->siguiente == NULL)
        exit(LST_POSICION_INVALIDA);
    aEliminar = p->siguiente;
    p->siguiente = aEliminar->siguiente;
    fEliminar(aEliminar->elemento);
    free(aEliminar);
}

static void destruir_recursivo(tPosicion pos, void (*fEliminar)(tElemento)){

    if(pos->siguiente!=NULL)
        destruir_recursivo(pos->siguiente, fEliminar);

    fEliminar(pos->elemento);
    pos->elemento = NULL;
    free(pos);

}

/**
 Destruye la lista L, elimininando cada una de sus celdas. Los elementos almacenados en las celdas son eliminados mediante la función fEliminar parametrizada.
**/
void l_destruir(tLista * l, void (*fEliminar)(tElemento)){
    tLista lista = *l;
    tPosicion pos = lista;

    if(pos->siguiente!=NULL){
        destruir_recursivo(pos->siguiente, fEliminar);
    }
    // Elimina header
    pos->siguiente = NULL;
    pos->elemento = NULL;
    free(pos);

    *l = NULL;
}


/**
 Recupera y retorna el elemento en la posición P.
 Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/
tElemento l_recuperar(tLista l, tPosicion p){
    if (p==NULL || (p->siguiente)==NULL)
        exit(LST_POSICION_INVALIDA);
    return (p->siguiente)->elemento;
}

/**
 Recupera y retorna la primera posición de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_primera(tLista l){
    return l;
}

/**
 Recupera y retorna la posición siguiente a P en L.
 Si P es fin(L), finaliza indicando LST_NO_EXISTE_SIGUIENTE.
**/
tPosicion l_siguiente(tLista l, tPosicion p){
    if (p->siguiente==NULL)
        exit(LST_NO_EXISTE_SIGUIENTE);
    return p->siguiente;
}

/**
 Recupera y retorna la posición anterior a P en L.
 Si P es primera(L), finaliza indicando LST_NO_EXISTE_ANTERIOR.
**/
tPosicion l_anterior(tLista l, tPosicion p){
    tPosicion pos = l;
    if (p==l)
        exit(LST_NO_EXISTE_ANTERIOR);
    while(pos->siguiente!=p)
        pos = pos->siguiente;
    return pos;
}

/**
 Recupera y retorna la última posición de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_ultima(tLista l){
    tPosicion pos = l;
    while((pos->siguiente!=NULL) && (pos->siguiente->siguiente!=NULL))
        pos = pos->siguiente;
    return pos;
}

/**
 Recupera y retorna la posición fin de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_fin(tLista l){
    tPosicion pos = l;
    while(pos->siguiente!=NULL)
        pos = pos->siguiente;
    return pos;
}

/**
 Retorna la longitud actual de la lista.
**/
int l_longitud(tLista l){
    int cont = 0;
    tPosicion pos = l->siguiente;
    while(pos!=NULL){
        cont++;
        pos = pos->siguiente;
    }
    return cont;
}
