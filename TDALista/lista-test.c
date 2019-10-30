#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
void fEliminar(tElemento e){
    free(e);
    e = NULL;
}

void mostrarMenu(){
    printf("Test lista:\n\n");
    printf("1. Crear lista de enteros.\n");
    printf("2. Longitud de la lista.\n");
    printf("3. Agregar un entero al principio.\n");
    printf("4. Agregar un entero al final.\n");
    printf("5. Recuperar el primer elemento.\n");
    printf("6. Recuperar el último elemento.\n");
    printf("7. Eliminar la primera posicion.\n");
    printf("8. Eliminar la última posicion.\n");
    printf("9. Destruir la lista.\n");
    printf("10. Salir.\n\n");
}

void mostrarLista(tLista l){
    tPosicion pos;
    int i, num;
    if(l==NULL)
        printf("Lista no creada.");
    else {
        printf("Lista = <");
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

void mostrarLog(char log[]){
    printf("Estado: %s\n\n\n", log);
}

void mostrar_componentes(tLista l, char log[]){
    system("@cls||clear");
    mostrarMenu();
    mostrarLista(l);
    mostrarLog(log);
}

int main(){
    int opcion;
    int * num = NULL;
    char log[1000] = "";
    tLista lista = NULL;

    while(0==0){
        mostrar_componentes(lista, log);
        scanf("%d", &opcion);


        switch(opcion){
            case 1:
                if(lista==NULL){
                    crear_lista(&lista);
                    strcpy(log, "Lista vacía creada exitosamente. \n");
                }
                else
                    strcpy(log, "Para crear una nueva lista, primero destruya la anterior. \n");
                break;
            case 2:
                num = (int*) malloc(sizeof(int));
                *num = l_longitud(lista);
                strcpy(log, "La lista tiene ");
                char log_aux3[20];
                sprintf(log_aux3, "%i", *num);
                strcat(log, log_aux3);
                strcat(log, " elementos.");
                break;
            case 3:
                mostrar_componentes(lista, log);
                printf("Ingrese un número entero: ");
                num = (int*) malloc(sizeof(int));
                scanf("%i", num);
                l_insertar(lista,l_primera(lista),num);
                strcpy(log, "El número ha sido agregado exitosamente. \n");
                break;
            case 4:
                mostrar_componentes(lista, log);
                printf("Ingrese un número entero: ");
                num = (int*) malloc(sizeof(int));
                scanf("%i", num);
                l_insertar(lista,l_fin(lista),num);
                strcpy(log, "El número ha sido agregado exitosamente. \n");
                break;
            case 5:
                num = (int*) malloc(sizeof(int));
                num = l_recuperar(lista, l_primera(lista));
                strcpy(log, "El primer numero es el ");
                char log_aux[20];
                sprintf(log_aux, "%i", *num);
                strcat(log, log_aux);
                strcat(log, ".");
                break;
            case 6:
                num = (int*) malloc(sizeof(int));
                num = l_recuperar(lista, l_ultima(lista));
                strcpy(log, "El último numero es el ");
                char log_aux2[20];
                sprintf(log_aux2, "%i", *num);
                strcat(log, log_aux2);
                strcat(log, ".");
                break;
            case 7:
                l_eliminar(lista, l_primera(lista),fEliminar);
                strcpy(log, "El primer número ha sido borrado exitosamente. \n");
                break;
            case 8:
                l_eliminar(lista, l_ultima(lista), fEliminar);
                strcpy(log, "El último número ha sido borrado exitosamente. \n");
                break;
            case 9:
                l_destruir(&lista, fEliminar);
                strcpy(log, "La lista se ha borrado exitosamente. \n");
                break;
            case 10:
                exit(0);
        }
    }
}

*/
