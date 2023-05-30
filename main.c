// Pedro Teixeira Amorim
// 2022157609

// gcc main.c stops.c lines.c -o metromondego
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "stops.h"
#include "lines.h"

void guardarDados(LineList *firstLine, Stop *stops, int numStops, const char *filename)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return;
    }

    fwrite(&numStops, sizeof(int), 1, file); // Guardar o número de paragens

    fwrite(stops, sizeof(Stop), numStops, file); // Guardar as paragens

    LineList *currentLine = firstLine;
    while (currentLine != NULL) // Guardar os dados de cada linha
    {
        Line *line = &(currentLine->line);

        int lineNameLength = strlen(line->name);
        fwrite(&lineNameLength, sizeof(int), 1, file); // Escrever o tamanho do nome da linha

        fwrite(line->name, sizeof(char), lineNameLength, file); // Escrever o nome da linha

        fwrite(&(line->nStops), sizeof(int), 1, file); // Escrever o número de paragens da linha

        LineStop *currentStop = line->nextStop;
        while (currentStop != NULL)
        {
            int stopIndex = -1;
            for (int i = 0; i < numStops; i++)
            {
                if (strcmp(currentStop->stop.codigo, stops[i].codigo) == 0)
                {
                    stopIndex = i; // Guardar o indice de cada paragem
                    break;
                }
            }

            // Escrever o índice da paragem
            fwrite(&stopIndex, sizeof(int), 1, file);

            currentStop = currentStop->nextStop;
        }

        currentLine = currentLine->nextLine;
    }

    fclose(file);
    printf("Dados gravados com sucesso no ficheiro %s\n", filename);
}
int main()
{
    system("cls");
    int choice, numStops = 0, numLines = 0;
    Stop *stops = malloc(sizeof(Stop) * numStops);
    LineList *firstLine = NULL;
    LineList *currentLine = NULL;
    if (stops == NULL)
    {
        printf("Erro na alocação de memória");
        return 0;
    }
    FILE *file = fopen("metromondego.dat", "rb");
    if (file == NULL)
    {
        printf("Nao foi possivel abrir o arquivo metromondego.dat\n");
    } else {
    fread(&numStops, sizeof(int), 1, file);
    stops = realloc(stops, sizeof(Stop) * numStops);
    fread(stops, sizeof(Stop), numStops, file);
    fclose(file);
    }
    do
    {
        printf("\n\n--- MENU ---\n");
        printf("1 - Paragens\n");
        printf("2 - Linhas\n");
        printf("3 - Percursos\n");
        printf("4 - Exit\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: // submenu Paragens
            system("cls");
            printf("\n--Operacoes Paragens--\n");
            printf("1 - Listar todas as paragens\n");
            printf("2 - Adicionar nova paragem\n");
            printf("3 - Remover paragem existente\n");
            printf("4 - Voltar ao menu principal\n");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                system("cls");
                printStops(stops, numStops);
                break;

            case 2:
                system("cls");
                printf("\n--- Adicionar Paragem ---\n");
                stops = realloc(stops, sizeof(Stop) * (numStops + 1));
                int flag = 0;
                do
                {
                    stops[numStops] = addStop();
                    for (int i = 0; i < numStops; i++) // verificar codigos repetidos
                    {
                        if (strcmp(stops[i].codigo, stops[numStops].codigo) == 0)
                        {
                            flag = 1;
                            break;
                        }
                    }
                } while (flag);
                printStop(stops[numStops]);
                numStops++;
                break;

            case 3: // Apagar paragem
                system("cls");
                printStops(stops, numStops);
                printf("\n--- Apagar Paragem ---\n");
                stops = deleteStop(stops, &numStops, firstLine);
                break;
            case 4: // Back to main menu
                system("cls");
                printf("\n--- Back to main menu ---\n");
                choice = 0;
                break;

            default:
                printf("\nOpção inválida. Tente outra vez.\n");
                break;
            }

            break;
        case 2: // "Linhas"
            system("cls");
            printf("\n--Operacoes Linhas--\n");
            printf("1 - Ver Linhas\n");
            printf("2 - Adicionar nova Linha\n");
            printf("3 - Atualizar Linha existente\n");
            printf("4 - Voltar ao menu principal\n");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                system("cls");
                printf("\n--- Lista das Linhas ---\n\n");
                printAllLines(firstLine);
                break;

            case 2:
                system("cls");
                if (numStops > 1)
                {
                    printf("\n--- Adicionar Linha ---\n");
                    LineList *newLine = malloc(sizeof(LineList));
                    if (newLine == NULL)
                    {
                        printf("Erro na alocação de memória");
                        return 0;
                    }
                    newLine->line = addLine(stops, numStops);
                    newLine->nextLine = NULL;

                    if (firstLine == NULL)
                    {
                        firstLine = newLine;
                    }
                    else
                    {
                        LineList *currentLine = firstLine;
                        while (currentLine->nextLine != NULL)
                        {
                            currentLine = currentLine->nextLine;
                        }
                        currentLine->nextLine = newLine;
                    }

                    numLines++;
                }
                else
                {
                    printf("\nParagens Insuficientes");
                }

                break;

            case 3: // Alterar linha
                system("cls");
                printf("\n--- Atualizar Linha ---\n\n");

                Line *selectedLine = printAllLines(firstLine);
                if (selectedLine != NULL)
                {
                    updateLine(selectedLine, stops, numStops);
                }
                else
                {
                    printf("Linha Invalida");
                }

                break;

            case 4: // Back to main menu
                system("cls");
                printf("\n--- Back to main menu ---\n");
                choice = 0;
                break;

            default:
                printf("\nOpção inválida. Tente outra vez.\n");
                break;
            }
            break;
        case 3: // "Percursos"
            system("cls");
            printf("\nPercursos Menu\n");
            // TODO: Implement menu functionality for "Percursos"
            break;
        case 4: // "Exit"
            system("cls");
            guardarDados(firstLine, stops, numStops, "metromondego.dat");
            break;
        default:
            printf("\nOpção inválida. Tente outra vez.\n");
        }
    } while (choice != 4);

    free(firstLine);
    free(stops);
    return 0;
}
