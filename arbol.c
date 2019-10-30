#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>


void (*eliminarElementoDelNodo)(tElemento);  // acá se guarda la funcion de a_destruir()
void a_destruir_aux(tElemento elem);


void fNoEliminar(){}

void borrar(tElemento e){
    free(e);
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

    tLista listaHijos = n->hijos;
    int cantHijos= l_longitud(listaHijos);
    if ((a->raiz)==n){
        if (cantHijos==1){
            tNodo nodo = l_recuperar(listaHijos, l_primera(listaHijos));
            nodo->padre = NULL;
            fEliminar(a->raiz->elemento);
            a->raiz = nodo;
            l_destruir(&(n->hijos),&fNoEliminar);
            free(n);
        }
        else{
            if (cantHijos==0){
                free(n);
                a->raiz = NULL;
            }
            else{
                exit(ARB_OPERACION_INVALIDA);
            }
        }
    }
    else{//caso general
        //l_insertar inserta izquierda de la posicion dada
        tLista listaPadre = (n->padre)->hijos;
        tPosicion pos_a_eliminar = buscarPos(listaPadre, n);

        int i;
        tPosicion pos_hijos = l_primera(listaHijos);

        for(i=0; i<cantHijos; i++){
            tNodo nodo_hijo = l_recuperar(listaHijos, pos_hijos);
            nodo_hijo->padre = n->padre;
            l_insertar(listaPadre,pos_a_eliminar, nodo_hijo);
            pos_a_eliminar = l_siguiente(listaPadre, pos_a_eliminar);
            pos_hijos = l_siguiente(listaHijos, pos_hijos);
        }

        l_eliminar(listaPadre, pos_a_eliminar, &fNoEliminar);
        fEliminar(n->elemento);

        //Destruyo la lista de Hijos de n, pero sin eliminar los nodos
        l_destruir(&(n->hijos), &fNoEliminar);

        n->padre = NULL;
        n->elemento = NULL;
        free(n);
        n = NULL;
    }
}

void a_destruir_aux(tElemento elem){

    tNodo nodo;

    if(elem != NULL){
        nodo = elem;
        nodo->padre = NULL;
        eliminarElementoDelNodo(nodo->elemento);
        l_destruir(&(nodo->hijos), &a_destruir_aux);
        free(nodo);
        nodo = NULL;
    }

}

/**
 Destruye el árbol A, eliminando cada uno de sus nodos.
 Los elementos almacenados en el árbol son eliminados mediante la función fEliminar parametrizada.
**/
void a_destruir(tArbol * a, void (*fEliminar)(tElemento)){

    tNodo raiz = (*a)->raiz;
    eliminarElementoDelNodo = fEliminar; // guardo la funcion para que sea visible en forma global

    if(raiz != NULL)
            a_destruir_aux(raiz);

    free(*a);
    *a = NULL;

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
    (*sa) = malloc(sizeof(struct arbol));
    if(*sa == NULL)
        exit(ARB_ERROR_MEMORIA);

    tNodo padre;
    tLista hijospadre;
    tPosicion pos;

    if(n != a->raiz){
        padre=n->padre;
        hijospadre=padre->hijos;
        pos=l_primera(hijospadre);

        while( ( l_recuperar(hijospadre, pos) != n ) ){
            pos=l_siguiente(hijospadre, pos);
        }
        (*sa)->raiz=n;
        (*sa)->raiz->padre=NULL;
        l_eliminar(hijospadre, pos, &fNoEliminar);
    }
    else{
        (*sa)->raiz=a->raiz;
        a->raiz=NULL;
    }
}
