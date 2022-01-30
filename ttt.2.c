#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TicTacToe.h"

int main(int argc, char *argv[]){
  // Setting up random seed
  srand(clock());
  // Setting up the amount of player
  int noPlayers = 1;
  // Setting Bot/AI Difficulty
  /* botDiff[0] sets value for player "x", botDiff[1] sets values for player "o"
    Value of 0 means the AI is playered control, 1 means a Random AI and 2 means Smart AI */
  int botDiff[2] = {0};
  botDiff[1] = ask_bot_diff(2);

  playGame(noPlayers, botDiff);

  return 0;
}
