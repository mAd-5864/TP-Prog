//Pedro Teixeira Amorim
//2022157609
#include "stops.h"

#ifndef LINES_H_INCLUDED
#define LINES_H_INCLUDED


#define MAX_STOPS_LINE 40
#define MAX_NAME_LENGTH 20

typedef struct Line Line; // Estrutura para as linhas

struct Line {
    char name[MAX_NAME_LENGTH];
    struct Stop stops[MAX_STOPS_LINE];
    int nStops;
    struct Line* nextLine;
};

#endif