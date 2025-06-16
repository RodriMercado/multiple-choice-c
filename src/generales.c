#include <stdio.h>
#include <stdlib.h>
#include "generales.h"
#include "puntos.h"
#include "jugadores.h"

//Funciones Generales

void presioneParaContinuar() {
    printf("\nPresiona una tecla para continuar...");
    getchar();
    getchar();
    system("cls");
}

int menuPrincipal() {
    int opcion;
    printf("\n\n--------- BIENVENIDOS!!! ---------\n\n");
    printf("Menu Principal:\n");
    printf("1. Jugar Partida\n");
    printf("2. Mostrar Puntajes\n");
    printf("3. Vaciar Historial\n");
    printf("4. Salir\n");
    printf("\nSeleccione una opcion: ");

    scanf("%d", &opcion);

    return opcion;
}

int menuVaciarHistorial() {
    int opcion;
    printf("\n\nQuieres eliminar historial?\n\n");
    printf("1. SI\n");
    printf("2. NO\n");
    printf("\nIngrese una opcion: ");
    scanf("%d", &opcion);

    while (opcion != 1 && opcion != 2) {
        printf("Por favor, ingrese opcion 1 o 2: ");
        scanf("%d", &opcion);
    }

    if (opcion == 1) {
        vaciarHistorial();
        presioneParaContinuar();
    } else {
        printf("\nAccion cancelada, regresando al menu principal.\n");
        presioneParaContinuar();
    }

    return opcion;
}


