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
  int botDiff[2] = {2, 2};

  int wins[3] = {0};
  int cWinner;
  for(int i = 0; i < N; i++){
    cWinner = playGame(noPlayers, botDiff);
    wins[cWinner]++;
  }
  printWins(wins, "Smart vs Smart");
  exportWins(wins, "Smart vs Smart");

  /* Smart AI vs Random AI */
  // Setting Bot/AI Difficulty
  botDiff[1] = 1;

  for(int i = 0; i < 3; i++) wins[i] = 0;
  for(int i = 0; i < N; i++){
    cWinner = playGame(noPlayers, botDiff);
    wins[cWinner]++;
  }
  printWins(wins, "Smart vs Random");
  exportWins(wins, "Smart vs Random");

  /* Random AI vs Random AI */
  // Setting Bot/AI Difficulty
  botDiff[0] = 1;

  for(int i = 0; i < 3; i++) wins[i] = 0;
  for(int i = 0; i < N; i++){
    cWinner = playGame(noPlayers, botDiff);
    wins[cWinner]++;
  }
  printWins(wins, "Random vs Random");
  exportWins(wins, "Random vs Random");

  return 0;
}
