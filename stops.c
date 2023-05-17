// Pedro Teixeira Amorim
// 2022157609

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "stops.h"
#include "lines.h"

char *generateCode(char name[]) // Função para  gerar os codigos alfanumeéricos
{
    srand(time(NULL)); // Seed random number generator
    char *code = malloc((MAX_CODE_LENGTH + 1) * sizeof(char));

    code[0] = toupper(name[0]);
    for (int i = 1; i < MAX_CODE_LENGTH; i++)
    {
        int random_num = rand() % 10;
        code[i] = random_num + '0';
    }
    code[MAX_CODE_LENGTH] = '\0';
    return code;
}

Stop addStop()
{
    Stop p;

    printf("Nome da Paragem: ");
    fflush(stdin);
    if (fgets(p.name, sizeof(p.name), stdin) != NULL)
    {
        size_t len = strlen(p.name);
        if (len > 0 && p.name[len - 1] == '\n')
        {
            p.name[--len] = '\0';
        }
    }
    char *code = generateCode(p.name);
    strcpy(p.codigo, code);
    p.valid = 1;
    return p;
}

void printStop(Stop stop)
{
    printf("\nNome: %s\nCodigo: %s\n", stop.name, stop.codigo);
}
void printStops(Stop tab[], int n)
{
    printf("\n--- Lista das Paragens ---\n");
    for (int i = 0; i < n; i++)
    {
        printStop(tab[i]);
    }
}
Stop *deleteStop(Stop *stops, int *numStops, LineList *firstLine)
{
    printf("Introduza o codigo da paragem: ");
    char codeToDelete[MAX_CODE_LENGTH + 1];
    fflush(stdin);
    scanf("%5s", codeToDelete);

    int deleted = 0;
    for (int i = 0; i < *numStops; i++)
    {
        if (strcmp(codeToDelete, stops[i].codigo) == 0)
        {
            LineList *currentLine = firstLine;
            while (currentLine != NULL)
            {
                LineStop *currentStop = currentLine->line.nextStop;
                while (currentStop != NULL)
                {
                    if (strcmp(stops[i].codigo, currentStop->stop.codigo) == 0)
                    {
                        printf("\nRemova a paragem da Linha %s antes de a apagar\n", currentLine->line.name);
                        deleted = 1;
                        break;
                    }
                    currentStop = currentStop->nextStop;
                }
                currentLine = currentLine->nextLine;
            }
            if (!deleted)
            {
                deleted = 1;
                for (int j = i + 1; j < *numStops; j++)
                {
                    stops[j - 1] = stops[j];
                }
                (*numStops)--;
                printf("\nParagem Apagada\n");
            }
            break;
        }
    }
    if (!deleted)
    {
        printf("\nParagem nao encontrada\n");
    }
    return stops;
}

Stop *getStops(char *filename, int *numStops)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Erro ao abrir ficheiro\n");
        return NULL;
    }

    Stop *stops = malloc(sizeof(Stop) * MAX_STOPS);
    if (stops == NULL)
    {
        printf("Erro na alocação de memória");
        fclose(file);
        return 0;
    }

    *numStops = 0;
    char line[MAX_NAME_LENGTH + 1];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (line[strlen(line) - 1] == '\n')
        {
            line[strlen(line) - 1] = '\0';
        }
        if (*numStops >= MAX_STOPS)
        {
            printf("Numero maximo de paragens atingido\n");
            break;
        }
        strcpy(stops[*numStops].name, line);
        strcpy(stops[*numStops].codigo, generateCode(stops[*numStops].name));
        (*numStops)++;
    }
    fclose(file);
    return stops;
}
/* Stop* readStop(FILE* file) {
    Stop* stop = malloc(sizeof(Stop));
    if (stop == NULL) {
        printf("Failed to allocate memory for Stop.\n");
        return NULL;
    }
    if (fscanf(file, " %[^#]#%s", stop->name, stop->codigo) != 2) {
        free(stop);
        return NULL;
    }
    stop->valid = 1;
    return stop;
} */
