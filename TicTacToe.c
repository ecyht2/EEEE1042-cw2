#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TicTacToe.h"

int check_win(int board[]){
  const int winCon[][3] = {
    //Horizontal Win Conditions
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 8},
    //Vertical Win Conditions
    {0, 3, 6},
    {1, 4, 7},
    {2, 5, 8},
    //Diaganol Win Conditions
    {0, 4, 8},
    {2, 4, 6}
  };

  // Setting up the number of win Conditions
  int noWinCon = sizeof(winCon)/sizeof(int)/3;

  //Looping over all the win conditions
  for(int i = 0; i < noWinCon; i++){
    // Checking if the win condition is met
    if(board[winCon[i][0]] == board[winCon[i][1]] && board[winCon[i][2]] == board[winCon[i][1]] && board[winCon[i][0]] != 0)
      // Returning the winner if the the win condition is met
      return board[winCon[i][0]];
  }

  // Returing that no one has won yet
  return 0;
}

void switch_player(int *player){
  *player = *player % 2 + 1;
}

char player_symbol(int playerNo){
  /* This function returns the symbol of the player number */
  char player;

  // Logic to tell which symbol the playerNo corresponds to
  if(playerNo == 1) player = 'x';
  else player = 'o';

  //Returning the player symbol
  return player;
}

int ask_no_players(){
  // Setting initial Variables
  int nPlayers = -1;

  //Asking for the number of players
  do{
    printf("Available Choices: 0, 1, 2\n");
    printf("How many players are playing: ");
    if(scanf("%d", &nPlayers) == 0) scanf("%*s");
    printf("\n");

    if(nPlayers < 0 || nPlayers > 2){
      printf("Invalid Number of Players, please try again\n");
    }
  } while(nPlayers < 0 || nPlayers > 2);

  // Returning the number of players
  return nPlayers;
}

int ask_bot_diff(int botNo){
  // Setting up initial Values
  int bDiff = -1;
  char player;

  // Determining the symbol of the bot
  player = player_symbol(botNo);

  do{
    printf("Available Choices: 1, 2, 3\n");
    printf("What difficulty do you want bot %c to be: ", player);
    if(scanf("%d", &bDiff) == 0) scanf("%*s");
    printf("\n");

    if(bDiff < 1 || bDiff > 3){
      printf("Invalid Bot/AI difficulty, please try again\n");
    }
  } while(bDiff < 1 || bDiff > 3);

  // Returning the Bot difficulty
  return bDiff;
}

int minimax(int board[], int player, int nFreeSpace, int freeSpace[], int *choice){
  // Checking current game state
  int winner = check_win(board);
  // Returns a value if there aren't anymore free spaces
  if(nFreeSpace == 0 || winner > 0){
    // Returns 0 if a tie
    if(winner == 0)
      return 0;
    // Returns 10 if player won
    else if(winner == player)
      return 10;
    // Returns -10 if player lost
    else return -10;
  }

  // Setting up who is the next player
  int nextPlayer = player;
  if(player == 1)
    nextPlayer = 2;
  else nextPlayer = 1;

  // Setting up variables
  int newFreeSpace[nFreeSpace - 1];
  int dummyChoice;
  int cMax = -1000;

  // Looping over all available choices
  for(int i = 0; i < nFreeSpace; i++){
    // Making a temporary choice
    int tmpChoice = freeSpace[i];
    board[tmpChoice] = player;

    // Creating the left over free spaces
    for(int j = 0; j < nFreeSpace; j++){
      int remove = 0;
      if(j >= i){
        remove = 1;
        if(j == i) continue;
      }
      newFreeSpace[j - remove] = freeSpace[j];
    }

    // Going over all possible choices
    int value = -minimax(board, nextPlayer, nFreeSpace - 1, newFreeSpace, &dummyChoice);
    // If the current choice have a higher score, use the current choice
    if(value > cMax){
      *choice = tmpChoice;
      cMax = value;
    }

    // Undoing the temporary choice
    board[tmpChoice] = 0;
  }

  return cMax;
}

int bot_choice(int board[], int botDiff, int player){
  //Initializing needed variables
  int *freeSpots = NULL;
  int counter = 0;
  int choice;

  for(int i = 0; i < 9; i++){
    if(board[i] == 0){
      // Resizing the amount of freeSpots in on the board
      counter++;
      freeSpots = (int *) realloc(freeSpots, counter*sizeof(int));
      //Adding the index of the free spot to the array
      freeSpots[counter - 1] = i;
    }
  }

  switch(botDiff){
    case 1:
      //Returning a random element from the available spot if the difficulty is 1
      choice = freeSpots[rand() % counter];
      //Freeing memory from freeSpots
      free(freeSpots);
      //returning a random choice
      return choice;
      break;
    case 2:
      /*
      Uncomment to make the bot to always chose the middle spot if empty making the bot "even smarter"
      if(board[4] == 0) return 4;
      */

      // Checking if any of the choices will result in the bot's victory
      for(int i = 0; i < counter; i++){
        // Testing Placments
        choice = freeSpots[i];
        board[choice] = player;
        // Checking winner
        int winner = check_win(board);
        // Undo Placment
        board[choice] = 0;
        //Returning the choice if it results in a win
        if(winner == player){
          //Freeing memory from freeSpots
          free(freeSpots);
          return choice;
        }
      }

      //Setting so that it checks if any of the choices will result in the enemy's win
      if(player == 1) player = 2;
      else if(player == 2) player = 1;

      // Checking if any of the choices will result in the enemy's victory
      for(int i = 0; i < counter; i++){
        // Testing Placments
        choice = freeSpots[i];
        board[choice] = player;
        // Checking winner
        int winner = check_win(board);
        // Undo Placment
        board[choice] = 0;
        //Returning the choice if it results in an enemy win
        if(winner == player){
          //Freeing memory from freeSpots
          free(freeSpots);
          return choice;
        }
      }

      // Making a random choice otherwise
      choice = freeSpots[rand() % counter];
      //Freeing memory from freeSpots
      free(freeSpots);
      // Returning a random choice otherwise
      return choice;
      break;
    case 3:
      minimax(board, player, counter, freeSpots, &choice);
      free(freeSpots);
      return choice;
      break;
    default:
      free(freeSpots);
      break;
  }

  return 0;
}

int bot_logic(int board[], int botDiff[], int noPlayers, int player){
  char playerSym = player_symbol(player);
  int choice = -1;

  // If there is no human players the choice would be chosen by an AI based on it's difficulty
  if(noPlayers == 0){
    // Finding and ruturning the bot choice
    choice = bot_choice(board, botDiff[player - 1], player);
    // Printing the choice of the bot
    printf("Bot %c chose spot number %d\n", playerSym, choice + 1);
    return choice;
  } else if(noPlayers == 1 && playerSym == 'o'){ //If the number players is one and the symbol is 'o' let an AI decide the choice
    // Finding and ruturning the bot choice
    choice = bot_choice(board, botDiff[player - 1], player);
    // Printing the choice of the bot
    printf("Bot %c chose spot number %d\n", playerSym, choice + 1);
    return choice;
  }

  return -1;
}

int ask_placement(int player, int botDiff[], int noPlayers, int board[]){
  // Setting up initial Values
  char playerSym = player_symbol(player);
  int choice = -1;

  choice = bot_logic(board, botDiff, noPlayers, player);
  if(choice != -1) return choice;

  do{
    // Asking where the player wants to place their symbol
    printf("Player %c turn, please select a position: ", playerSym);
    if(scanf("%d", &choice) == 0) scanf("%*s");
    printf("\n");

    // Printing that the placement chosen is invalid (Chosen)
    if(!(choice >= 1 && choice <= 9) || board[choice - 1] != 0){
      printf("Invalid Position please try again.\n");
    }
  } while(!(choice >= 1 && choice <= 9) || board[choice - 1] != 0); //Reasking the player if it is an invalid option

  // returning the choice
  return choice - 1;
}

void print_board(int board[]){
  // Looping over Rows
  for(int i = 0; i < 3; i++){
    // Looping over Colummns
    for(int j = 0; j < 3; j++){
      switch(board[i*3 + j]){
        // Print a space if it is not chosen by anyone
        case 0:
          printf(" %d ", i*3 + j + 1);
          break;
        // Print a "x" if player "x" chose the spot
        case 1:
          printf(" x ");
          break;
        // Print a "o" if player "o" chose the spot
        case 2:
          printf(" o ");
          break;
        // Print a space other wise
        default:
          printf("   ");
          break;
      }
      // Printing Column Divider
      if(j < 2) printf("|");
    }
    // Printing Row Divider
    if(i < 2) printf("\n---+---+---\n");
  }
  //Printing newline
  printf("\n");
}

void print_winner(int winner){
  char winnerChar = player_symbol(winner);
  if(winner > 0) printf("Player %c won!\n", winnerChar);
  else printf("It is a tie\n");
}

int playGame(int noPlayers, int botDiff[]){
  // Setting up initial values
  int cPlayer = rand() % 2 + 1;
  int cBoard[] = {0, 0, 0,
                  0, 0, 0,
                  0, 0, 0};
  int winner = 0;

  //Printing out the initial board
  print_board(cBoard);
  //Starting the game
  for(int i = 0; i < 9; i++){
    // Asking for the player where they want to place their symbol
    int placement = ask_placement(cPlayer, botDiff, noPlayers, cBoard);
    // Updating the Board
    cBoard[placement] = cPlayer;
    //Printing the Board
    print_board(cBoard);
    // Checking if anyone won the game
    winner = check_win(cBoard);
    if(winner > 0){
      break;
    }
    // Switching to next player
    switch_player(&cPlayer);
  }

  // Printing Winner
  print_winner(winner);

  return winner;
}

void printWins(int wins[], char *message){
  printf("%s\n", message);
  printf("x wins %d amount of times\n", wins[1]);
  printf("x losts %d amount of times\n", wins[2]);
  printf("It is a tie %d amount of times\n", wins[0]);
}

void exportWins(int wins[], char *message){
  FILE *f;

  if((f = fopen("outputData.txt", "a")) != NULL){
    fprintf(f, "%s\n", message);
    fprintf(f, "x wins %d amount of times\n", wins[1]);
    fprintf(f, "x losts %d amount of times\n", wins[2]);
    fprintf(f, "It is a tie %d amount of times\n", wins[0]);
  } else printf("Failed to open output file");
}

void print_error(){
  fprintf(stderr, "Unknown Usage of Program\n");
  fprintf(stderr, "'./ttt.out' to start the porgram with CLI and have the program ask you botDifficulty and number of players\n");
  fprintf(stderr, "'./ttt.out --gui' to start the porgram with GUI and have the program ask you botDifficulty and number of players\n");
  fprintf(stderr, "'./ttt.out noPlayers botDiff[0] botDiff[1]' to start the program in CLI with the given settings\n");
  fprintf(stderr, "'./ttt.out noPlayers botDiff[0] botDiff[1] --gui' to start the program in GUI with the given settings\n");
}
