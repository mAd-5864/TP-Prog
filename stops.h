// Pedro Teixeira Amorim
// 2022157609

#ifndef STOPS_H_INCLUDED
#define STOPS_H_INCLUDED

#define MAX_STOPS 40
#define MAX_NAME_LENGTH 20
#define MAX_CODE_LENGTH 4

typedef struct Stop Stop; // Estrutura para as paragens

struct Stop
{
    int valid;
    char name[MAX_NAME_LENGTH];
    char codigo[MAX_CODE_LENGTH + 1];
};

void getName(char *name, const char *message);
char *generateCode(char name[]);
Stop addStop();
void printStop(Stop stop);
void printStops(Stop tab[], int n);
#endif