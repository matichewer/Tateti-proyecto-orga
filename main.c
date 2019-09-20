#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

/*
void mostrarLista(tLista l)
{
    tPosicion pos;
    int i, num;
    if(l==NULL)
        printf("La lista no existe");
    else {
        pos = l_primera(l);
        printf("Lista = < ");
        //printf("%i",*(int *)elem);
        //pos = pos->siguiente;
        for(i=0; i<l_longitud(l); i++){
            num = *(int *)l_recuperar(l, pos);
            printf("%d, ", num);
            pos = l_siguiente(l,pos);
        }
        printf(" >");
        }
    printf("\n\n");
}

void fEliminar(tElemento e)
{
   free(e);
  e = NULL; // no se si ésta linea va
}

int main(){
    tLista l;

    int * a = (int *) malloc(sizeof(int));
    int * b = (int *) malloc(sizeof(int));
    int * c = (int *) malloc(sizeof(int));

    *a = 1;
    *b = 2;
    *c = 3;

    crear_lista(&l);
    printf("Lista vacia creada exitosamente.\n");
    printf("Longitud: %i\n", l_longitud(l));
    printf("Imprimiendo: ");
    mostrarLista(l);

    l_insertar(l, l_primera(l), b);
    printf("Se añade un %i al principio.\n", *b);
    printf("Longitud: %i\n", l_longitud(l));
    printf("Imprimiendo: ");
    mostrarLista(l);

    l_insertar(l, l_fin(l),c);
    printf("Se añade un %i al final.\n", *c);
    printf("Longitud: %i\n", l_longitud(l));
    printf("Imprimiendo: ");
    mostrarLista(l);

    l_insertar(l, l_primera(l),a);
    printf("Se añade un %i al principio.\n", *a);
    printf("Longitud: %i\n", l_longitud(l));
    printf("Imprimiendo: ");
    mostrarLista(l);

    printf("El primer elemento de la lista es %i.\n",*(int *)l_primera(l)->siguiente->elemento);
    printf("El ultimo elemento de la lista es %i.\n",*(int *)l_ultima(l)->elemento);
    printf("El fin de la lista es %i.\n",*(int *)l_fin(l)->elemento);

    printf("\nEl siguiente al primero es %i.\n",*(int *)l_siguiente(l,l_primera(l)->siguiente)->elemento);
    printf("El anterior al ultimo es %i.\n",*(int *)l_anterior(l,l_ultima(l))->elemento);
    printf("El anterior al fin es %i.\n\n",*(int *)l_anterior(l,l_fin(l))->elemento);

    printf("Recuperando ultimo elemento: %i\n",*(int *)l_recuperar(l,l_ultima(l)));

    // lo siguiente da error y esta bien que de error

 //    printf("\nEl siguiente al fin es %i.\n",*(int *)l_siguiente(l,l_fin(l)->siguiente)->elemento);
 //   printf("El anterior al primero es %i.\n",*(int *)l_anterior(l,l_primera(l))->elemento);


    printf("\nEliminando primer elemento.\n");
    l_eliminar(l,l_primera(l), &fEliminar);
    printf("Longitud: %i\n", l_longitud(l));
    printf("Imprimiendo: ");
    mostrarLista(l);

    printf("\nEliminando ultimo elemento.\n");
    l_eliminar(l,l_ultima(l), &fEliminar);
    printf("Longitud: %i\n", l_longitud(l));
    printf("Imprimiendo: ");
    mostrarLista(l);


    printf("\nEliminando elemento.\n");
    l_eliminar(l,l_primera(l), &fEliminar);
    printf("Longitud: %i\n", l_longitud(l));
    printf("Imprimiendo: ");
    mostrarLista(l);

    printf("Agregando 1 al principio...\n");
    l_insertar(l, l_primera(l),a);
    printf("Longitud: %i\n", l_longitud(l));
    printf("Imprimiendo: ");
    mostrarLista(l);


    l_insertar(l, l_fin(l),b);
    printf("Se añade un %i al final.\n", *b);
    printf("Longitud: %i\n", l_longitud(l));
    printf("Imprimiendo: ");
    mostrarLista(l);


    l_insertar(l, l_fin(l),c);
    printf("Se añade un %i al final.\n", *c);
    printf("Longitud: %i\n", l_longitud(l));
    printf("Imprimiendo: ");
    mostrarLista(l);


    // destruir no funciona
    printf("\nDestruyendo la lista..\n");
    l_destruir(&l, &fEliminar);
    printf("Longitud: %i\n", l_longitud(l));



}
*/
