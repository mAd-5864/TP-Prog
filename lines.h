// Pedro Teixeira Amorim
// 2022157609
#include "stops.h"

#ifndef LINES_H_INCLUDED
#define LINES_H_INCLUDED

#define MAX_STOPS_LINE 40
#define MAX_NAME_LENGTH 20

typedef struct Line Line; // Estrutura para as linhas
typedef struct LineStop LineStop; // Estrutura para as paragens da linha
typedef struct LineList LineList; // Lista das Linhas

struct LineStop {
    Stop stop;
    LineStop *nextStop;
};

struct Line
{
    char name[MAX_NAME_LENGTH];
    int nStops;
    LineStop *nextStop;
};

struct LineList {
    Line line;
    LineList *nextLine;
};

void printLine(Line line);
Line *printAllLines(LineList *first);
Line addLine(Stop *tab, int numStops);
LineStop *addStopToLine(Line *line, Stop *tab, int numStops);
void removeStopFromLine(Line *line);
Line *updateLine(Line *selectedLine, Stop *tab, int numStops);
#endif