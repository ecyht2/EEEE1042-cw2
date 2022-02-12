#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "TicTacToe.h"
#include "Gui.h"

int main(int argc, char *argv[]){
  /* The program will first ask you the amount of players that are playing, 2 = two player mode, 1 = single player mode and 0 = AI vs AI */
  /* If the amount of player chosen is less than 2, the program will ask you what the difficulty of AI you want to be. 1 = the AI will place randomly and 2 = will be the smart AI which has some logic */

  // Setting up random seed
  srand(clock());

  // Setting up needed variables
  int noPlayers = -1;
  int botDiff[2] = {-1, -1};

  if(argc < 2){ // If no arguments are passed in
    // Asking for how many players are playing
    noPlayers = ask_no_players();

    // Asking for the difficulty of the bot
    /* botDiff[0] sets value for player "x", botDiff[1] sets values for player "o"
      Value of 0 means the AI is playered control, 1 means a Random AI and 2 means Smart AI */
    if(noPlayers == 1){
      botDiff[1] = ask_bot_diff(2);
    } else if(noPlayers == 0){
      botDiff[0] = ask_bot_diff(1);
      botDiff[1] = ask_bot_diff(2);
    }
    // Starting the game
    playGame(noPlayers, botDiff);
  } else if(argc == 2){ // If --gui is passed in
    if(strcmp(argv[1], "--gui") == 0){ // Checking if --gui is passed
      playGameGUI(argc, argv, noPlayers, botDiff); // Playing Game with GUI
    } else{
      // Printing Error
      print_error();
      return 1;
    }
  } else if(argc == 4 || argc == 5){ //
    // Storing the argmuments into variables
    noPlayers = atoi(argv[1]);
    botDiff[0] = atoi(argv[2]);
    botDiff[1] = atoi(argv[3]);

    // Checking if a Valid noPlayers were passed
    if(noPlayers < 0 || noPlayers > 2){
      fprintf(stderr, "Invalid Numbers of Players Try Again");
      return 1;
    }
    // Checking if a Valid botDiffs were passed
    if(noPlayers < 2 && (botDiff[0] < 1 || botDiff[1] < 1 || botDiff[0] > 3 || botDiff[1] > 3)){
      fprintf(stderr, "Invalid Bot Difficulty Try Again");
      return 1;
    }


    if(argc == 4){
      // If 4 arguments were passed
      playGame(noPlayers, botDiff);
    } else {
      // If 5 arguments were passed
      if(strcmp(argv[4], "--gui") == 0){ // Checking if --gui is passed
        playGameGUI(argc, argv, noPlayers, botDiff); // Playing Game with GUI
      } else{
        // Printing Error
        print_error();
        return 1;
      }
    }
  } else{
    print_error();
  }

  return 0;
}
