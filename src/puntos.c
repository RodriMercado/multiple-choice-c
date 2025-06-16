#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "puntos.h"
#include "jugadores.h"

// Guardar puntajes desde archivo

void guardarPuntajes(puntosPtr puntos, usuarioPtr jugador) {
    FILE *archPts = fopen("puntaje.txt", "r+");

    if (archPts == NULL) {
        printf("ERROR! No se pudo abrir el archivo de puntajes.\n");
        exit(1);
    }

    char linea[50];
    int encontrado = 0;

    while (fgets(linea, sizeof(linea), archPts) != NULL) {
        char alias[10];
        int dni, puntuacionMaxima;

        if (sscanf(linea, "%9[^,],%d,%d", alias, &dni, &puntuacionMaxima) == 3) {
            if (strcmp(getAlias(jugador), alias) == 0 && getDni(jugador) == dni) {
                encontrado = 1;

                // Actualiza la puntuación máxima si la nueva puntuación es mayor
                if (puntos->actuales > puntuacionMaxima) {
                    fseek(archPts, -1 * (strlen(linea) + 1), SEEK_CUR);
                    fprintf(archPts,"%s,%d,%d\n", getAlias(jugador), getDni(jugador), puntos->actuales);
                }
                break;
            }
        }
    }

    if (!encontrado) {
        // Si no se encontró al jugador, agrega una nueva entrada al final del archivo
        fseek(archPts, 0, SEEK_END);
        fprintf(archPts,"%s,%d,%d\n", getAlias(jugador), getDni(jugador), puntos->actuales);
    }
    fclose(archPts);
}


// Mostrar el historial de puntajes

void historialPuntajes() {
    printf("\nHistorial de Puntuaciones\n\n");
    printf("------------------------------------------------------\n");
    printf("ALIAS                 DNI                   PUNTAJES\n");
    printf("------------------------------------------------------\n\n");

    FILE *archPts = fopen("puntaje.txt", "r");
    if (archPts == NULL) {
        printf("No se pudo abrir el archivo de puntajes.\n");
        return;
    }

    char linea[50];

    while (fgets(linea, sizeof(linea), archPts) != NULL) {
        char alias[10];
        int dni;
        int puntaje;

        if (sscanf(linea, "%[^,],%d,%dpts\n", alias, &dni, &puntaje) == 3) {
            printf("%-10s            %d              %d\n", alias, dni, puntaje);
        }
    }

    fclose(archPts);
}


// Vaciar el historial de puntuacion

void vaciarHistorial() {

    FILE *archVacio = fopen("puntaje.txt", "w");

    if (archVacio == NULL) {
        printf("ERROR! No se pudo abrir el archivo");
        exit(1);
    }

    // Escribe datos en el archivo (en este caso, vacío)
    fprintf(archVacio,"%s","");

    fclose(archVacio);

    printf("\nEl Historial se ha borrado correctamente.\n");
}

// Iniciar los puntajes en 0 al comienzo de la partida

void iniciarPuntos(int puntajes[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        puntajes[i] = 0;
    }
}

// Mostrar los puntajes al final de la partida

void mostrarPuntajesFinales(usuarioPtr jugadores[], puntosPtr puntos[], int cantidad) {

    printf("\n------------- Puntajes Finales -------------\n");

    for (int i = 0; i < cantidad; i++) {
        printf("%-10s       %d\n", getAlias(jugadores[i]), puntos[i]->actuales);

    }
}
