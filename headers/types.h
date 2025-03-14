/*------------------------ TIPOS ------------------------*/

/* Neste código pode se encontrar todas as constantes e as structs utilizadas no programa */

/* Cada cabeçalho (.h) foi usado, de modo a iniciar todas as funções em todos os ficheiros executáveis */

#ifndef TYPES_H
#define TYPES_H

#define ROWS 6
#define COLS 7

typedef struct
{
    char board[ROWS][COLS];
    int currentPlayer; // 1 ou 2
    int mode;          // 1: Jogador vs IA, 2: Dois jogadores
    char player1[50];
    char player2[50];
} MatchState;

typedef struct
{
    char name[50];
    int wins;
} RankingEntry;

#endif
