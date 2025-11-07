#include <stdio.h>
#include <stdlib.h>
#include <time.h>


char PLAYER = 'X';
char COMPUTER = 'O';
char EMPTY = ' ';

char board[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '},
};

void printBoard() {
    //printf("   |   |   \n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("___________\n");
    //printf("   |   |   \n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("___________\n");
    //printf("   |   |   \n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

int generateRandom() {
    int randomNumber = rand() % 3;
    return randomNumber;
}
char checkWinner() {
    for (int i = 0; i < 3; i++) {
        //check the winner horizontally
        if (board[i][0] != EMPTY && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];
        //check the winner vertically
        if (board[0][i] != EMPTY && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i];
    }
    //check the winner diagonally
    if (board[0][0] != EMPTY && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];
    if (board[0][2] != EMPTY && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2];
    return EMPTY;
}


int main () {
    srand(time(NULL));
    char currentPlayer = PLAYER;
    short row, column;
    row = -1;
    column = -1;
    for (int i = 0; i < 9; i++) {
        printBoard();
        // If its players  turn:
        if (currentPlayer == PLAYER) {
            printf("------------Enter your chosen position(row column): \n");
            scanf("%hd %hd", &row, &column);
            row--;
            column--;
            // check if row and column input are available
            if (row < 0 || row > 2 || column < 0 || column > 2) {
                printf("------------Invalid output!! Try again!------------\n");
                i--;
                continue;
            }
            // If the box is empty:
            if (board[row][column] == EMPTY) {
                board[row][column] = PLAYER;
            }
            // If the box is not empty
            else {
                printf("------------This spot is taken. Try again!!!------------\n");
                i--;
                continue;
            }

            if (checkWinner() == PLAYER) {
                printBoard();
                printf("------------YOU WON!!!------------\n");
                break;
            }

            currentPlayer = COMPUTER;
        } else if (currentPlayer == COMPUTER) {
            int a, b;
                do {
                    a = generateRandom();
                    b = generateRandom();
                } while (board[a][b] != EMPTY);
                printf("Computer chose is: %d %d \n", a+1, b+1);
                board[a][b] = COMPUTER;
            if (checkWinner() == COMPUTER) {
                printBoard();
                printf("------------YOU LOSE------------\n");
                printf("------------COMPUTER WIN!!!------------\n");
                break;
            }
            currentPlayer = PLAYER;
        }
        if (i == 8 && checkWinner() == EMPTY) {
            printBoard();
            printf("------------IT'S A DRAW!------------\n");
        }
    }
    printf("\n\n !!!!!!!!!!!!!!!!GAME OVER!!!!!!!!!!!!!!!!\n");

    return 0;
};