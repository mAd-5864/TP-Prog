// Pedro Teixeira Amorim
// 2022157609

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "lines.h"
#include "stops.h"

Line addLine()
{
    Line l;

    printf("\nNome da Linha: ");
    fflush(stdin);
    if (fgets(l.name, sizeof(l.name), stdin) != NULL)
    {
        size_t len = strlen(l.name);
        if (len > 0 && l.name[len - 1] == '\n')
        {
            l.name[--len] = '\0';
        }
    }
    printf("\nInsira o numero de Paragens da Linha: ");
    scanf("%d", &l.nStops);
    addStopsToLine(l);
    // printStops(stops, numStops);
}

/* char **readCodes(int numCodes)
{
    char **codes = malloc(numCodes * sizeof(char *));
    if (codes == NULL)
    {
        printf("Error allocating memory\n");
        exit(1);
    }
    for (int i = 0; i < numCodes; i++)
    {
        codes[i] = malloc(MAX_CODE_LENGTH + 1);
        if (codes[i] == NULL)
        {
            printf("Error allocating memory\n");
            exit(1);
        }
        printf("Enter code %d: ", i + 1);
        scanf("%s", codes[i]);
    }
    return codes;
} */

Line addStopsToLine(Line line)
{
    for (int i = 0; i < line.nStops; i++)
    {
        if (line.stops[i].name[0] == '\0')
        {
            printf("Insira o codigo da paragem a adicionar: ");
        }
    }
}