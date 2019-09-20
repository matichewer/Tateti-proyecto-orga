#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

void abrir_menu(){
    printf("Test lista:\n\n");
    printf("1. Crear lista de enteros.\n");
    printf("2. Agregar un entero a la lista.\n");
    printf("3. Mostrar lista.\n");
    printf("4. Destruir la lista.\n");
    printf("5. Salir.\n\n");
}

int main(){
    int opcion;
    int * num = NULL;
    char [] logs;
    tLista lista = NULL;


    while(0==0){
        abrir_menu();
        scanf("%d", &opcion);
        //system("@cls||clear");


        switch(opcion){
            case 1:
                crear_lista(&lista);
                printf("Lista vacía creada exitosamente. \n");
                break;
            case 2:
                printf("Inserte su nro entero: ");
                num = (int*) malloc(sizeof(int));
                scanf("%i", num);
                l_insertar(lista,l_primera(lista),num);
                printf("Su numero %d ha sido agregado. \n",*num);
                break;
            case 5:
                exit(0);

    }
    }
}


