#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include "jugadores.h"

struct Juego {
    usuarioPtr jugadores[4];
};

typedef struct Juego * juegoPtr;

void jugarPartida();
void desempatar(puntosPtr puntos[], usuarioPtr jugadores[], int cantidad);
int verificarEmpate(puntosPtr puntos[], int cantidad);

#endif // JUEGO_H_INCLUDED
