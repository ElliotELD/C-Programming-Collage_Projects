#include <stdio.h>

#define SIZE 3

void initializeBoard(char board[SIZE][SIZE]);
void printBoard(char board[SIZE][SIZE]);
int checkWin(char board[SIZE][SIZE]);
void playerMove(char board[SIZE][SIZE], char player);

int main()
{
    char board[SIZE][SIZE];
    int moves = 0;
    char currentPlayer = 'X';

    initializeBoard(board);

    while (1)
    {
        printBoard(board);
        playerMove(board, currentPlayer);
        moves++;

        if (checkWin(board))
        {
            printBoard(board);
            printf("Player %c wins!\n", currentPlayer);
            break;
        }

        if (moves == SIZE * SIZE)
        {
            printBoard(board);
            printf("It's a draw!\n");
            break;
        }

        // Switch player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    return 0;
}

void initializeBoard(char board[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void printBoard(char board[SIZE][SIZE])
{
    printf("\n");
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1)
                printf("|");
        }
        printf("\n");
        if (i < SIZE - 1)
            printf("---+---+---\n");
    }
    printf("\n");
}

void playerMove(char board[SIZE][SIZE], char player)
{
    int row, col;
    while (1)
    {
        printf("Player %c, enter your move (row and column): ", player);
        scanf("%d %d", &row, &col);
        if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ')
        {
            board[row][col] = player;
            break;
        }
        else
        {
            printf("Invalid move. Try again.\n");
        }
    }
}

int checkWin(char board[SIZE][SIZE])
{
    // Check rows and columns
    for (int i = 0; i < SIZE; i++)
    {
        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') ||
            (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' '))
        {
            return 1;
        }
    }

    // Check diagonals
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' '))
    {
        return 1;
    }

    return 0;
}
