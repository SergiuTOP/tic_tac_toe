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

int isMovesLeft(char b[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (b[i][j] == EMPTY) return 1;
    return 0;
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        if (i < 2) printf("---+---+---\n");
    }
    printf("\n");
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
    char currentPlayer = PLAYER;
    int row, col;

    for (int turn = 0; turn < 9; turn++) {
        printBoard();

        if (currentPlayer == PLAYER) {
            printf("Enter row col (1-3 1-3): ");
            if (scanf("%d %d", &row, &col) != 2) return 0;
            row--; col--;
            if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != EMPTY) {
                printf("Invalid move, try again.\n");
                turn--;
                continue;
            }
            board[row][col] = PLAYER;
        } else {
            struct Move m = FindBestMove(board);
            printf("Computer chooses: %d %d\n", m.row + 1, m.col + 1);
            board[m.row][m.col] = AI;
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
