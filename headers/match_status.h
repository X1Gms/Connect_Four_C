#ifndef MATCH_STATUS_H
#define MATCH_STATUS_H

// Inicialização das funções do ficheiro match_status.c

#include "types.h"

int checkWin(char board[ROWS][COLS], char token);
int isDraw(char board[ROWS][COLS]);

#endif
