#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "preguntas.h"
#include "generales.h"

struct Pregunta {
    int nroPreg;
    char pregunta[150];
    char posibles[4][100];
    int correcta;
};

// Getters
int getNroPreg (preguntasPtr p){
    return p->nroPreg;
}
char * getPregunta (preguntasPtr p){
    return p->pregunta;
}
char * getPosibles (preguntasPtr p, int f){
    return p->posibles[f];
}
int getCorrecta(preguntasPtr p){
    return p->correcta;
}


// Cargar preguntas desde archivo
void cargarPreguntas(preguntasPtr preg[]) {
    FILE* archPreg = fopen("preguntas.txt", "r");
    FILE* archResp = fopen("respuestas.txt", "r");

    if (archPreg == NULL || archResp == NULL) {
        printf("Error al abrir archivos de preguntas o respuestas.\n");
        exit(1);
    }

    for (int i = 0; i < CANTPREGUNTAS; i++) {
        preg[i] = malloc (sizeof(struct Pregunta));

        // Cargar Pregunta
        fscanf(archPreg, "%d, %[^\n]\n", &preg[i]->nroPreg, preg[i]->pregunta);

        // Cargar las Opciones
        fscanf(archResp, "%d, %49[^,], %49[^,], %49[^,], %49[^,], %d\n",
               &preg[i]->nroPreg,
                preg[i]->posibles[0], preg[i]->posibles[1],
                preg[i]->posibles[2], preg[i]->posibles[3],
               &preg[i]->correcta);
    }

    fclose(archPreg);
    fclose(archResp);
}
