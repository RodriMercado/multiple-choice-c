#ifndef PUNTOS_H_INCLUDED
#define PUNTOS_H_INCLUDED

struct Usuario;
typedef struct Usuario * usuarioPtr;


struct Puntos {
    int actuales;
};

typedef struct Puntos * puntosPtr;

void guardarPuntajes(puntosPtr puntos, usuarioPtr jugador);

void historialPuntajes();
void iniciarPuntos(int puntajes[], int cantidad);
void mostrarPuntajesFinales(usuarioPtr jugadores[], puntosPtr puntos[], int cantidad);
void vaciarHistorial();


#endif // PUNTOS_H_INCLUDED
