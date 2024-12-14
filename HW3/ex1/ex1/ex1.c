#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX_SIZE 10

void create_board(char board[][2 * MAX_SIZE], int N) {
	/* Assign to board: Nx2N nested array. (no '\n' in assignment) */
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 2*N; j++) {
			if (0 == j % 2) {
				board[i][j] = '_';
			}
			else {
				board[i][j] = (j == 2 * N - 1) ? '\0' : ' ';
			}
		}
	}
}
void print_board(const char board[][2 * MAX_SIZE],const int N) {
	/* Prints board. */
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 2 * N; j++) {
			printf("%c", board[i][j]);
		}
		printf("\n");
	}
}
void update_board(char board[][2 * MAX_SIZE], const char* current_mark) {
	/*
	1. Ask for Indices, and check if valid.
	2. Sepreates to row and column.
	3. Updates board in the location, with the current mark.
	*/
}
int check_won(const char board[][2 * MAX_SIZE], const char* current_mark) {
	/* return 1 if full row/coloumn/diagnol with mark*/
	return 0;
}
void pass_turn(char* current_player) {
	/* Alternate current player and mark*/
}

/* Testing #1
int main() {
	char board[MAX_SIZE][2 * MAX_SIZE];
	create_board(board, 8);
	return 0;
		
}
*/

int main() {
	char board[MAX_SIZE][2 * MAX_SIZE];
	const char player_1 = 1, mark_1 = 'X', player_2 = 2, mark_2 = 'O';
	const char* current_player = &player_1;
	const char* current_mark = &mark_1;  // const char* - pointer to a constant char (the pointer itself can point on another char const)
	int N, won = 0, turn_num = 0;
	printf("Please enter the board size N [1-10]:\n");
	scanf("%d", &N);
	create_board(board, N);
	printf("Welcome to %dx%d Tic-Tac-Toe:\n", N, N);
	print_board(board, N);
	do
	{
		turn_num++;
		printf("Player %d, please insert your move :\n", *current_player);
		update_board(board, current_mark);
		print_board(board, N);
		won = check_won(board, current_mark);
		if (!won) {
			pass_turn(current_player);
		}
	} while (!won && turn_num < N * N); // max iterations turn num = N^2
	if (won) {
		printf("Player _ is the winner!\n", *current_player);
	}
	printf("There is a Tie!\n");
	return 0;
}
