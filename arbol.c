#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>


void (*eliminarElementoDelNodo)(tElemento);  // acá se guarda la funcion de a_destruir()
void eliminarNodo(tNodo nodo);

void fEliminarNodoo(tNodo nodo){

}

tPosicion buscarPos(tLista l, tNodo n){
    tPosicion toReturn = l_primera(l);
    tPosicion fin = l_fin(l);

    while( (toReturn!=fin) && (l_recuperar(l,toReturn) != n))
        toReturn=l_siguiente(l,toReturn);

    if(l_recuperar(l,toReturn)==n)
        return toReturn;
    else
        return NULL;
}

/**
Inicializa un árbol vacío.
Una referencia al árbol creado es referenciado en *A.
**/
void crear_arbol(tArbol * a){
    (*a) = (tArbol) malloc(sizeof( struct arbol));
    ((*a)->raiz) = NULL;
    if(*a == NULL)
        exit(ARB_ERROR_MEMORIA);
}

/**
Crea la raíz de A.
Si A no es vacío, finaliza indicando ARB_OPERACION_INVALIDA.
**/
void crear_raiz(tArbol a, tElemento e){
    if(a->raiz != NULL)
        exit(ARB_OPERACION_INVALIDA);

    tNodo nodo_nuevo = (tNodo) malloc(sizeof(struct nodo));
    if(nodo_nuevo == NULL)
        exit(ARB_ERROR_MEMORIA);

    nodo_nuevo->elemento = e;
    nodo_nuevo->padre = NULL;
    crear_lista(&(nodo_nuevo->hijos));
    (a->raiz) = nodo_nuevo;
}

/**
 Inserta y retorna un nuevo nodo en A.
 El nuevo nodo se agrega en A como hijo de NP, hermano izquierdo de NH, y cuyo rótulo es E.
 Si NH es NULL, el nuevo nodo se agrega como último hijo de NP.
 Si NH no corresponde a un nodo hijo de NP, finaliza indicando ARB_POSICION_INVALIDA.
 NP direcciona al nodo padre, mientras NH al nodo hermano derecho del nuevo nodo a insertar.
**/
tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e){
    tPosicion posNH = NULL;
    tLista listaHermanos = np->hijos;

    tNodo nodo_nuevo = malloc(sizeof(struct nodo));
    if(nodo_nuevo == NULL)
        exit(ARB_ERROR_MEMORIA);
    nodo_nuevo->elemento = e;
    nodo_nuevo->padre = np;
    crear_lista(&(nodo_nuevo->hijos));

    if (nh==NULL){
        l_insertar(listaHermanos,l_fin(listaHermanos), nodo_nuevo);
    }
    else{
        if (nh->padre != np)
            exit(ARB_POSICION_INVALIDA);
        posNH = buscarPos(listaHermanos,nh);
        l_insertar(listaHermanos,posNH,nodo_nuevo);
    }
    return nodo_nuevo;
}


/**
 Elimina el nodo N de A.
 El elemento almacenado en el árbol es eliminado mediante la función fEliminar parametrizada.
 Si N es la raíz de A, y tiene un sólo hijo, este pasa a ser la nueva raíz del árbol.
 Si N es la raíz de A, y a su vez tiene más de un hijo, finaliza retornando ARB_OPERACION_INVALIDA.
 Si N no es la raíz de A y tiene hijos, estos pasan a ser hijos del padre de N, en el mismo orden y a partir de la posición que ocupa N en la lista de hijos de su padre.
**/
void a_eliminar(tArbol a, tNodo n, void (*fEliminar)(tElemento)){
    // como chequeo que n es un nodo al arbol a?

    tLista listaHijos=n->hijos;
    int cantHijos= l_longitud(listaHijos);
    if (a->raiz==n){
        if (cantHijos==1){
            tNodo nodo = l_recuperar(listaHijos, l_primera(listaHijos));
            nodo->padre = NULL;
            fEliminar(a->raiz->elemento);
            a->raiz = l_recuperar(listaHijos, l_primera(listaHijos));
        }
        else{
            exit(ARB_OPERACION_INVALIDA);
        }
    }
    else{
        //caso general
        //l_insertar inserta izquierda de la posicion dada
        tLista listaPadre= (n->padre)->hijos;
        tPosicion posN = buscarPos(listaPadre,n);
        tPosicion posInsertar= posN->siguiente;
        int i;
        tPosicion pos= l_primera(listaHijos);
        for(i=0;i<cantHijos;i++){
            tNodo nodo1 = l_recuperar(listaHijos, l_primera(listaHijos));
            nodo1->padre = NULL;
            l_insertar(listaPadre,posInsertar,l_recuperar(listaHijos,pos));
            pos = l_siguiente(listaHijos,pos);
        }
        l_eliminar(listaPadre,posN,fEliminarNodoo);
        //free(n->elemento);
        free(n->hijos);  // DUDOSO, ¿no se pierden los hijos?
        //free(n->padre);
        n->padre = NULL;
        free(n);
    }

}

/**
 Destruye el árbol A, eliminando cada uno de sus nodos.
 Los elementos almacenados en el árbol son eliminados mediante la función fEliminar parametrizada.
**/
void a_destruir(tArbol * a, void (*fEliminar)(tElemento)){
/*
    tNodo raiz = (*a)->raiz;
    if(raiz != NULL){
        eliminarElementoDelNodo = fEliminar; // guardo la funcion para que sea visible en forma global
        l_destruir(&(raiz->hijos), eliminarNodo); // llamada recursiva hacia abajo
        fEliminar(raiz->elemento);
        free(raiz);
        (*a)->raiz=NULL;
    }
    free(a);
    a = NULL;
*/
 }

void eliminarNodo(tNodo nodo){
    /*
    l_destruir(&nodo->hijos, &eliminarNodo);
    eliminarElementoDelNodo(nodo->elemento);
    nodo->padre = NULL;
    free(nodo);
    */
}

/**
Recupera y retorna el elemento del nodo N.
*/
tElemento a_recuperar(tArbol a, tNodo n){
    return n->elemento;
}

/**
Recupera y retorna el nodo correspondiente a la raíz de A.
**/
tNodo a_raiz(tArbol a){
    return a->raiz;
}

/**
 Obtiene y retorna una lista con los nodos hijos de N en A.
**/
tLista a_hijos(tArbol a, tNodo n){
    return n->hijos;
}

/**
 Inicializa un nuevo árbol en *SA.
 El nuevo árbol en *SA se compone de los nodos del subárbol de A a partir de N.
 El subarbol de A a partir de N debe ser eliminado de A.
**/
void a_sub_arbol(tArbol a, tNodo n, tArbol * sa){
    (*sa) = malloc(sizeof(tNodo));
    if(*sa == NULL)
        exit(ARB_ERROR_MEMORIA);
}
