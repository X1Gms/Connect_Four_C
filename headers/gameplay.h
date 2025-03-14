#ifndef GAMEPLAY_H
#define GAMEPLAY_H

// Inicialização das funções do ficheiro gameplay.c

#include "types.h"

int moves(char board[ROWS][COLS], int coluna, char token);
void play_match(int mode, char player1[], char player2[]);
void singleplayer();
void multiplayer();

#endif
