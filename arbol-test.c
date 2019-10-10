#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>

void fEliminar(tElemento e){
    free(e);
    e = NULL;
}

void mostrarLista(tLista l){
    tPosicion pos;
    int i, num;
    if(l==NULL)
        printf("Lista no creada.");
    else {
        printf("Lista de hijos = <");
        pos = l_primera(l);
        if(l_longitud(l)>0){
            num = *(int *)l_recuperar(l, pos);
            printf(" %d", num);
            pos = l_siguiente(l, pos);
        }
        for(i=1; i<l_longitud(l); i++){
            num = *(int *)l_recuperar(l, pos);
            printf(", %d", num);
            pos = l_siguiente(l,pos);
        }
        printf(" >");
    }
    printf("\n\n");
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

    crear_arbol(&arbol);
    crear_raiz(arbol,a);
    int num = *(int*) a_recuperar(arbol, a_raiz(arbol));
    printf("Creamos la raiz con un 1 y la mostramos: %d\n\n", num);


    printf("Insertamos un 2 como hijo de 1, y lo mostramos\n\n");
    a_insertar(arbol, a_raiz(arbol), NULL, b);

    tLista hijos= a_hijos(arbol, a_raiz(arbol));
    num = *((int*) l_recuperar(hijos, l_primera(hijos)));
    printf("Entro aca con %d\n", num);

    a_eliminar(arbol, a_raiz(arbol), fEliminar);
    num = *(int*) a_recuperar(arbol, a_raiz(arbol));
    printf("Mostramos raiz %d\n\n", num);

    /*
    a_insertar(arbol, a_raiz(arbol), NULL, c);
    a_insertar(arbol, a_raiz(arbol), NULL, d);
    mostrarLista(a_hijos(arbol, a_raiz(arbol)));
*/



    return 0;
}
