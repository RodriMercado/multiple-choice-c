#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jugadores.h"

struct Usuario {
    char alias[10];
    int dni;
    puntosPtr puntos;
};

int getDni (usuarioPtr j){
    return j->dni;
}

char * getAlias (usuarioPtr j){
    return j->alias;
}

void ingresarDatos(usuarioPtr jugador) {

    printf("Ingresar ALIAS: ");
    fflush(stdin);
    gets(getAlias(jugador));

    while(strlen(getAlias(jugador)) > 10){
        printf("ERROR! Alias demasiado largo (Max 10 caracteres). Intente nuevamente.");
        printf("\nIngresar ALIAS: ");
        fflush(stdin);
        gets(getAlias(jugador));
    }

    printf("Ingresar DNI: ");
    scanf("%d", &jugador->dni);

    getchar();
}


void datosUsuario(usuarioPtr jugadores[], int cantidad) {

    for (int i = 0; i < cantidad; i++) {
        jugadores[i] = (usuarioPtr)malloc(sizeof(struct Usuario));
        printf("\n----------- JUGADOR %d -----------\n", i + 1);
        ingresarDatos(jugadores[i]);
    }
    printf("\n");
}

int cantJugadores() {
    int cantidad;

    do {
        printf("\nIngrese la cantidad de jugadores (Max 4): ");
        scanf("%d", &cantidad);

        if (cantidad < 2 || cantidad > 4) {
            printf("El numero de jugadores debe ser de 2 a 4.\n");
        } else {
            return cantidad;
        }

    } while (1);
}

void liberarJugadores(usuarioPtr jugadores[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        free(jugadores[i]);
        jugadores[i] = NULL;
    }
}

void liberarPuntos(puntosPtr puntos[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        free(puntos[i]);
        puntos[i] = NULL;
    }
}
