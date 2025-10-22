#include <stdio.h>

char board[3][3];
char current_marker;
int current_row, current_col;

void resetBoard() {
    for (int i = 0, n=1; i < 3; i++) {
        for (int j = 0; j < 3; j++, n++) {
            board[i][j] = '0' + n;
        }
    }
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c ", board[i][0], board[i][1], board[i][2]);
        if (i != 2)
            printf("\n---|---|---\n");
    }
    printf("\n");
}

int placeMarker(int slot, char marker) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;
    if (board[row][col] == 'X' || board[row][col] == 'O')
        return 0; // spot already taken
    board[row][col] = marker;
    current_row = row;
    current_col = col;
    return 1;
}

int checkWin() {
    char m = current_marker;
    // Check row and column
    if (board[current_row][0] == m && board[current_row][1] == m && board[current_row][2] == m) return 1;
    if (board[0][current_col] == m && board[1][current_col] == m && board[2][current_col] == m) return 1;
    // Diagonals
    if (current_row == current_col)
        if (board[0][0] == m && board[1][1] == m && board[2][2] == m) return 1;
    if (current_row + current_col == 2)
        if (board[0][2] == m && board[1][1] == m && board[2][0] == m) return 1;
    return 0;
}

int checkDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O') return 0;
    return 1;
}

void playGame() {
    int slot, valid;
    char markers[2] = {'X', 'O'};
    int player = 0;
    resetBoard();
    printBoard();
    while (1) {
        printf("Player %d [%c], choose your slot (1-9): ", player + 1, markers[player]);
        scanf("%d", &slot);
        valid = placeMarker(slot, markers[player]);
        if (!valid) {
            printf("Invalid move! Try again.\n");
            continue;
        }
        printBoard();
        current_marker = markers[player];
        if (checkWin()) {
            printf("Player %d [%c] wins!\n", player + 1, markers[player]);
            break;
        }
        if (checkDraw()) {
            printf("It's a draw!\n");
            break;
        }
        player = 1 - player; // Switch player
    }
}

int main() {
    char ch;
    do {
        playGame();
        printf("Play again? (y/n): ");
        scanf(" %c", &ch);
    } while (ch == 'y' || ch == 'Y');
    return 0;
}
