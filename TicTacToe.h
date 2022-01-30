#ifndef TICTACTOE_H_
#define TICTACTOE_H_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int check_win(int board[]);
void switch_player(int *player);
char player_symbol(int playerNo);
int ask_no_players(void);
int ask_bot_diff(int botNo);
void copy_board(int inBoard[], int outBoard[]);
int bot_choice(int board[], int botDiff, int player);
int bot_logic(int board[], int botDiff[], int noPlayers, int player);
int ask_placement(int player, int botDiff[], int noPlayers, int board[]);
void print_board(int board[]);
void print_winner(int winner);
int playGame(int noPlayers, int botDiff[]);
void printWins(int wins[], char *message);
void exportWins(int wins[], char *message);
void print_error();

#endif // TIC-TAC-TOE_H_
