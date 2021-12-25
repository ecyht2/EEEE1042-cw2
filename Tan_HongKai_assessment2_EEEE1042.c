#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TicTacToe.h"

int main(){
  /* The program will first ask you the amount of players that are playing, 2 = two player mode, 1 = single player mode and 0 = AI vs AI */
  /* If the amount of player chosen is less than 2, the program will ask you what the difficulty of AI you want to be. 1 = the AI will place randomly and 2 = will be the smart AI which has some logic */

  // Setting up random seed
  srand(clock());
  // Asking for how many players are playing
  int noPlayers = ask_no_players();

  // Asking for the difficulty of the bot
  /* botDiff[0] sets value for player "x", botDiff[1] sets values for player "o"
    Value of 0 means the AI is playered control, 1 means a Random AI and 2 means Smart AI */
  int botDiff[2] = {0};

  if(noPlayers == 1){
    botDiff[1] = ask_bot_diff(2);
  } else if(noPlayers == 0){
    botDiff[0] = ask_bot_diff(1);
    botDiff[1] = ask_bot_diff(2);
  }

  playGame(noPlayers, botDiff);

  return 0;
}
