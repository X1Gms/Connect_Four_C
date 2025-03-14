#include "../headers/match_status.h"

int checkWin(char board[ROWS][COLS], char token)
{
    /* Horizontal */
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j <= COLS - 4; j++)
        {
            if (board[i][j] == token &&
                board[i][j + 1] == token &&
                board[i][j + 2] == token &&
                board[i][j + 3] == token) // Se o tabuleiro tiver 4 tokens na horizontal.
            {
                return 1; // Termina o jogo em vitória.
            }
        }
    }
    /* Vertical */
    for (int i = 0; i <= ROWS - 4; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (board[i][j] == token &&
                board[i + 1][j] == token &&
                board[i + 2][j] == token &&
                board[i + 3][j] == token) // Se o tabuleiro tiver 4 tokens na vertical.
            {
                return 1; // Termina o jogo em vitória.
            }
        }
    }
    /* Diagonal (para baixo à direita) */
    for (int i = 0; i <= ROWS - 4; i++)
    {
        for (int j = 0; j <= COLS - 4; j++)
        {
            if (board[i][j] == token &&
                board[i + 1][j + 1] == token &&
                board[i + 2][j + 2] == token &&
                board[i + 3][j + 3] == token) // Se o tabuleiro tiver 4 tokens na diagonal para baixo e para a direita.
            {
                return 1; // Termina o jogo em vitória.
            }
        }
    }
    /* Diagonal (para baixo à esquerda) */
    for (int i = 0; i <= ROWS - 4; i++)
    {
        for (int j = 3; j < COLS; j++)
        {
            if (board[i][j] == token &&
                board[i + 1][j - 1] == token &&
                board[i + 2][j - 2] == token &&
                board[i + 3][j - 3] == token) // Se o tabuleiro tiver 4 tokens na diagonal para baixo e para a esquerda.
            {
                return 1; // Termina o jogo em vitória.
            }
        }
    }
    return 0; // Continua o jogo.
}

int isDraw(char board[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (board[i][j] == ' ')
                return 0; // Continua o jogo.
        }
    }
    return 1; // Termina o jogo em empate.
}
