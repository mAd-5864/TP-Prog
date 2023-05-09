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
    // Stop *stops = getStops("paragens.txt", &numStops);

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
                stops = deleteStop(stops, &numStops);
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

            case 3: // Apagar paragem
                system("cls");
                printf("\n--- Atualizar Linha ---\n");
                printf("Escolha a linha: ");

                // TODO: Implement menu functionality for "Linhas"
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
            printf("\nFim Programa!\n");
            break;
        default:
            printf("\nOpção inválida. Tente outra vez.\n");
        }
    } while (choice != 4);

    free(firstLine);
    free(stops);
    system("cls");
    return 0;
}