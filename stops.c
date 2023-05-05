// Pedro Teixeira Amorim
// 2022157609

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "stops.h"

char *generateCode() // Função para  gerar os codigos alfanumeéricos
{
    srand(time(NULL)); // Seed random number generator
    char *code = malloc((MAX_CODE_LENGTH + 1) * sizeof(char));

    for (int i = 0; i < MAX_CODE_LENGTH; i++)
    {
        int random_num = rand() % 36;
        if (random_num < 10)
        {
            code[i] = random_num + '0';
        }
        else
        {
            code[i] = random_num - 10 + 'A';
        }
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
    char *code = generateCode();
    strncpy(p.codigo, code, MAX_CODE_LENGTH);
    return p;
}

void printStop(struct Stop stop)
{
    printf("\nNome: %s\nCodigo: %s\n", stop.name, stop.codigo);
}
void printStops(Stop tab[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printStop(tab[i]);
    }
}

Stop *getStops(char *filename, int *numStops)
{
    FILE *file = fopen(filename, "r"); // Open file in read mode
    if (file == NULL)
    { // Check if file opened successfully
        printf("Failed to open file.\n");
        return NULL;
    }
    Stop *stops = malloc(sizeof(Stop) * MAX_STOPS); // Allocate memory for array
    if (stops == NULL)
    {
        printf("Erro na alocação de memória");
        fclose(file);
        return 0;
    }
    *numStops = 0; // Initialize number of stops to 0
    char line[MAX_NAME_LENGTH + 1];
    while (fgets(line, sizeof(line), file) != NULL)
    { // Read file line by line
        if (line[strlen(line) - 1] == '\n')
        { // Remove newline character at end of line
            line[strlen(line) - 1] = '\0';
        }
        if (*numStops >= MAX_STOPS)
        { // Check if array is full
            printf("Maximum number of stops reached.\n");
            break;
        }
        strcpy(stops[*numStops].name, line);
        strcpy(stops[*numStops].codigo, generateCode());
        (*numStops)++;
    }
    fclose(file);
    return stops;
}
