#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/ranking.h"

RankingEntry *loadRanking(int *count) // Carregar os ranking
{
    FILE *fp = fopen("ranking.txt", "r"); // Abre o arquivo "ranking.txt" em modo leitura.
    if (fp == NULL)                       // Se o arquivo não abrir.
    {
        *count = 0;
        return NULL;
    }
    int capacity = 10;
    int i = 0;
    RankingEntry *rankings = malloc(capacity * sizeof(RankingEntry)); // Aloca a memória do tamanho dos RankingEntry para o vetor rankings.
    if (!rankings)                                                    // Se a alocação falhar.
    {
        printf("Erro de alocacao.\n");
        *count = 0;
        fclose(fp); // Fecha o arquivo "ranking.txt".
        return NULL;
    }
    while (fscanf(fp, "%s %d", rankings[i].name, &rankings[i].wins) == 2) // Enquanto o arquivo é escaneado verificando os nomes e o número de vitórias.
    {
        i++;
        if (i >= capacity) // Se o número de incrementos não for suficiente para a capacidade atual.
        {
            capacity *= 2;                                                           // Duplicação da capacidade.
            RankingEntry *temp = realloc(rankings, capacity * sizeof(RankingEntry)); // Utilização do realocamento para aumentar o vetor em n posições para os jogadores no ranking.
            if (!temp)                                                               // Se a realocação falhar.
            {
                printf("Erro de alocacao.\n");
                break;
            }
            rankings = temp;
        }
    }
    *count = i;
    fclose(fp);      // Fecha o arquivo "ranking.txt".
    return rankings; // Retorna os rankings com a classificação.
}

void saveRanking(RankingEntry *rankings, int count) // Salvar os rankings
{
    FILE *fp = fopen("ranking.txt", "w"); // Abre o arquivo "ranking.txt" em modo escrita.
    if (fp == NULL)                       // Se o arquivo não abrir.
    {
        printf("Erro ao salvar o ranking.\n");
        return;
    }
    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%s %d\n", rankings[i].name, rankings[i].wins); // Para cada entrada, escreve o nome e o número de vitórias no arquivo, cada um em uma nova linha.
    }
    fclose(fp);
}

void updateRanking(const char *nome) // Atualizar os rankings
{
    int count = 0;
    RankingEntry *rankings = loadRanking(&count); // // Carregamento da função "loadRankings" para obter o vetor atual dos rankings.
    if (rankings == NULL)                         // Se os rankings estiverem vazios.
    {
        count = 0;
        rankings = malloc(sizeof(RankingEntry)); // Aloca a memória do tamanho dos RankingEntry para o vetor rankings.
        if (!rankings)                           // Se a alocação falhar.
        {
            printf("Erro de alocacao.\n");
            return;
        }
    }
    int found = 0;
    for (int i = 0; i < count; i++) // Percorre o vetor com os seus valores, procurando valores que tenham o mesmo nome e número de vitórias.
    {
        if (strcmp(rankings[i].name, nome) == 0) // Se encontrar...
        {
            rankings[i].wins++; // Incremento no número de vitórias.
            found = 1;
            break;
        }
    }
    if (!found) // Se não foi encontrado.
    {
        RankingEntry *temp = realloc(rankings, (count + 1) * sizeof(RankingEntry)); // Utilização do realocamento para aumentar o vetor em uma posição para o novo jogador.
        if (!temp)                                                                  // Se a realocação falhar.
        {
            printf("Erro de alocacao.\n");
            free(rankings);
            return;
        }
        rankings = temp;
        strcpy(rankings[count].name, nome); // Preenchimento dos dados do novo jogador no ranking.
        rankings[count].wins = 1;           // Esse novo jogador terá 1 vitória.
        count++;                            // Adicionado mais um jogador, o "count" será incrementado por ter mais um jogador.
    }
    saveRanking(rankings, count); // Carregamento da função "saveRanking" para salvar o novo ranking.
    free(rankings);
}

void printRanking() // Mostrar o ranking.
{
    int count = 0;
    RankingEntry *rankings = loadRanking(&count); // Carregamento do ranking no "loadRanking".
    if (count == 0 || rankings == NULL)           // Se o ranking estiver vazio.
    {
        printf("Ranking vazio.\n");
        return;
    }
    printf("\n----- Ranking de Vitorias -----\n");
    for (int i = 0; i < count; i++)
    {
        printf("%s - %d vitorias\n", rankings[i].name, rankings[i].wins); // Preenchimento das entradas exibidas no "loadRanking" por nome e número de vitórias (formato: "nome : X vitorias").
    }
    printf("-------------------------------\n");
    free(rankings);
}
