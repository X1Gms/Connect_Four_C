#ifndef RANKING_H
#define RANKING_H

#include "types.h"

// Inicialização das funções do ficheiro ranking.c

RankingEntry *loadRanking(int *count);
void saveRanking(RankingEntry *rankings, int count);
void updateRanking(const char *nome);
void printRanking();

#endif
