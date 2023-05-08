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
    printf(" ]");
}

Line addLine(Stop *tab, int numStops)
{
    Line *l = malloc(sizeof(Line));
    l->nextStop = NULL;

    printf("\nNome da Linha: ");
    fflush(stdin);
    if (fgets(l->name, sizeof(l->name), stdin) != NULL)
    {
        size_t len = strlen(l->name);
        if (len > 0 && l->name[len - 1] == '\n')
        {
            l->name[--len] = '\0';
        }
    }
    do
    {

        printf("\nInsira o numero de Paragens da Linha: ");
        scanf("%d", &l->nStops);
        system("cls");
        if (l->nStops > numStops)
        {
            printf("\nApenas existem %d Paragens\n", numStops);
        }

    } while (l->nStops > numStops);

    LineStop *saveStop = NULL;
    for (int i = 0; i < l->nStops; i++)
    {
        LineStop *stop = addStopToLine(l, tab, numStops);
        if (saveStop == NULL)
        {
            l->nextStop = stop;
        }
        else
        {
            saveStop->nextStop = stop;
        }
        saveStop = stop;
    }
    printLine(*l);
    return *l;
}

LineStop *addStopToLine(Line *line, Stop *tab, int numStops)
{
    int cona = 0;
    LineStop *newStop = malloc(sizeof(LineStop));
    if (newStop == NULL)
    {
        printf("Erro na alocação de memória");
        return 0;
    };
    newStop->nextStop = NULL;
    int flag;
    do
    {
        flag = 0;
        printStops(tab, numStops);
        printf("\nIntroduza o codigo da paragem: ");
        char codeToAdd[MAX_CODE_LENGTH + 1];
        fflush(stdin);
        scanf("%4s", codeToAdd);

        LineStop *p = line->nextStop;
        for (int i = 0; i < numStops; i++)
        {
            if (strcmp(codeToAdd, tab[i].codigo) == 0)
            {
                flag++;
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
                    if (p != NULL)
                    {
                        while (p->nextStop != NULL)
                        {
                            p = p->nextStop;
                        }
                        p->nextStop = newStop;
                    }
                    newStop->stop = tab[i];
                    newStop->nextStop = NULL;
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
    return newStop;
}
