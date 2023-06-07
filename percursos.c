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

void encontrarPercursoDireto(LineStop *currentStop, char partida[], char destino[], int *direct, int *invert)
{
    int partidaFound = 0, destinoFound = 0, i = 0;
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
                *invert = 1;
            }

            (*direct)++;
            break;
        }

        currentStop = currentStop->nextStop;
    }
}

void mostrarPercursoDireto(LineList *firstLine, char partida[], char destino[])
{
    system("cls");
    LineList *currentLine = firstLine;
    int direct = 0, notPossible = 1;

    printf("\nPercursos diretos possiveis:\n");
    while (currentLine != NULL)
    {
        Line *line = &(currentLine->line);
        LineStop *currentStop = line->nextStop;
        int invert = 0;
        direct = 1;
        encontrarPercursoDireto(currentStop, partida, destino, &direct, &invert);

        if (direct > 1)
        {
            printLine(*line, partida, destino, 0, invert);
            direct--;
            notPossible = 0;
        }

        currentLine = currentLine->nextLine;
    }

    if (notPossible)
    {
        system("cls");
        printf("\nNao existe percurso direto\n\n");
    }
}

void mostrarPercursoComEscala(LineList *firstLine, char partida[], char destino[])
{
    system("cls");
    printf("\nPercursos com Escala:\n");
    int changeLine = 0;
    LineList *currentLine = firstLine;
    while (currentLine != NULL)
    {
        Line *linhaPartida = &(currentLine->line);
        LineStop *currentStop = linhaPartida->nextStop;
        int partidaFound = 0;
        int i = 0;

        // Verificar se partida existe na linha atual
        while (currentStop != NULL)
        {
            i++;
            if (strcmp(currentStop->stop.name, partida) == 0)
            {
                partidaFound = i;
                break;
            }

            currentStop = currentStop->nextStop;
        }

        // Se a partida for encontrada na linha atual
        if (partidaFound)
        {
            int connectionCount = linhaPartida->nStops - 1, skip = 0;
            char possibleConnection[connectionCount][MAX_NAME_LENGTH];
            currentStop = linhaPartida->nextStop;
            for (size_t j = 0; j < connectionCount + 1; j++)
            {
                if (strcmp(currentStop->stop.name, partida) != 0 && strcmp(currentStop->stop.name, destino) != 0)
                    strcpy(possibleConnection[j - skip], currentStop->stop.name);
                else
                    skip++;
                currentStop = currentStop->nextStop;
            }

            LineList *currentLine = firstLine;
            int direct = 0;

            while (currentLine != NULL)
            {

                Line *line = &(currentLine->line);
                if (linhaPartida != line)
                {
                    LineStop *currentStop = line->nextStop;
                    int invert = 0, invert2 = 0, j;
                    direct = 1;
                    for (j = 0; j < connectionCount; j++)
                    {
                        invert = 0, invert2 = 0;
                        ;
                        encontrarPercursoDireto(currentStop, possibleConnection[j], destino, &direct, &invert);
                        if (direct > 1)
                        {
                            changeLine = 1;
                            int trash = 0;
                            encontrarPercursoDireto(linhaPartida->nextStop, partida, possibleConnection[j], &trash, &invert2);

                            printf("\n\n   ------- Linha %s -> Linha %s -------", linhaPartida->name, line->name);
                            printLine(*linhaPartida, partida, possibleConnection[j], 0, invert2);
                            printLine(*line, possibleConnection[j], destino, 0, invert);
                            direct--;
                        }
                    }
                }

                currentLine = currentLine->nextLine;
            }
        }
        currentLine = currentLine->nextLine;
    }
    if (!changeLine)
    {
        system("cls");
        printf("\nNao existe percurso com Escala\n\n");
    }
}

void calcularPercurso(LineList *firstLine, char partida[], char destino[])
{
    system("cls");
    mostrarPercursoDireto(firstLine, partida, destino);
    mostrarPercursoComEscala(firstLine, partida, destino);
}
