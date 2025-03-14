#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/save_load.h"
#include "../headers/menu.h"
#include "../headers/gameplay.h"
#include "../headers/match_status.h"
#include "../headers/ranking.h"

void saveMatch(MatchState game)
{
    FILE *fp = fopen("savegame.dat", "wb");
    /*
        Ponteiro criado para salvar o arquivo e guardá-lo em binário
        para garantir a integridade dos dados guardados
    */
    if (fp == NULL)
    {
        printf("Erro ao salvar a partida.\n");
        return;
    }
    fwrite(&game, sizeof(MatchState), 1, fp); // Guarda os dados do jogo, guardando a estrutura indicada
    fclose(fp);                               // Fecha o ficheiro
}

void resumeMatch(MatchState game)
{
    int currentPlayer = game.currentPlayer;
    int column;  // Coluna escolhido pelo utilizador
    char symbol; // Simbolo que identifica o jogador
    int win = 0; // Variável para verificar o término do jogo como vitória para um dos jogadores
    while (1)
    {
        printBoard(game.board);
        if (currentPlayer == 1)
            printf("%s (X), escolha uma coluna (1-7) ou 0 para salvar/sair: ", game.player1);
        // Vez do primeiro jogador
        else
        {
            if (game.mode == 2)
                printf("%s (O), escolha uma coluna (1-7) ou 0 para salvar/sair: ", game.player2);
            // Numa partida multiplayer, o segundo jogador tem a oportunidade de efetuar jogadas
            else
                printf("Computador (O) esta jogando...\n");
            // Numa partida singleplayer, a IA efetua jogadas
        }

        if (currentPlayer == 2 && game.mode == 1)
        {
            /*No caso de ser a vez do computador, gerará um número aleatório
             e mostra a coluna escolhida pelo computador*/
            do
            {
                column = rand() % COLS + 1;
            } while (game.board[0][column - 1] != ' ');
            printf("Computador escolheu a coluna %d\n", column);
        }
        else
        {
            scanf("%d", &column); // No caso da partida multiplayer, é pedido ao segundo jogador para efetuar a jogada
        }

        if (column == 0)
        {
            /*Uma vez que os dados foram armazenados numa estrutura anteriormente, não é necessário
             criar novamente uma nova instância do Estado da Partida*/
            game.currentPlayer = currentPlayer; // Armazena o jogador atual
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
        if (game.board[0][column] != ' ')
        {
            printf("Coluna %d estah cheia. Escolha outra coluna.\n", column + 1);
            continue;
            // No caso da coluna já se encontrar cheia, informará o jogador
        }
        moves(game.board, column, symbol); // Efetua a jogada
        if (checkWin(game.board, symbol))
        {
            // Caso haja vitória, é mostrado o tabuleiro uma última vez e é declarado o jogador vencedor
            printBoard(game.board);
            if (currentPlayer == 1)
                printf("Parabens %s! Voce venceu!\n", game.player1);
            else
                printf("Parabens %s! Voce venceu!\n", (game.mode == 2 ? game.player2 : "Computador"));
            win = 1;
            break;
        }

        /*No caso de haver empate, é mostrado o tabuleiro uma última vez e é declarado empate,
        dado o tabuleiro se encontrar cheio e não haver nenhuma combinação*/

        if (isDraw(game.board))
        {
            printBoard(game.board);
            printf("Empate! O tabuleiro estah cheio.\n");
            break;
        }
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }

    /*No caso de ocorrer uma vitória no modo multiplayer,
    atualizará a pontuação do jogador vencedor*/
    if (game.mode == 2 && win)
    {
        if (currentPlayer == 1)
            updateRanking(game.player1);
        else
            updateRanking(game.player2);
    }
}

void loadMatch()
{
    FILE *fp = fopen("savegame.dat", "rb"); // Ponteiro criado para ler o arquivo em formato binário
    if (fp == NULL)                         // Se nenhuma partida salva foi encontrada
    {
        printf("Nenhuma partida salva encontrada.\n");
        return;
    }
    MatchState game;                         // Criação de um estado de partida
    fread(&game, sizeof(MatchState), 1, fp); // Carregamento dos dados do ficheiro na estrutura
    fclose(fp);                              // Fechar ficheiro
    resumeMatch(game);                       // Continuar a Partida
}
