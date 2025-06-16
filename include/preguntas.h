#ifndef PREGUNTAS_H_INCLUDED
#define PREGUNTAS_H_INCLUDED
#define CANTPREGUNTAS 100

struct Pregunta;
typedef struct Pregunta * preguntasPtr;

void cargarPreguntas(preguntasPtr preguntas[]);
void liberarPreguntas(preguntasPtr preg[]);

int getNroPreg (preguntasPtr p);
char * getPregunta (preguntasPtr p);
char * getPosibles (preguntasPtr p, int f);
int getCorrecta(preguntasPtr p);


#endif // PREGUNTAS_H_INCLUDED
