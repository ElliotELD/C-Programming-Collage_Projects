#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to roll a six-sided die
int rollDie() { return rand() % 6 + 1; }

// Function to print the board
void printBoard(int player1, int player2)
{
    // Logic to print the snake-ladder game board
    // This is one way to print the board.
    for (int i = 100; i >= 1; i--)
    {
        if (i == player1)
            printf("#P1 ");
        else if (i == player2)
            printf("#P2 ");
        else
            printf("%d ", i);

        if (i % 10 == 1)
            printf("\n\n");
    }
    printf("\n");
}

// Function to move the player
int movePlayer(int currentPlayer, int roll)
{
    int newPosition = currentPlayer + roll;
    // Define the positions of snakes and ladders on the board
    int snakesAndLadders[101] = {0};

    // Define the positions of snakes and ladders on the board
    snakesAndLadders[6] = 40;
    snakesAndLadders[23] = -10;
    snakesAndLadders[45] = -7;
    snakesAndLadders[61] = -18;
    snakesAndLadders[65] = -8;
    snakesAndLadders[77] = 5;
    snakesAndLadders[98] = -10;

    int newSquare = newPosition + snakesAndLadders[newPosition];

    if (newSquare > 100)
    {
        return currentPlayer; // Player cannot move beyond square 100
    }

    return newSquare;
}

int main()
{
    srand(time(0)); // Initialize random seed
    int player1 = 0, player2 = 0;
    int currentPlayer = 1;
    int won = 0;

    printf("Snake and Ladder Game\n");

    while (!won)
    {
        printf("\nPlayer %d, press Enter to roll the die...", currentPlayer);
        getchar(); // Wait for the player to press Enter
        int roll = rollDie();
        printf("You rolled a %d.\n", roll);

        if (currentPlayer == 1)
        {
            player1 = movePlayer(player1, roll);
            printf("Player 1 is now at square %d.\n\n", player1);
            if (player1 == 100)
            {
                printf("Player 1 wins!\n");
                won = 1;
            }
        }
        else
        {
            player2 = movePlayer(player2, roll);
            printf("Player 2 is now at square %d.\n\n", player2);
            if (player2 == 100)
            {
                printf("Player 2 wins!\n");
                won = 1;
            }
        }

        // Print the board after each player's turn
        printBoard(player1, player2);

        // Switch to the other player
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }

    return 0;
}
