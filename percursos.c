// Pedro Teixeira Amorim
// 2022157609

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lines.h"
#include "stops.h"

void getName(char *name, const char *message)
{
    printf("\n%s ", message);
    fflush(stdin);
    if (fgets(name, MAX_NAME_LENGTH, stdin) != NULL)
    {
        size_t len = strlen(name);
        if (len > 0 && name[len - 1] == '\n')
        {
            name[--len] = '\0';
        }
    }
}

void calcularPercurso(LineList *firstLine, char partida[], char destino[])
{
    system("cls");
    LineList *currentLine = firstLine;
    int direct = malloc(sizeof(int));
    int changeLine = 0;

    printf("\nPercursos diretos:\n");
    while (currentLine != NULL)
    {
        Line *line = &(currentLine->line);
        LineStop *currentStop = line->nextStop;
        int partidaFound = 0;
        int destinoFound = 0;

        // Check if starting and ending stops exist on the line
        while (currentStop != NULL)
        {
            if (strcmp(currentStop->stop.name, partida) == 0)
            {
                partidaFound = 1;
            }
            if (strcmp(currentStop->stop.name, destino) == 0)
            {
                destinoFound = 1;
            }

            if (partidaFound && destinoFound)
            {
                direct = 1;
                break;
            }

            currentStop = currentStop->nextStop;
        }

        if (direct)
        {
            printf("\nLinha %s\n", line->name);
            printf("[ %s -> ", partida);
            currentStop = line->nextStop;
            while (strcmp(currentStop->stop.name, partida) != 0)
            {
                currentStop = currentStop->nextStop;
            }
            while (currentStop != NULL)
            {
                currentStop = currentStop->nextStop;
                if (strcmp(currentStop->stop.name, destino) == 0)
                {
                    break;
                }
                printf("%s -> ", currentStop->stop.name);
            }
            printf("%s ]\n\n", destino);
        }

        printf("Linha atual: %s \n\n", currentLine->line.name);
        currentLine = currentLine->nextLine;
    }

    if (!direct)
    {
        printf("Nao existe percurso direto\n\n");
    }
}
