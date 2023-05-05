// Pedro Teixeira Amorim
// 2022157609

// gcc main.c stops.c lines.c -o metromondego
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "stops.h"

int main()
{
    system("cls");
    int choice, numStops = 0;
    Stop *stops = getStops("paragens.txt", &numStops);
    if (stops == NULL)
    {
        printf("Nao foi possivel aceder ao ficheiro\n");
        return 1;
    }
    /*     Stop *stops = malloc(sizeof(Stop) * numStops);
        if (stops == NULL)
        {
            printf("Erro na alocação de memória");
            return 0;
        } */
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
                printf("\n--- Lista das Paragens ---\n");
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
                    for (int i = 0; i < numStops; i++)
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
                printf("\n--- Apagar Paragem ---\n");
                printf("Introduza o codigo da paragem: ");
                char codeToDelete[MAX_CODE_LENGTH + 1];
                fflush(stdin);
                scanf("%s", codeToDelete);

                int deleted = 0;
                for (int i = 0; i < numStops; i++)
                {
                    if (strcmp(codeToDelete, stops[i].codigo) == 0)
                    {
                        deleted = 1;
                        for (int j = i + 1; j < numStops; j++)
                        {
                            stops[j - 1] = stops[j];
                        }
                        numStops--;
                        printf("\nParagem Apagada\n");
                        break;
                    }
                }
                if (!deleted)
                {
                    printf("\nParagem nao encontrada\n");
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
                printf("\n--- Lista das Linhas ---\n");
                // TODO: Implement menu functionality for "Linhas"
                break;

            case 2:
                system("cls");
                printf("\n--- Adicionar Linha ---\n");
                // TODO: Implement menu functionality for "Linhas"
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

    free(stops);
    system("cls");
    return 0;
}