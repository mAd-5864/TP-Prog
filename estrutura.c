#include <stdio.h>
#include <string.h>

#define MAX_STOPS 10
#define MAX_NAME_LENGTH 30
#define MAX_CODE_LENGTH 3

// Estrutura para as paragens
struct Stop {
    char name[MAX_NAME_LENGTH];
    char codigo[MAX_CODE_LENGTH];
};

// Estrutura para as linhas
struct Line {
    char name[MAX_NAME_LENGTH];
    struct Stop stops[MAX_STOPS];
    int nStops;
    struct Line* nextLine;
};

int main() { // Paragens
    struct Stop pombal = {"Pombal", "POM"};
    struct Stop soure = {"Soure", "SOU"};
    struct Stop alfarelos = {"Alfarelos", "ALF"};
    struct Stop coimbraB = {"CoimbraB", "COB"};
    struct Stop coimbra = {"Coimbra", "COI"};
    struct Stop pampilhosa = {"Pampilhosa", "PAM"};
    struct Stop mealhada = {"Mealhada", "MEA"};
    struct Stop mogofresAnadia = {"Mogofres-Anadia", "ANA"};
    struct Stop figueiraFoz = {"Figueira da Foz", "FIG"};
    struct Stop bifurcacaoLares = {"Bifurcação de Lares", "BLA"};
    struct Stop cantanhede = {"Cantanhede", "CAN"};
    struct Stop mira = {"Mira", "MIR"};
    struct Stop mortagua = {"Mortágua", "MOR"};
    struct Stop hospitalPediatrico = {"Hospital Pediátrico", "PED"};
    struct Stop lojaCidadao = {"Loja do Cidadão", "CID"};
    struct Stop portagem = {"Portagem", "POR"};
    struct Stop quintaFonte = {"Quinta da Fonte", "QFO"};
    struct Stop sobralCeira = {"Sobral de Ceira", "SCE"};
    struct Stop condeixaNova = {"Condeixa-a-Nova", "CNO"};
    struct Stop mirandaCorvo = {"Miranda do Corvo", "MCO"};
    struct Stop lousa = {"Lousã", "LOU"};
    struct Stop serpins = {"Serpins", "SER"};
    struct Stop vilaNovaCeira = {"Vila Nova do Ceira", "VCE"};

    // Linhas
    struct Line linhaVermelha = {"Linha Vermelha", {pombal, soure, alfarelos, coimbraB, coimbra, coimbraB, pampilhosa, mealhada, mogofresAnadia}, 9, NULL};
    struct Line linhaVerde = {"Linha Verde", {figueiraFoz, bifurcacaoLares, alfarelos, coimbraB, coimbra}, 5, NULL};
    struct Line linhaVerdeAuxiliar = {"Linha Verde Auxiliar", {louriçal, bifurcacaoLares}, 2, NULL};
    struct Line linhaAzul = {"Linha Azul", {figueiraFoz, cantanhede, pampilhosa}, 3, NULL};
    struct Line linhaAzulAuxiliar = {"Linha Azul Auxiliar", {mira, cantanhede}, 2, NULL};
    struct Line linhaRoxa = {"Linha Roxa", {mortagua, pampilhosa, coimbraB}, 3, NULL};
    struct Line linhaAmarela = {"Linha Amarela", {hospitalPediatrico, lojaCidadao, portagem, quintaFonte, sobralCeira}, 5, NULL};
    struct Line linhaCiano = {"Linha Ciano", {santaApolonia, coimbraB, lojaCidadao}, 3, NULL};
    struct Line linhaCinzenta = {"Linha Cinzenta", {coimbra, portagem}, 2, NULL};
    struct Line linhaRosa = {"Linha Rosa", {condeixaNova, sobralCeira}, 2, NULL};
    struct Line linhaVerdeEscuro = {"Linha Verde Escuro", {sobralCeira, mirandaCorvo, lousa, serpins, vilaNovaCeira}, 5, NULL};
