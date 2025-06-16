#ifndef RESPUESTAS_H_INCLUDED
#define RESPUESTAS_H_INCLUDED

struct Respuesta {
    int nroRespuesta;
    char respuesta[100];
    int correcta; // 0 o 1
};
typedef struct Respuesta * respuestasPtr;

void cargarRespuestas(respuestasPtr respuestas[], int cantidadRespuestas);

#endif // RESPUESTAS_H_INCLUDED
