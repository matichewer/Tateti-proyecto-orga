#include "lista.h"
#include <stdio.h>
#include <stdlib.h>


void mostrarLista(tLista l)
{
    tPosicion pos = l->siguiente;

    if (pos == NULL)

        printf("Lista vacia.");

    else{

        printf("Lista = < ");
        printf("%i",*(int *)pos->elemento);
        pos = pos->siguiente;
        while (pos != NULL)
        {
            printf(", %d", *(int *)pos->elemento);
            pos = pos->siguiente;
        }
    printf(" >");
    }
    printf("\n\n");
}

void fEliminar(tElemento e)
{
    free(e);
  //  e = NULL;  no se si ésta linea va
}

int main(){
    int a = 1;
    int b = 2;
    int c = 3;
    tLista l = (tLista) malloc(sizeof(struct celda));
    crear_lista(&l);
    printf("Lista vacia creada exitosamente.\n");
    printf("Longitud: %i\n", l_longitud(l));
    printf("Imprimiendo: ");
    mostrarLista(l);

    l_insertar(l, l_primera(l),&b);
    printf("Se añade un %i al principio.\n", b);
    printf("Longitud: %i\n", l_longitud(l));
    printf("Imprimiendo: ");
    mostrarLista(l);

    l_insertar(l, l_fin(l),&c);
    printf("Se añade un %i al final.\n", c);
    printf("Longitud: %i\n", l_longitud(l));
    printf("Imprimiendo: ");
    mostrarLista(l);

    l_insertar(l, l_primera(l),&a);
    printf("Se añade un %i al principio.\n", a);
    printf("Longitud: %i\n", l_longitud(l));
    printf("Imprimiendo: ");
    mostrarLista(l);

    printf("El primer elemento de la lista es %i.\n",*(int *)l_primera(l)->siguiente->elemento);
    printf("El ultimo elemento de la lista es %i.\n",*(int *)l_ultima(l)->elemento);
    printf("El fin de la lista es %i.\n",*(int *)l_fin(l)->elemento);

    printf("\nEl siguiente al primero es %i.\n",*(int *)l_siguiente(l,l_primera(l)->siguiente)->elemento);
    printf("El anterior al ultimo es %i.\n",*(int *)l_anterior(l,l_ultima(l))->elemento);
    printf("El anterior al fin es %i.\n",*(int *)l_anterior(l,l_fin(l))->elemento);



    // No se por qué, pero lo comentado da error:
/*
    printf("Eliminando primer elemento.\n");
    l_eliminar(l,l_primera(l)->siguiente,fEliminar(&a));
    printf("Imprimiendo: ");
    mostrarLista(l);
*/
}
