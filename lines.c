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
    printf("\n Linha %s - %d Paragens\n", line.name, line.nStops);
    LineStop *stop = line.nextStop;

    printf("[ %s", stop->stop.name);
    stop = stop->nextStop;
    for (int i = 1; i < line.nStops; i++)
    {
        printf("  <>  %s", stop->stop.name);
        stop = stop->nextStop;
    }
    printf(" ]\n");
}

Line *printAllLines(LineList *first)
{
    if (first == NULL)
    {
        printf("\nNao existe nenhuma linha");
    }
    else
    {
        int i = 0;
        LineList *currentLine = first;
        while (currentLine != NULL)
        {
            printf("%d - Linha %s\n", ++i, currentLine->line.name);
            currentLine = currentLine->nextLine;
        }
        int choice;
        scanf("%d", &choice);
        i = 0;
        currentLine = first;
        while (currentLine != NULL)
        {
            i++;
            if (choice == i)
            {
                system("cls");
                printLine(currentLine->line);
                return &(currentLine->line);
            }
            currentLine = currentLine->nextLine;
        }
        return NULL;
    }
}

Line addLine(Stop *tab, int numStops, LineList *firstLine)
{
    Line *l = malloc(sizeof(Line));
    l->nextStop = NULL;

    int flag = 0;
    do
    {
        flag = 0;
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

        LineList *currentLine = firstLine;
        while (currentLine != NULL)
        {
            if (strcmp(currentLine->line.name, l->name)==0)
            {
                flag = 1;
                system("cls");
                printf("\nLinha ja existente!\n");
                break;
            }
            currentLine = currentLine->nextLine;
        }

    } while (flag);
    do
    {
        printf("\nInsira o numero de Paragens da Linha: ");
        scanf("%d", &l->nStops);
        system("cls");
        if (l->nStops > numStops)
        {
            printf("\nApenas existem %d Paragens\n", numStops);
        }
        else if (l->nStops < 2)
        {
            printf("\nUma Linha deve ter pelo menos 2 Paragens\n", numStops);
        }
    } while (l->nStops > numStops || l->nStops < 2);

    LineStop *saveStop = NULL;
    for (int i = 0; i < l->nStops; i++)
    {
        LineStop *stop = addStopToLine(l, tab, numStops, 0);
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
    system("cls");
    printLine(*l);
    return *l;
}

LineStop *addStopToLine(Line *line, Stop *tab, int numStops, int pos)
{
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
                    newStop->stop = tab[i];
                    if (p != NULL)
                    {
                        if (pos == 0)
                        {
                            while (p->nextStop != NULL)
                            {
                                p = p->nextStop;
                            }
                            p->nextStop = newStop;
                            newStop->nextStop = NULL;
                        }
                    }
                    if (pos == 1)
                    {
                        newStop->nextStop = line->nextStop;

                        LineStop *lastStop = newStop;
                        while (lastStop->nextStop != NULL)
                        {
                            lastStop = lastStop->nextStop;
                        }
                        lastStop->nextStop = p;

                        line->nextStop = newStop;
                        line->nStops++;
                    }
                    else if (pos > 1)
                    {
                        LineStop *prevStop = line->nextStop;
                        for (int j = 1; j < pos - 1; j++)
                        {
                            prevStop = prevStop->nextStop;
                        }
                        newStop->nextStop = prevStop->nextStop;
                        prevStop->nextStop = newStop;

                        line->nStops++;
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
    return newStop;
}
void removeStopFromLine(Line *line)
{
    LineStop *stop = line->nextStop;
    for (size_t i = 0; i < line->nStops; i++)
    {
        printStop(stop->stop);
        stop = stop->nextStop;
    }
    printf("\nIntroduza o codigo da paragem a remover: ");
    char codeToDelete[MAX_CODE_LENGTH + 1];
    fflush(stdin);
    scanf("%4s", codeToDelete);

    LineStop *prevStop = NULL;
    stop = line->nextStop;
    while (stop != NULL && strcmp(stop->stop.codigo, codeToDelete) != 0)
    {
        prevStop = stop;
        stop = stop->nextStop;
    }

    if (stop == NULL)
    {
        printf("\nParagem nao pertence a Linha\n");
        return;
    }

    // apagar a paragem
    if (prevStop == NULL)
    {
        line->nextStop = stop->nextStop;
    }
    else
    {
        prevStop->nextStop = stop->nextStop;
    }
    system("cls");
    printf("\nParagem Removida da Linha %s\n", line->name);

    free(stop);
    line->nStops--;
}

Line *updateLine(Line *selectedLine, Stop *tab, int numStops)
{
    int choice;
    do
    {
        printf("\n--- Atualizar Linha ---\n");
        printf("\n1 - Adicionar Paragem");
        printf("\n2 - Remover Paragem");
        printf("\n3 - Voltar ao menu principal\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            system("cls");
            if (numStops > selectedLine->nStops)
            {
                printLine(*selectedLine);
                int posicaoEscolhida = 1;
                do
                {
                    if (posicaoEscolhida < 1 || posicaoEscolhida > selectedLine->nStops + 1)
                    {
                        printf("Posicao Invalida");
                    }
                    printf("\nEscolha a posicao da nova Paragem (1-%d):", selectedLine->nStops + 1);
                    scanf("%d", &posicaoEscolhida);
                } while (posicaoEscolhida < 1 || posicaoEscolhida > selectedLine->nStops + 1);
                addStopToLine(selectedLine, tab, numStops, posicaoEscolhida);
            }
            else
            {
                printf("Paragens Insuficientes");
            }
            break;

        case 2:
            system("cls");
            if (selectedLine->nStops > 2)
            {
                removeStopFromLine(selectedLine);
            }
            else
            {
                printf("A Linha %s apenas tem %d Paragens", selectedLine->name, selectedLine->nStops);
            }

            break;

        case 3:
            system("cls");
            printf("\n--- Back to main menu ---\n");
            break;

        default:
            printf("\nOpção inválida. Tente outra vez.\n");
            choice = 0;
            break;
        }
    } while (!choice);
    return selectedLine;
}
