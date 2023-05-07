// Pedro Teixeira Amorim
// 2022157609

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "lines.h"
#include "stops.h"

void printLine(Line line)
{
    system("cls");
    printf("\nLinha %s - %d Paragens\n", line.name, line.nStops);
    LineStop *stop = line.nextStop;

    printf("[ %s", stop->stop.name);
    stop = stop->nextStop;
    for (int i = 1; i < line.nStops; i++)
    {
        printf("  <->  %s", stop->stop.name);
        stop = stop->nextStop;
    }

    /*     while (stop != NULL)
        {
            stop = stop->nextStop;
            printf(" <-> %s", stop->stop.name);
        } */
    printf(" ]");
}

Line addLine(Stop *tab, int numStops)
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
    do
    {

        printf("\nInsira o numero de Paragens da Linha: ");
        scanf("%d", &l.nStops);
        system("cls");
        if (l.nStops > numStops)
        {
            printf("\nApenas existem %d Paragens\n", numStops);
        }

    } while (l.nStops > numStops);

    LineStop *prevStop = NULL;
    for (int i = 0; i < l.nStops; i++)
    {
        LineStop *stop = addStopToLine(&l, tab, numStops);
        if (prevStop == NULL)
        {
            l.nextStop = stop;
        }
        else
        {
            prevStop->nextStop = stop;
        }
        prevStop = stop;
    }
    printLine(l);
    return l;
}

LineStop *addStopToLine(Line *line, Stop *tab, int numStops)
{
    LineStop *stop = NULL;
    int flag;
    do
    {
        flag = 0;
        printStops(tab, numStops);
        printf("\nIntroduza o codigo da paragem: ");
        char codeToAdd[MAX_CODE_LENGTH + 1];
        fflush(stdin);
        scanf("%5s", codeToAdd);

        for (int i = 0; i < numStops; i++)
        {
            if (strcmp(codeToAdd, tab[i].codigo) == 0)
            {
                flag++;
                LineStop *p = stop;
                while (p != NULL)
                {
                    if (strcmp(codeToAdd, p->stop.codigo) == 0)
                    {
                        flag++;
                        system("cls");
                        printf("\nParagem ja pertence a Linha\n");
                        break;
                    }
                    p = p->nextStop;
                }
                if (flag == 1)
                {
                    LineStop *newStop = (LineStop *)malloc(sizeof(LineStop));
                    newStop->stop = tab[i];
                    newStop->nextStop = NULL;
                    if (stop == NULL)
                    {
                        stop = newStop;
                    }
                    else
                    {
                        LineStop *p = stop;
                        while (p->nextStop != NULL)
                        {
                            p = p->nextStop;
                        }
                        p->nextStop = newStop;
                    }
                    system("cls");
                    printf("\nParagem Adicionada\n");
                    break;
                }
            }
        }

        if (!flag)
        {
            system("cls");
            printf("\nParagem nao encontrada\n");
        }
    } while (flag != 1);

    return stop;
}
