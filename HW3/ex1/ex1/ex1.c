#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_SIZE 10

void create_board(char board[][MAX_SIZE], int N) {
    // Initialize the board with empty spaces ('_')
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = '_';
        }
    }
}

void print_board(char board[][MAX_SIZE], int N) {
    // Print the current board state with spaces
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int validate_indices(int row, int col, int N, char board[][MAX_SIZE]) {
    // Check if is this a valid move
    if (row > N || row < 0 || col > N && col < 0 || board[row][col] != '_') {
        return 0; // invalid
    }
    return 1;
}

void update_board(char board[][MAX_SIZE], char current_mark, int N) {
    int row, col;

    while (1) {
        printf("please insert your move:\n");
        if (scanf("%d,%d", &row, &col) != 2) {
            while (getchar() != '\n');
            printf("Invalid indices, please choose your move again:\n");
            continue;
        }
        row--; col--; // Convert to 0-based index

        if (validate_indices(row, col, N, board)) {
            board[row][col] = current_mark;
            break;
        }
        else {
            printf("Invalid indices, please choose your move again:\n");
        }
    }
}

int check_won(char board[][MAX_SIZE], char current_mark, int N) {

    for (int i = 0; i < N; i++) {
        int row_win = 1, col_win = 1;
        for (int j = 0; j < N; j++) {
            if (board[i][j] != current_mark) row_win = 0;
            if (board[j][i] != current_mark) col_win = 0;
        }
        if (row_win || col_win) return 1;
    }

    int diag1_win = 1, diag2_win = 1;
    for (int i = 0; i < N; i++) {
        if (board[i][i] != current_mark) diag1_win = 0;
        if (board[i][N - 1 - i] != current_mark) diag2_win = 0;
    }
    if (diag1_win || diag2_win) return 1;

    return 0; // No winner
}

void pass_turn(char* current_player) {
    *current_player = (*current_player == '1') ? '2' : '1';
}

int main() {
    char board[MAX_SIZE][MAX_SIZE];
    int N, turn_num = 0, max_turns;
    char player_1_mark = 'X', player_2_mark = 'O', current_player = '1';
    char current_mark;

    printf("Please enter the board size N [1-10]:\n");
    scanf("%d", &N);

    max_turns = N * N;

    create_board(board, N);
    printf("Welcome to %dx%d Tic-Tac-Toe:\n", N, N);
    print_board(board, N);

    while (turn_num < max_turns) {
        current_mark = (current_player == '1') ? player_1_mark : player_2_mark;
        printf("Player %c, ", current_player); // part one in the sentence

        update_board(board, current_mark, N);
        print_board(board, N);

        if (check_won(board, current_mark, N)) {
            printf("Player %c is the winner!\n", current_player);
            return 0;
        }

        turn_num++;
        pass_turn(&current_player);
    }

    printf("There is a Tie!\n");
    return 0;
}
