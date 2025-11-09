#include <stdio.h>
#include <stdlib.h>

char PLAYER = 'X'; // Human (minimizer)
char AI     = 'O'; // Computer (maximizer)
char EMPTY  = ' ';

int min(int a, int b) { return (a < b) ? a : b; }
int max(int a, int b) { return (a > b) ? a : b; }

struct Move { int row, col; };

char board[3][3] = {
    { ' ', ' ', ' ' },
    { ' ', ' ', ' ' },
    { ' ', ' ', ' ' }
};
char box[3][3] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'}
};

int isMovesLeft(char b[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (b[i][j] == EMPTY) return 1;
    return 0;
}
int checkBoxUsed(char b) {
    if (b == EMPTY) return 0;
    else return 1;
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        char b1 = (checkBoxUsed(board[i][0])) ? board[i][0] : box[i][0];
        char b2 = (checkBoxUsed(board[i][1])) ? board[i][1] : box[i][1];
        char b3 = (checkBoxUsed(board[i][2])) ? board[i][2] : box[i][2];
        printf(" %c | %c | %c \n", b1, b2, b3);
        if (i < 2) printf("---+---+---\n");
    }
    printf("\n");
}

struct Move playerInput(int x) {
    struct Move move;
    move.row = (x - 1) / 3; // integer division
    move.col = (x - 1) % 3; // modulo for column
    return move;
}

// +10 if AI wins, -10 if PLAYER wins, 0 otherwise
int evaluateBoard(char b[3][3]) {
    // Check the rows
    for (int r = 0; r < 3; r++) {
        if (b[r][0] != EMPTY && b[r][0] == b[r][1] && b[r][1] == b[r][2])
            return (b[r][0] == AI) ? 10 : -10;
    }
    // Check the columns
    for (int c = 0; c < 3; c++) {
        if (b[0][c] != EMPTY && b[0][c] == b[1][c] && b[1][c] == b[2][c])
            return (b[0][c] == AI) ? 10 : -10;
    }
    // Check the diagonals
    if (b[0][0] != EMPTY && b[0][0] == b[1][1] && b[1][1] == b[2][2])
        return (b[0][0] == AI) ? 10 : -10;
    if (b[0][2] != EMPTY && b[0][2] == b[1][1] && b[1][1] == b[2][0])
        return (b[0][2] == AI) ? 10 : -10;

    return 0;
}

// isMax = 1 for AI, 0 for Player
int minimax(char b[3][3], int depth, int isMax) {
    int score = evaluateBoard(b);

    // Terminal states
    if (score == 10)  return score - depth; // prefer faster wins
    if (score == -10) return score + depth; // prefer slower losses
    if (!isMovesLeft(b)) return 0;

    if (isMax) { // AI's turn (maximize)
        int best = -1000;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (b[i][j] == EMPTY) {
                    b[i][j] = AI;
                    best = max(best, minimax(b, depth + 1, 0));
                    b[i][j] = EMPTY;
                }
        return best;
    } else { // Player's turn (minimize)
        int best = 1000;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (b[i][j] == EMPTY) {
                    b[i][j] = PLAYER;
                    best = min(best, minimax(b, depth + 1, 1));
                    b[i][j] = EMPTY;
                }
        return best;
    }
}

struct Move FindBestMove(char b[3][3]) {
    int bestValue = -1000;
    struct Move bestMove = { -1, -1 };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b[i][j] == EMPTY) {
                b[i][j] = AI;
                int moveVal = minimax(b, 0, 0); // next is player (min)
                b[i][j] = EMPTY;

                if (moveVal > bestValue) {
                    bestValue = moveVal;
                    bestMove.row = i;
                    bestMove.col = j;
                }
            }
        }
    }
    return bestMove;
}

char checkWinner() {
    int r = evaluateBoard(board);
    if (r == 10)  return AI;
    if (r == -10) return PLAYER;
    return EMPTY;
}

int main() {
    char currentPlayer;
    //Choosing who is starting first
    int p;
    printf("Who is starting the game?\n");
    printf("Player(1), AI(2)\n");
    scanf("%d", &p);
    if (p == 2) currentPlayer = AI;
    else if (p == 1) currentPlayer = PLAYER;
    else printf("Type 1 or 2");


    for (int turn = 0; turn < 9; turn++) {
        printBoard();

        if (currentPlayer == PLAYER) {
            int x;
            printf("Enter your move: ");
            scanf("%d", &x);
            if (x<0 || x > 9) {
                printf("Invalid move, try again.\n");
                turn--;
                continue;
            }
            struct Move m = playerInput(x);

            if (board[m.row][m.col] != EMPTY) {
                printf("Spot already taken!! Try again.\n");
                turn--;
                continue;
            }

            board[m.row][m.col] = PLAYER;
        } else {
            struct Move n = FindBestMove(board);
            int boxNumber = (n.row * 3) + n.col + 1;
            printf("Computer chooses: %d\n", boxNumber);
            board[n.row][n.col] = AI;
        }

        char w = checkWinner();
        if (w != EMPTY) {
            printBoard();
            if (w == PLAYER) printf("YOU WON!!\n");
            else             printf("AI WON!!\n");
            break;
        }
        if (!isMovesLeft(board)) {
            printBoard();
            printf("IT'S A DRAW!!\n");
            break;
        }

        currentPlayer = (currentPlayer == PLAYER) ? AI : PLAYER;
    }

    printf("\nGAME OVER\n");
    return 0;
}
