#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jugadores.h"
#include "preguntas.h"
#include "juego.h"
#include "generales.h"
#include "puntos.h"

int verificarEmpate(puntosPtr puntos[], int cantidad) {
    int maxPuntuacion = puntos[0]->actuales;
    int hayEmpate = 0;

    for (int i = 1; i < cantidad; i++) {
        if (puntos[i]->actuales == maxPuntuacion) {
            hayEmpate = 1;
        } else if (puntos[i]->actuales > maxPuntuacion) {
            maxPuntuacion = puntos[i]->actuales;
            hayEmpate = 0;
        }
    }

    return hayEmpate;
}


void desempatar(puntosPtr puntos[], usuarioPtr jugadores[], int cantidad) {

    //Se va a generar una multiplicacion Aleatoria entre dos numeros del 1 al 100.

    srand(time(NULL));
    int num1 = rand() % 100 + 50;  //Aleatorio de 50 a 100
    int num2 = rand() % 100 + 50;  //Aleatorio de 50 a 100
    int num3 = rand() % 100 + 50;  //Aleatorio de 50 a 149

    float rtaCorrecta = num1 * num2 / num3;
    float rtaUsuario;

    int diferenciaMinima = -1;
    int ganador = -1;

    printf("---------------------------------------------------------------------------------------\n");
    printf("La partida termino en empate.\n");
    printf("Se debe responder una pregunta matematica para determinar el ganador.\n");
    printf("El ganador sera quien acierte el resultado o quien este mas cerca de dicho resultado.\n");
    printf("---------------------------------------------------------------------------------------\n\n");

    int maxPuntuacion = puntos[0]->actuales;

    // Primero encuentra la máxima puntuacion
    for (int i = 1; i < cantidad; i++) {
        if (puntos[i]->actuales > maxPuntuacion) {
            maxPuntuacion = puntos[i]->actuales;
        }
    }

    // Bucle de la pregunta matematica
    for (int i = 0; i < cantidad; i++) {
        if (puntos[i]->actuales == maxPuntuacion) {
            printf("Responde el Jugador > %s <\n", getAlias(jugadores[i]));
            printf("Cual es el resultado de %d x %d / %d: ", num1, num2, num3);
            scanf("\n%f", &rtaUsuario);

            int diferencia = abs(rtaUsuario - rtaCorrecta);

            if (diferenciaMinima == -1 || diferencia < diferenciaMinima) {
                ganador = i;
                diferenciaMinima = diferencia;
            }
        }
    }

    // Al finalizar muestra el resultado del calculo matematico.
    printf("\nEl resultado es: %.2f",rtaCorrecta);

    // Mostrar el ganador y sumarle 1 punto extra.
    if (ganador != -1) {
        puntos[ganador]->actuales += 1;
        printf("\n\nEl jugador '%s' es el GANADOR y sumara un punto extra. Felicidades!\n", getAlias(jugadores[ganador]));
        presioneParaContinuar();
    }

}

void jugarPartida() {

    srand(time(NULL));

    printf("-------------- Inicia el Juego!!! --------------\n");

    //-------- Datos de los Jugadores -------
    int cantidad = cantJugadores();
    system("cls");

    usuarioPtr jugadores[cantidad];
    datosUsuario(jugadores, cantidad);
    system("cls");

    //-------- Cargar Preguntas -------
    preguntasPtr p[CANTPREGUNTAS];
    cargarPreguntas(p);

    //------- Puntajes de la partida -------
    int puntajesPartida[cantidad];
    puntosPtr puntos[cantidad];

    //------- Asignar Memoria puntos -------
    for (int i = 0; i < cantidad; i++) {
        puntos[i] = malloc(sizeof(struct Puntos));
    }

    // Inicia el puntaje en 0 al comenzar la partida
    for (int i = 0; i < cantidad; i++) {
        puntos[i]->actuales = 0;
    }

    // Inicializar puntajes de partida
    iniciarPuntos(puntajesPartida, cantidad);
    int puntaje = 0;

    //-------- Turno de los Jugadores -------
    int preguntasUtilizadas[CANTPREGUNTAS] = {0}; // Establecer todas las preguntas como no utilizada
    int contTurno = 1;
    int ronda = 1;
    int maxRonda = 25;

    while (contTurno <= cantidad) {

        printf("-------- Turno del jugador %d (%s) --------\n\n", contTurno, getAlias(jugadores[contTurno - 1]));

        // Contador de rondas

        if (ronda > maxRonda) {
            printf("Felicidades! Haz completado todas las rondas.\n");
            printf("Continua el siguiente jugador.\n");
            contTurno++;
            ronda = 1;  // Reiniciar la ronda al cambiar de jugador
            presioneParaContinuar();
            continue;  // Saltar al siguiente turno del jugador
        }

        // Mostrar Pregunta y Opciones

        int pregAle;
        do {
            pregAle = rand() % CANTPREGUNTAS;
        } while (preguntasUtilizadas[pregAle]);
        preguntasUtilizadas[pregAle] = 1;  // Marcar la pregunta como utilizada
        printf("Ronda %d\n", ronda);
        printf("%s\n", getPregunta(p[pregAle]));
        printf("\n");

        for (int i = 0; i < 4; i++) {
            printf("%d) %s\n", i + 1, getPosibles(p[pregAle], i));
        }
        int respuestaUsuario;
        printf("\nElija una opcion: ");



        // Tiempo
        clock_t inicio = clock();
        scanf("%d", &respuestaUsuario);
        clock_t fin = clock();

        double tiempoTranscurrido = (double)(fin - inicio) / CLOCKS_PER_SEC; // Tiempo en segundos

        if (tiempoTranscurrido <= 15) {
            int opcionCorrecta = getCorrecta(p[pregAle]);

            // Respuesta correcta y en tiempo = 15 puntos.
            if (respuestaUsuario == opcionCorrecta) {
                puntaje += 15;
                printf("Respuesta Correcta!\n");
                puntos[contTurno - 1]->actuales += 15;
            } else {
                printf("Ups! Respuesta Incorrecta. Continua el siguiente Jugador.\n");
                contTurno++;
                ronda = 0; // Reiniciar el contador de rondas
            }
        } else {

            // Respuesta correcta y tiempo excedido = 10 puntos.
            int opcionCorrecta = getCorrecta(p[pregAle]);

            if (respuestaUsuario == opcionCorrecta) {
                puntaje += 10;
                printf("Respuesta Correcta!\n");
                puntos[contTurno - 1]->actuales += 10;
            } else {
                printf("Respuesta Incorrecta. Continua el siguiente Jugador.\n");
                contTurno++;
                ronda = 0; // Reiniciar el contador de rondas
            }
        }
        ronda++;
        presioneParaContinuar();
    }

    // Restablecer las preguntas
    for (int i = 0; i < CANTPREGUNTAS; i++) {
        preguntasUtilizadas[i] = 0;  // Restablecer todas las preguntas como no utilizadas
    }

    //-------- Desempate (si es necesario) --------

    if (verificarEmpate(puntos, cantidad)) {
        desempatar(puntos, jugadores, cantidad);
        mostrarPuntajesFinales(jugadores, puntos, cantidad);
        presioneParaContinuar();
    }else{
        mostrarPuntajesFinales(jugadores, puntos, cantidad);
        presioneParaContinuar();
    }

    //-------- Guardar puntajes en Archivo --------

    for (int i = 0; i < cantidad; i++) {
        guardarPuntajes(puntos[i], jugadores[i]);
    }

    //-------- Liberar Memoria --------

    liberarJugadores(jugadores, cantidad);
    liberarPuntos(puntos, cantidad);
}
