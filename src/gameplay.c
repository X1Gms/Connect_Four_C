#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/gameplay.h"
#include "../headers/menu.h"
#include "../headers/match_status.h"
#include "../headers/ranking.h"
#include "../headers/save_load.h"

/*

    Jogadas realizadas pelos jogadores

    As jogadas efetuadas pelos jogadores são determinadas pela coluna escolhido pelo jogador

    O símbolo correspondente ao jogador é armazenado na última casa desocupada da coluna

*/

int moves(char board[ROWS][COLS], int coluna, char symbol)
{

    for (int i = ROWS - 1; i >= 0; i--)
    {
        if (board[i][coluna] == ' ')
        {
            board[i][coluna] = symbol;
            return i;
        }
    }
    return -1; // Coluna cheia
}

void playMatch(int mode, char player1[], char player2[])
{
    char board[ROWS][COLS];
    resetBoard(board);

    /* A cada partida é efetuado uma limpeza ao tabuleiro, de modo a não haver
     conflito de dados de jogos anteriores, nomeadamente de jogos por carregar */

    int currentPlayer = 1; // 1 ou 2
    int column;            // Coluna escolhido pelo utilizador
    char symbol;           // Simbolo que identifica o jogador
    int win = 0;           // Variável para verificar o término do jogo como vitória para um dos jogadores

    while (1)
    {
        printBoard(board);
        if (currentPlayer == 1)
        {
            printf("%s (X), escolha uma coluna (1-7) ou 0 para salvar/sair: ", player1);
            // Vez do primeiro jogador
        }
        else
        {
            if (mode == 2)
                printf("%s (O), escolha uma coluna (1-7) ou 0 para salvar/sair: ", player2);
            // Numa partida multiplayer, o segundo jogador tem a oportunidade de efetuar jogadas
            else
                printf("Computador (O) esta jogando...\n");
            // Numa partida singleplayer, a IA efetua jogadas
        }

        if (currentPlayer == 2 && mode == 1)
        {
            /*No caso de ser a vez do computador, gerará um número aleatório
             e mostra a coluna escolhida pelo computador*/
            do
            {
                column = rand() % COLS + 1;
            } while (board[0][column - 1] != ' ');
            printf("Computador escolheu a coluna %d\n", column);
        }
        else
        {
            scanf("%d", &column); // No caso da partida multiplayer, é pedido ao segundo jogador para efetuar a jogada
        }

        if (column == 0)
        {
            MatchState game; // Estrutura para guardar o jogo
            memcpy(game.board, board, sizeof(board));
            /*A função memcpy, permite guardar os dados de forma mais eficiente,
             ao invés de recorrer a um conjunto de iterações, trabalhando diretamente com a memória*/
            game.currentPlayer = currentPlayer; // Armazena o jogador atual
            game.mode = mode;                   // Armazena o modo de jogo atual
            strcpy(game.player1, player1);      // Armazena o nome do jogador 1
            strcpy(game.player2, player2);      // Armazena o nome do jogador 2
            saveMatch(game);                    // Salva a partida
            printf("Partida salva!\n");
            return;
        }

        if (column < 1 || column > COLS)
        {
            printf("Coluna invalida. Tente novamente.\n");
            continue;

            /* O uso da palavra-chave continue permite saltar para a próxima iteração,
             de modo a permitir o jogador a re-efetuar a sua jogada, em caso de erro*/
        }
        // No caso da coluna não existir, informa ao jogador da inexistência da coluna

        column--; // Ajusta para índice 0-base, dado à numeração de indexação na lógica de programação

        symbol = (currentPlayer == 1) ? 'X' : 'O'; // O símbolo correspondente ao jogador é armazenado
        if (board[0][column] != ' ')
        {
            printf("Coluna %d estah cheia. Escolha outra coluna.\n", column + 1);
            continue;
            // No caso da coluna já se encontrar cheia, informará o jogador
        }

        moves(board, column, symbol); // Efetua a jogada
        if (checkWin(board, symbol))
        {
            // Caso haja vitória, é mostrado o tabuleiro uma última vez e é declarado o jogador vencedor
            printBoard(board);
            if (currentPlayer == 1)
                printf("Parabens %s! Voce venceu!\n", player1);
            else
                printf("Parabens %s! Voce venceu!\n", (mode == 2 ? player2 : "Computador"));
            win = 1;
            break;
        }

        /*No caso de haver empate, é mostrado o tabuleiro uma última vez e é declarado empate,
        dado o tabuleiro se encontrar cheio e não haver nenhuma combinação*/

        if (isDraw(board))
        {
            printBoard(board);
            printf("Empate! O tabuleiro estah cheio.\n");
            break;
        }
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }

    /*No caso de ocorrer uma vitória no modo multiplayer,
    atualizará a pontuação do jogador vencedor*/

    if (mode == 2 && win)
    {
        if (currentPlayer == 1)
            updateRanking(player1);
        else
            updateRanking(player2);
    }
}

// Função para iniciar uma partida singleplayer
void singleplayer()
{
    playMatch(1, "Jogador", "Computador");
}

// Função para iniciar uma partida multiplayer, armazenando o nome dos jogadores
void multiplayer()
{
    char player1[50], player2[50];
    printf("Digite o nome do Jogador 1 (X): ");
    scanf("%s", player1);
    printf("Digite o nome do Jogador 2 (O): ");
    scanf("%s", player2);
    playMatch(2, player1, player2);
}
