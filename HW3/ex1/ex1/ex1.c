#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX_SIZE 10

void create_board(char board[][2 * MAX_SIZE], const int N) {
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
void print_board(const char board[][2 * MAX_SIZE], const int N) {
	/* Prints board. */
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 2 * N; j++) {
			printf("%c", board[i][j]);
		}
		printf("\n");
	}
}
void update_board(char board[][2 * MAX_SIZE], const char* current_mark, const int N) {
	/*
	1. Ask for Indices,cleans and assign : [ *(idx) -> row_idx , *(idx+1) -> column_idx].
	2. check if valid
	3. Updates board in the location, with the current mark.
	*/
	
	// ask for indices
	int idx[2] = { 0 };
	scanf(" %d , %d", &idx[0], &idx[1]);


	// check if valid -- if not scanf again (try do-while)


	// if valid
	 board[idx[0] - 1][2 * (idx[1] - 1)] = *current_mark;
}
int check_won(const char board[][2 * MAX_SIZE], const char* current_mark, const int N) {
	// check rows win or columns or diagonal win
	int row_win = 1, column_win = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] != *current_mark) {
				row_win = 0;
			}
			if (board[j][i] != *current_mark) {
				column_win = 0;
			}
		}
	}
	int diag1_win = 1, diag2_win = 1;
	for (int i = 0; i < N; i++) {
		if (board[i][i] != *current_mark) {
			diag1_win = 0;
		}
		if (board[i][N - 1 - i] != *current_mark) {
			diag2_win = 0;
		}
	}
	if (row_win || column_win || diag1_win || diag2_win) {
		return 1;
	}
	return 0;
}
void pass_turn( char* current_player,  char player_1,  char player_2,char* current_mark, char mark_1, char mark_2 ) {
	if(*current_player == '1') {
		current_player = '2';
		current_mark = 'O';
	}
	current_player ='1';
	current_mark = 'X';
	}


//test main
/*
int main() {

	int* idx;
	idx = get_idx();
	printf("%d %d", *idx, *(idx + 1));
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
		update_board(board, current_mark, N);
		print_board(board, N);
		won = check_won(board, current_mark ,N);
		if (!won) {
			pass_turn(current_player, player_1,player_2,current_mark,mark_1,mark_2);
		}
	} while (!won && turn_num < N * N); // max iterations turn num = N^2
	if (won) {
		printf("Player %d is the winner!\n", *current_player);
		return 0;
	}
	printf("There is a Tie!\n");
	return 0;
}
