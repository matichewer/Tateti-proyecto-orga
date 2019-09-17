#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

/**
 Inicializa una lista vacía.
 Una referencia a la lista creada es referenciada en *L.
**/
extern void crear_lista(tLista * l){
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
extern void l_insertar(tLista l, tPosicion p, tElemento e){
    tPosicion aux;
    if (l==NULL || p==NULL)
        exit(LST_POSICION_INVALIDA);
    aux = (tPosicion) malloc(sizeof(struct celda));
    if ((aux)==NULL) exit(LST_ERROR_MEMORIA);
    aux->elemento=e;
    aux->siguiente=p->siguiente;
    p->siguiente=aux;
}

/**
 Elimina la celda P de L. El elemento almacenado en la posición P es eliminado mediante la función fEliminar parametrizada.
 Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/
extern void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento)){
    tPosicion aux = (tPosicion) malloc(sizeof(struct celda));
    if ((aux)==NULL) exit(LST_ERROR_MEMORIA);

    if(p==l_fin(l))
        exit(LST_POSICION_INVALIDA);

    aux = (p->siguiente)->siguiente;
    fEliminar((p->siguiente)->elemento);
    free(p->siguiente);
    p->siguiente=aux;
}

/**
 Destruye la lista L, elimininando cada una de sus celdas. Los elementos almacenados en las celdas son eliminados mediante la función fEliminar parametrizada.
**/
extern void l_destruir(tLista * l, void (*fEliminar)(tElemento)){
    int i;
    tPosicion pos = l_siguiente(*l,l_primera(*l));
    tPosicion sig;
    for(i=0; i<l_longitud(*l); i++){
        sig = pos->siguiente;
        fEliminar(pos->elemento);
        free(pos);
        pos = sig;
    }
    free(l_primera(*l));
    free(*l);
}

/**
 Recupera y retorna el elemento en la posición P.
 Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/
extern tElemento l_recuperar(tLista l, tPosicion p){
    if (p==l_fin(l))
        exit(LST_POSICION_INVALIDA);
    return (p->siguiente)->elemento;
}

/**
 Recupera y retorna la primera posición de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
extern tPosicion l_primera(tLista l){
    return (*l).siguiente;
}

/**
 Recupera y retorna la posición siguiente a P en L.
 Si P es fin(L), finaliza indicando LST_NO_EXISTE_SIGUIENTE.
**/
extern tPosicion l_siguiente(tLista l, tPosicion p){
    if (p==l_fin(l))
        exit(LST_NO_EXISTE_SIGUIENTE);

    return p->siguiente;
}

/**
 Recupera y retorna la posición anterior a P en L.
 Si P es primera(L), finaliza indicando LST_NO_EXISTE_ANTERIOR.
**/
extern tPosicion l_anterior(tLista l, tPosicion p){
    if (p==l_primera(l))
        exit(LST_NO_EXISTE_ANTERIOR);
    tPosicion aux;
    aux= (tPosicion)malloc(sizeof(struct celda));
    if ((aux)==NULL) exit(LST_ERROR_MEMORIA);
    aux=l_primera(l);
    int encontre=0;
    while(aux->siguiente!=p && encontre==0){
        if (aux->siguiente==p)
            encontre=1;
        aux->siguiente=aux->siguiente;
    }
    return aux;
}

/**
 Recupera y retorna la última posición de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
extern tPosicion l_ultima(tLista l){
    tPosicion aux;
    aux= (tPosicion)malloc(sizeof(struct celda));
    if ((aux)==NULL) exit(LST_ERROR_MEMORIA);
    aux= l_primera(l);
    while((aux->siguiente->siguiente!=NULL)){
        aux = aux->siguiente;
    }
    return aux;
}

/**
 Recupera y retorna la posición fin de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
extern tPosicion l_fin(tLista l){
    tPosicion aux;
    aux= (tPosicion)malloc(sizeof(struct celda));
    if ((aux)==NULL) exit(LST_ERROR_MEMORIA);

    aux= l_primera(l);
    while((aux->siguiente!=NULL)){
        aux = aux->siguiente;
    }
    return aux;
}

/**
 Retorna la longitud actual de la lista.
**/
extern int l_longitud(tLista l){
    int cont;
    tPosicion temp=l;
    cont=0;
    while(temp!=NULL){
        cont++;
        temp=temp->siguiente;
    }
    return cont;
}
