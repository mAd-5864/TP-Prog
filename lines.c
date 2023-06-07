// Pedro Teixeira Amorim
// 2022157609

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "lines.h"
#include "stops.h"

void strtrim(char *str) {
    int len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        str[len - 1] = '\0';
        len--;
    }
}

void printLine(Line line, char start[], char finish[], int full, int reverse)
{
    LineStop *currentStop = line.nextStop;
    if (full)
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
    else if (reverse)
    {
        printf("\nLinha %s\n", line.name);
        printf("[ %s -> ", start);
        currentStop = line.nextStop;

        while (strcmp(currentStop->stop.name, start) != 0)
        {
            currentStop = currentStop->nextStop;
        }

        while (currentStop != NULL)
        {
            currentStop = currentStop->prevStop;
            if (strcmp(currentStop->stop.name, finish) == 0)
            {
                break;
            }
            printf("%s -> ", currentStop->stop.name);
        }

        printf("%s ]\n\n", finish);
    }
    else
    {
        printf("\nLinha %s\n", line.name);
        printf("[ %s -> ", start);
        currentStop = line.nextStop;
        while (strcmp(currentStop->stop.name, start) != 0)
        {
            currentStop = currentStop->nextStop;
        }

        while (currentStop != NULL)
        {
            currentStop = currentStop->nextStop;
            if (strcmp(currentStop->stop.name, finish) == 0)
            {
                break;
            }
            printf("%s -> ", currentStop->stop.name);
        }

        printf("%s ]\n\n", finish);
    }
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
                printLine(currentLine->line, NULL, NULL, 1, 0);
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
            if (strcmp(currentLine->line.name, l->name) == 0)
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
        LineStop *stop = addStopToLine(l, tab, numStops, 0, NULL);
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
    printLine(*l, NULL, NULL, 1, 0);
    return *l;
}

LineStop *addStopToLine(Line *line, Stop *tab, int numStops, int pos, char newStopCode[])
{
    LineStop *newStop = malloc(sizeof(LineStop));
    if (newStop == NULL)
    {
        printf("Erro na alocação de memória");
        return NULL;
    }

    newStop->nextStop = NULL;
    newStop->prevStop = NULL;

    int flag;
    do
    {
        flag = 0;
        char codeToAdd[MAX_CODE_LENGTH + 1];
        if (newStopCode == NULL)
        {
            printStops(tab, numStops);
            printf("\nIntroduza o codigo da paragem: ");
            fflush(stdin);
            scanf("%4s", codeToAdd);
        }
        else
        {
            strcpy(codeToAdd, newStopCode);
        }

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
                    p = line->nextStop;
                    newStop->stop = tab[i];
                    if (pos == 0)
                    {
                        if (line->nextStop == NULL)
                        {
                            line->nextStop = newStop;
                        }
                        else
                        {
                            while (p->nextStop != NULL)
                            {
                                p = p->nextStop;
                            }
                            p->nextStop = newStop;
                            newStop->prevStop = p;
                        }
                    }

                    if (pos == 1)
                    {
                        newStop->nextStop = line->nextStop;
                        if (line->nextStop != NULL)
                        {
                            line->nextStop->prevStop = newStop;
                        }
                        line->nextStop = newStop;
                        line->nStops++;
                    }
                    else if (pos > 1)
                    {
                        LineStop *currentStop = line->nextStop;
                        for (int j = 1; j < pos; j++)
                        {
                            currentStop = currentStop->nextStop;
                        }
                        newStop->nextStop = currentStop->nextStop;
                        if (currentStop->nextStop != NULL)
                        {
                            currentStop->nextStop->prevStop = newStop;
                        }
                        currentStop->nextStop = newStop;
                        newStop->prevStop = currentStop;

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

    stop = line->nextStop;
    while (stop != NULL && strcmp(stop->stop.codigo, codeToDelete) != 0)
    {
        stop = stop->nextStop;
    }

    if (stop == NULL)
    {
        printf("\nParagem nao pertence a Linha\n");
        return;
    }

    // apagar a paragem
    if (stop->prevStop == NULL)
    {
        line->nextStop = stop->nextStop;
        if (stop->nextStop != NULL)
        {
            stop->nextStop->prevStop = NULL;
        }
    }
    else
    {
        stop->prevStop->nextStop = stop->nextStop;
        if (stop->nextStop != NULL)
        {
            stop->nextStop->prevStop = stop->prevStop;
        }
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
                printLine(*selectedLine, NULL, NULL, 1, 0);
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
                addStopToLine(selectedLine, tab, numStops, posicaoEscolhida, NULL);
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

void *deleteLine(LineList **first, Line *selectedLine)
{

    LineList *currentLine = *first;
    LineList *prevLine = NULL;

    // FEncontrar a linha escolhida na lista de linhas
    while (currentLine != NULL && &(currentLine->line) != selectedLine)
    {
        prevLine = currentLine;
        currentLine = currentLine->nextLine;
    }

    // Remover linha escolhida
    if (prevLine != NULL)
    {
        prevLine->nextLine = currentLine->nextLine;
    }
    else
    {
        *first = currentLine->nextLine;
    }
    printf("Linha %s apagada", selectedLine->name);
    freeLine(selectedLine);
}

void readLineFromFile(LineList *firstLine, Stop **tab, int *numStops)
{
    printf("\nIntroduza o nome do ficheiro que pretende ler: ");
    char filename[MAX_NAME_LENGTH];
    char ext[5] = ".txt"; // Extensao do ficheiro
    scanf("%s", &filename);
    strcat(filename, ext);
    FILE *ficheiro = fopen(filename, "r");
    if (ficheiro == NULL)
    {
        system("cls");
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }

    char lineName[MAX_NAME_LENGTH];
    fgets(lineName, sizeof(lineName), ficheiro);
    lineName[strcspn(lineName, "\n")] = '\0';

    Line *newLine = (Line *)malloc(sizeof(Line));
    strcpy(newLine->name, lineName);
    newLine->nextStop = NULL;
    newLine->nStops = 0;

    char stopRow[1000];
    while (fgets(stopRow, sizeof(stopRow), ficheiro) != NULL)
    {
        newLine->nStops++;
        stopRow[strcspn(stopRow, "\n")] = '\0';

        char stopName[MAX_NAME_LENGTH];
        char stopCode[MAX_CODE_LENGTH + 1];

        if (sscanf(stopRow, "%[^#]#%s", stopName, stopCode) == 2)
        {
            strtrim(stopName);

            Stop newStop;
            strncpy(newStop.name, stopName, sizeof(newStop.name) - 1);
            newStop.name[sizeof(newStop.name) - 1] = '\0';
            strncpy(newStop.codigo, stopCode, sizeof(newStop.codigo) - 1);
            newStop.codigo[sizeof(newStop.codigo) - 1] = '\0';

            // Realocar o array dinâmico de paragens
            *numStops += 1;
            *tab = (Stop *)realloc(*tab, (*numStops) * sizeof(Stop));
            if (*tab == NULL)
            {
                printf("Erro ao alocar memória para o array de paragens.\n");
                fclose(ficheiro);
                return;
            }

            // Adicionar a nova paragem ao array dinâmico
            (*tab)[*numStops - 1] = newStop;
            addStopToLine(newLine, *tab, *numStops, 0, newStop.codigo);
        }
    }

    LineList *currentLine = (LineList *)malloc(sizeof(LineList));
    currentLine->line = *newLine;
    currentLine->nextLine = NULL;

    if (firstLine == NULL)
    {
        firstLine = currentLine;
    }
    else
    {
        LineList *last = firstLine;
        while (last->nextLine != NULL)
        {
            last = last->nextLine;
        }
        last->nextLine = currentLine;
    }

    fclose(ficheiro);
    system("cls");
    printf("\nLinha %s adicionada ao sistema com sucesso.\n", newLine->name);
}

void freeLine(Line *line)
{
    LineStop *currentStop = line->nextStop;
    while (currentStop != NULL)
    {
        LineStop *nextStop = currentStop->nextStop;
        free(currentStop);
        currentStop = nextStop;
    }

    // Libertar a memoria da linha escolhida
    free(line);
}
