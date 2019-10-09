#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>

void fEliminar(tElemento e){
    free(e);
    e = NULL;
}

int main() {

    tArbol arbol;
    int *a = (int*) malloc(sizeof(int));
    *a = 1;
    int *b = (int*) malloc(sizeof(int));
    *b = 2;
    int *c = (int*) malloc(sizeof(int));
    *c = 3;
    int* d = (int*) malloc(sizeof(int));
    *d = 4;

    crear_arbol(&arbol);
    crear_raiz(arbol,a);
    int num = *(int *)a_recuperar(arbol, a_raiz(arbol));
    printf("%d", num);

    return 0;
}
