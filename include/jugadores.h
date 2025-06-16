#ifndef JUGADORES_H_INCLUDED
#define JUGADORES_H_INCLUDED

struct Puntos;
typedef struct Puntos * puntosPtr;

struct Usuario;
typedef struct Usuario * usuarioPtr;

int cantJugadores();
void ingresarDatos(usuarioPtr jugador);
void datosUsuario(usuarioPtr jugadores[], int cantidad);
void liberarJugadores(usuarioPtr jugadores[], int cantidad);
void liberarPuntos (puntosPtr puntos[], int cantidad);

char * getAlias(usuarioPtr j);
int getDni (usuarioPtr j);

#endif // JUGADORES_H_INCLUDED


