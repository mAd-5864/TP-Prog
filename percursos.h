// Pedro Teixeira Amorim
// 2022157609
#include "stops.h"
#include "lines.h"

#ifndef PERCURSOS_H_INCLUDED
#define PERCURSOS_H_INCLUDED

void calcularPercurso(LineList *firstLine, char partida[], char destino[]);
void getName(char* name, const char* message);
#endif