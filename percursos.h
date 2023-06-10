// Pedro Teixeira Amorim
// 2022157609
#include "stops.h"
#include "lines.h"

#ifndef PERCURSOS_H_INCLUDED
#define PERCURSOS_H_INCLUDED

void encontrarPercursoDireto(LineStop *currentStop, char partida[], char destino[], int *direct, int *invert);
void mostrarPercursoDireto(LineList *firstLine, char partida[], char destino[]);
void mostrarPercursoComEscala(LineList *firstLine, char partida[], char destino[]);
void calcularPercurso(LineList *firstLine, char partida[], char destino[]);
#endif