#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TicTacToe.h"
#define N 1000

int main(int argc, char *argv[]){
  // Setting up random seed
  srand(clock());
  // Setting up the amount of player
  int noPlayers = 0;

  /* Smart AI vs Smart AI */
  // Setting Bot/AI Difficulty
  /* botDiff[0] sets value for player "x", botDiff[1] sets values for player "o"
    Value of 0 means the AI is playered control, 1 means a Random AI and 2 means Smart AI */
  int botDiff[4][2] = {
    {3, 3},
    {2, 2},
    {2, 1},
    {1, 1}
  };
  char modes[4][20] = {
    "Minimax vs Minimax",
    "Smart vs Smart",
    "Smart vs Random",
    "Random vs Random"
  };

  for(int i = 0; i < 4; i++){
    int wins[3] = {0};
    int cWinner;
    for(int j = 0; j < N; j++){
      cWinner = playGame(noPlayers, botDiff[i]);
      wins[cWinner]++;
    }
    printWins(wins, modes[i]);
    exportWins(wins, modes[i]);
  }

  return 0;
}
