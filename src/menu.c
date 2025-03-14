#include <stdio.h>
#include "../headers/menu.h"
#include "../headers/gameplay.h"
#include "../headers/ranking.h"
#include "../headers/save_load.h"

// Função que imprimirá o menu do jogo na aplicação
void showMenu()
{
    printf("\n+-+-+-+-+-+-+ QUATRO EM LINHA +-+-+-+-+-+-+\n\n");
    printf("0 - Sair da Aplicacao\n");
    printf("1 - Jogar Partida Contra IA\n");
    printf("2 - Jogar Partida com Outro Jogador\n");
    printf("3 - Ver Ranking\n");
    printf("4 - Carregar Partida\n");
    printf("\nEscolha uma opcao: ");
}

// Função que reiniciará o tabuleiro
void resetBoard(char board[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            board[i][j] = ' ';
        }
    }
}

// Função que imprimirá o tabuleiro
void printBoard(char board[ROWS][COLS])
{
    int cell_width = 2;
    // Define a largura de cada célula para garantir espaçamento uniforme ao imprimir o tabuleiro

    int board_width = COLS * cell_width;
    // Calcula a largura total do tabuleiro, considerando o número de colunas e o espaço ocupado por cada célula

    printf("\n"); // Adiciona uma linha em branco antes de imprimir o tabuleiro

    for (int j = 0; j < COLS; j++)
    {
        printf("%*d", cell_width, j + 1);
        // Imprime os números das colunas alinhados à direita dentro de uma célula de largura 'cell_width'
    }

    printf("\n"); // Passa para a próxima linha após os números das colunas

    printf("+");
    for (int i = 0; i < board_width; i++)
    {
        printf("-");
    }
    printf("+\n");
    // Desenha a linha superior do tabuleiro

    for (int i = 0; i < ROWS; i++)
    {
        printf("|"); // Inicia a linha com uma borda vertical
        for (int j = 0; j < COLS; j++)
        {
            printf("%*c", cell_width, board[i][j]);
            // Imprime o caractere armazenado na célula atual, respeitando o espaçamento definido por 'cell_width'
        }
        printf("|\n"); // Fecha a linha com outra borda vertical
    }

    printf("+");
    for (int i = 0; i < board_width; i++)
    {
        printf("-");
    }
    printf("+\n");
    // Desenha a linha inferior do tabuleiro
}

void executeOption()
{
    int option;
    do
    {
        showMenu();           // Mostra o menu usado
        scanf("%d", &option); // Lê a opção escolhida pelo o utilizador
        switch (option)
        {
        case 0:
            printf("\n\n+-+-+-+-+-+-+ FIM DO PROGRAMA +-+-+-+-+-+-+\n");
            printf("Realizado Por Goncalo Santos e Diogo Macedo\n\n");
            break;
        case 1:
            singleplayer();
            break;
        case 2:
            multiplayer();
            break;
        case 3:
            printRanking();
            break;
        case 4:
            loadMatch();
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (option != 0);
}
