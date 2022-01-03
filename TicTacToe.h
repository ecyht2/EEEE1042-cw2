#ifndef TICTACTOE_H_
#define TICTACTOE_H_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int check_win(int board[]);
char player_symbol(int playerNo);
int ask_no_players();
int ask_bot_diff(int botNo);
int minimax(int board[], int player, int nFreeSpace, int freeSpace[], int * choice);
int bot_choice(int board[], int botDiff, int player);
int ask_placement(int player, int botDiff, int noPlayers, int board[]);
void print_board(int board[]);
int playGame(int noPlayers, int botDiff[]);
void printWins(int wins[], char *message);
void exportWins(int wins[], char *message);

#endif // TIC-TAC-TOE_H_
