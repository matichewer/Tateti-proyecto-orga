#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>

void fborrar(tElemento e){
    e = NULL;
    free(e);
}

void mostrarLista(tArbol arbol, tLista l){
    tPosicion pos;
    int i, num;
    if(l==NULL)
        printf("No tiene hijos.");
    else {
        tNodo nodoPadre = l_recuperar(l, l_primera(l));
        nodoPadre = (nodoPadre->padre);
        printf("Hijos de %d = <", *(int*) nodoPadre->elemento);
        pos = l_primera(l);
        if(l_longitud(l)>0){
            num = *((int*) a_recuperar(arbol, l_recuperar(l, pos)));
            printf(" %d", num);
            pos = l_siguiente(l, pos);
        }
        for(i=1; i<l_longitud(l); i++){
            num = *((int*) a_recuperar(arbol, l_recuperar(l, pos)));
            printf(", %d", num);
            pos = l_siguiente(l,pos);
        }
        printf(" >");
    }
    printf("\n");
}

int main() {

    tArbol arbol;
    int *a = (int *) malloc(sizeof(int));
    *a = 1;
    int *b = (int*) malloc(sizeof(int));
    *b = 2;
    int *c = (int*) malloc(sizeof(int));
    *c = 3;
    int* d = (int*) malloc(sizeof(int));
    *d = 4;
    int* e = (int*) malloc(sizeof(int));
    *e = 5;
    int* f = (int*) malloc(sizeof(int));
    *f = 6;
    int* g = (int*) malloc(sizeof(int));
    *g = 7;

    // Test creacion Arbol
    crear_arbol(&arbol);

    // Test creacion raiz
    crear_raiz(arbol,a);
    int num = *(int*) a_recuperar(arbol, a_raiz(arbol));
    printf("Creamos la raiz con un 1 y la mostramos: %d\n\n", num);

    // Test insertar
    tLista hijosDe1 = a_hijos(arbol, a_raiz(arbol));
    printf("Insertamos un 3 y 5 como hijo de 1, y lo mostramos:\n");
    tNodo posDe3= a_insertar(arbol, a_raiz(arbol), NULL, c);
    a_insertar(arbol, a_raiz(arbol), NULL, e);
    mostrarLista(arbol, hijosDe1);

    printf("\nInsertamos un 2 como primer hijo de 1 con NH= pos de 3, y lo mostramos:\n");
    a_insertar(arbol, a_raiz(arbol), l_recuperar(hijosDe1, l_primera(hijosDe1)), b);
    mostrarLista(arbol, hijosDe1);

    printf("\nInsertamos un 4 como hijo de 1 con NH= pos de 5, y lo mostramos:\n");
    tNodo posDe4 = a_insertar(arbol, a_raiz(arbol), l_recuperar(hijosDe1, l_ultima(hijosDe1)), d);
    mostrarLista(arbol, hijosDe1);

    printf("\nInsertamos un 6 como hijo de 3 con NH=NULL, y lo mostramos:\n");
    tLista hijosDe3 = a_hijos(arbol, posDe3);
    //tNodo posDe6= a_insertar(arbol, posDe3, NULL, f);
    a_insertar(arbol, posDe3, NULL, f);
    mostrarLista(arbol, hijosDe1);
    mostrarLista(arbol, hijosDe3);

    // Test eliminar
    printf("\nEliminamos el 4 de la lista.\n");
    //nodo4= l_recuperar(hijosDe1, l_anterior(hijosDe1, l_ultima(hijosDe1)))

    a_eliminar(arbol, posDe4, fborrar);
    mostrarLista(arbol, hijosDe1);
    mostrarLista(arbol, hijosDe3);


    printf("\nEliminamos el 3 de la lista. El 6 tiene que subir a la lista de hijos de 1\n");
    a_eliminar(arbol, posDe3, fborrar);
    mostrarLista(arbol, hijosDe1);



    // Test destruir
    printf("\nDestruimos el arbol.\n");
    a_destruir(&arbol, fborrar);
    arbol==NULL ? printf("El arbol se destruyó correctamente\n") : printf("El arbol no se destruyó correctamente\n");

    return 0;
}
