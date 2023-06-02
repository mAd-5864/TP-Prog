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
    int direct = 0;
    int changeLine = 0;

    printf("\nPercursos diretos possiveis:\n");
    while (currentLine != NULL)
    {
        Line *line = &(currentLine->line);
        LineStop *currentStop = line->nextStop;
        int partidaFound = 0;
        int destinoFound = 0;
        int i = 0, invert = 0;
        direct = 1;

        // Verificar se viagem e possivel na linha
        while (currentStop != NULL)
        {
            i++;
            if (strcmp(currentStop->stop.name, partida) == 0)
            {
                partidaFound = i;
            }
            if (strcmp(currentStop->stop.name, destino) == 0)
            {
                destinoFound = i;
            }

            if (partidaFound && destinoFound)
            {
                if (partidaFound > destinoFound)
                {
                    invert = 1;
                }

                direct++;
                break;
            }

            currentStop = currentStop->nextStop;
        }

        if (direct > 1)
        {
            if (invert)
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
                    currentStop = currentStop->prevStop;
                    if (strcmp(currentStop->stop.name, destino) == 0)
                    {
                        break;
                    }
                    printf("%s -> ", currentStop->stop.name);
                }

                printf("%s ]\n\n", destino); // Print 'partida' as the destination
            }
            else
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
            direct--;
        }

        currentLine = currentLine->nextLine;
    }

    if (!direct)
    {
        printf("Nao existe percurso direto\n\n");
    }
}
