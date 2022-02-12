#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include "Gui.h"
#include "TicTacToe.h"

struct g_data gdata;

static void select_players(GtkWidget *widget, gpointer data){
  /* Triggered when the user clicked on the continue button
   * at the Setup Players page */
  // Getting the selected option
  GtkWidget *combobox = data;
  int noPlayers = gtk_combo_box_get_active(GTK_COMBO_BOX (combobox));

  // Storing the number of players
  gdata.noPlayers = noPlayers;

  // Switching to different screens based on the number of players
  switch(noPlayers){
    case 0:
      gtk_stack_set_visible_child_name(GTK_STACK (gdata.stack), "Setup Bots 0");
      break;
    case 1:
      gtk_stack_set_visible_child_name(GTK_STACK (gdata.stack), "Setup Bots 1");
      break;
    case 2:
      gtk_stack_set_visible_child_name(GTK_STACK (gdata.stack), "TicTacToe");
      break;
  }
}

static void select_bots(GtkWidget *widget, gpointer data){
  /* Triggered when the user clicked on the continue button
   * at the Setup Bots 0/1 page */
  // Getting the selected option
  GtkWidget **combobox = data;
  int botDiff0 = gtk_combo_box_get_active(GTK_COMBO_BOX (combobox[1]));
  int botDiff1 = gtk_combo_box_get_active(GTK_COMBO_BOX (combobox[0]));

  // Storing the bot Difficulties
  gdata.botDiff[0] = botDiff0 + 1;
  gdata.botDiff[1] = botDiff1 + 1;

  // Changing to TicTacToe Screen
  gtk_stack_set_visible_child_name(GTK_STACK (gdata.stack), "TicTacToe");

  // Making a Move if AI/bot is moving first
  int choice = -1;
  choice = bot_logic(gdata.cBoard, gdata.botDiff, gdata.noPlayers, gdata.cPlayer);
  if(choice != -1) gtk_widget_activate(gdata.buttons[choice]);
}

static void select_choice(GtkWidget *widget, gpointer data){
  /* Triggered when the user clicked on one of the TicTacToe board button */
  // Setting up string
  char str[2] = "\0";
  str[0] = player_symbol(gdata.cPlayer);

  // Setting up current index and printing it
  int *i = (int *) data;
  g_print ("Spot %d is chosen\n", *i + 1);

  // Changing the button into a label
  /* Hiding the number
     gtk_widget_hide(GTK_WIDGET(widget)); */
  // Creating a New Label
  GtkWidget *label = gtk_label_new(str);
  gtk_grid_attach(GTK_GRID (gdata.grid), label, (*i%3), *i/3, 1, 1);

  // Updating Board
  gdata.cBoard[*i] = gdata.cPlayer;

  int winner = check_win(gdata.cBoard);
  // Printing Winner
  if(winner > 0 || gdata.noMoves > 7){
    print_winner(winner);
    print_board(gdata.cBoard);
    gtk_stack_add_named(GTK_STACK(gdata.stack), GTK_WIDGET (create_results(winner)), "Results");
    gtk_stack_set_visible_child_name(GTK_STACK (gdata.stack), "Results");
    return;
  }

  // Switching Player
  switch_player(&(gdata.cPlayer));

  // Adding an extra move
  gdata.noMoves++;

  // Bot Choice if there is one
  int choice = -1;
  choice = bot_logic(gdata.cBoard, gdata.botDiff, gdata.noPlayers, gdata.cPlayer);
  if(choice != -1) gtk_widget_activate(gdata.buttons[choice]);
}

static void play_again(GtkWidget *widget, gpointer data){
  GtkWidget *button;
  // Deleting the Previous TicTacToe Child
  GtkWidget *TicTacToe = gtk_stack_get_child_by_name(GTK_STACK (gdata.stack), "TicTacToe");
  gtk_stack_remove(GTK_STACK (gdata.stack), TicTacToe);
  // Deleting the Previous Results Child
  GtkWidget *Results = gtk_stack_get_child_by_name(GTK_STACK (gdata.stack), "Results");
  gtk_stack_remove(GTK_STACK (gdata.stack), Results);

  // Changing Visible Screen to the new board
  gtk_stack_add_named(GTK_STACK(gdata.stack), create_board(), "TicTacToe");
  gtk_stack_set_visible_child_name(GTK_STACK (gdata.stack), "TicTacToe");

  // Resetting Values
  gdata.noMoves = 0;
  for(int i = 0; i < 9; i++) gdata.cBoard[i] = 0;
  gdata.cPlayer = rand() % 2 + 1;

  // Bot Choice if there is one
  int choice = -1;
  choice = bot_logic(gdata.cBoard, gdata.botDiff, gdata.noPlayers, gdata.cPlayer);
  if(choice != -1) gtk_widget_activate(gdata.buttons[choice]);
}

GtkWidget * create_player_setup(){
  /* Creating the Setup Page for the number of players */
  // Creating Variables
  GtkWidget *combobox; GtkWidget *grid = gtk_grid_new();
  GtkWidget *button;
  GtkWidget *label;

  // Adding the description label
  label = gtk_label_new("Choose how many players are playing: ");
  gtk_grid_attach (GTK_GRID (grid), label, 0, 0, 1, 1);

  // Setup the combobox for Number of players
  combobox = gtk_combo_box_text_new();
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT (combobox), "0");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT (combobox), "1");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT (combobox), "2");
  gtk_combo_box_set_active(GTK_COMBO_BOX (combobox), 2);

  // Attaching combobox to the grid
  gtk_grid_attach (GTK_GRID (grid), combobox, 1, 0, 1, 1);

  // Creating and attaching the button to continue
  button = gtk_button_new_with_label("Continue");
  g_signal_connect(button, "clicked", G_CALLBACK (select_players), combobox);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 2, 1);

  // Returning the grid
  return grid;
}

GtkWidget * create_bot_setup(int nPlayers){
  /* Creating the Setup Page for the bot difficulty */
  // Creating Varible
  GtkWidget *combobox1;
  GtkWidget *combobox2;
  GtkWidget *grid = gtk_grid_new();
  static GtkWidget *button;
  GtkWidget *label;

  // Adding the description label
  label = gtk_label_new("Choose Bot Difficulty of o");
  gtk_grid_attach (GTK_GRID (grid), label, 0, 0, 1, 1);

  // Setup comboboxes for Bot Difficulty for player o
  combobox1 = gtk_combo_box_text_new();
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT (combobox1), "Random");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT (combobox1), "Smart");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT (combobox1), "Minimax");
  gtk_combo_box_set_active(GTK_COMBO_BOX (combobox1), 0);

  // Attaching combobox for player o to the grid
  gtk_grid_attach (GTK_GRID (grid), combobox1, 1, 0, 1, 1);

  // Setup comboboxes for Bot Difficulty for player x
  label = gtk_label_new("Choose Bot Difficulty of x");

  // Setup comboboxes for Bot Difficulty for player x
  combobox2 = gtk_combo_box_text_new();
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT (combobox2), "Random");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT (combobox2), "Smart");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT (combobox2), "Minimax");

  // Creating and attaching the button to continue
  button = gtk_button_new_with_label("Continue");

  gtk_grid_attach (GTK_GRID (grid), button, 0, 2, 2, 1);

  if(nPlayers == 0){
    gtk_combo_box_set_active(GTK_COMBO_BOX (combobox2), 0);
    // Attaching combobox for player x to the grid
    gtk_grid_attach (GTK_GRID (grid), combobox2, 1, 1, 1, 1);
    // Attaching label to the grid
    gtk_grid_attach (GTK_GRID (grid), label, 0, 1, 1, 1);

    static GtkWidget *comboboxPassed[2];
    comboboxPassed[0] = combobox1;
    comboboxPassed[1] = combobox2;

    g_signal_connect (button, "clicked", G_CALLBACK (select_bots), comboboxPassed);
  } else{
    static GtkWidget *comboboxPassed[2];
    comboboxPassed[0] = combobox1;
    comboboxPassed[1] = combobox2;
    g_signal_connect (button, "clicked", G_CALLBACK (select_bots), comboboxPassed);
  }

  // Returning the grid
  return grid;
}

GtkWidget * create_board(){
  /* Creating the tictactoe GUI board */
  // Creating Variables
  static int array[9];
  GtkWidget *grid = gtk_grid_new();;
  GtkWidget *button;

  // Setting up grid for data
  gdata.grid = grid;

  // Looping over all the buttons
  for(int i = 0; i < 9; i++) {
    array[i] = i;
    // Setting up a new button
    button = gtk_button_new();
    gdata.buttons[i] = button;
    g_signal_connect (button, "clicked", G_CALLBACK (select_choice), &array[i]);

    // Attaching Each Button On it's respective grid
    gtk_grid_attach (GTK_GRID (grid), button, (i%3), i/3, 1, 1);
  }

  // Returning the grid
  return grid;
}

GtkWidget * create_results(int winner){
  // Creating Variables
  GtkWidget *grid = gtk_grid_new();
  GtkWidget *label = gtk_label_new("");
  GtkWidget *button;

  // Setting the text to label to it's respective winner
  switch(winner){
    case 0: // Tie
      gtk_label_set_label(GTK_LABEL (label), "It is a tie");
      break;
    case 1: // Player x Won
      gtk_label_set_label(GTK_LABEL (label), "Player x Won!");
      break;
    case 2: // Player o Won
      gtk_label_set_label(GTK_LABEL (label), "Player o Won!");
      break;
  }

  // Setting minimum size of the label
  gtk_widget_set_size_request(label, 200, 200);
  // Attaching label to the grid
  gtk_grid_attach (GTK_GRID (grid), label, 0, 0, 2, 1);

  // Creating and attaching play again button
  button = gtk_button_new_with_label("Play Again?");
  g_signal_connect(button, "clicked", G_CALLBACK (play_again), NULL);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 1, 1);

  // Creating and attaching Quit button
  button = gtk_button_new_with_label("Quit");
  g_signal_connect_swapped(button, "clicked", G_CALLBACK (gtk_window_destroy), GTK_WINDOW (gdata.window));
  gtk_grid_attach (GTK_GRID (grid), button, 1, 1, 1, 1);

  return grid;
}

static void activate(GtkApplication *app, gpointer user_data){
  /* Multiple Sections Using GTK Notebooks
  // Creating a New Button and notebook
  GtkWidget *notebook = gtk_notebook_new();
  button = gtk_button_new_with_label("Switch Page");

  // Attaching Switch Page Button Signal
  g_signal_connect_swapped(button, "clicked", G_CALLBACK (gtk_notebook_next_page), notebook);

  // Pack the Notebook into the window
  gtk_window_set_child(GTK_WINDOW (window), notebook);

  // Creating New Pages
  gtk_notebook_insert_page(GTK_NOTEBOOK (notebook), button, NULL, 1);
  gtk_notebook_append_page(GTK_NOTEBOOK (notebook), grid, NULL);

  // Hiding Page Switcher
  gtk_notebook_set_show_tabs(GTK_NOTEBOOK (notebook), FALSE);
  */

  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;
  GtkWidget *stack = gtk_stack_new();
  GtkWidget *label;
  GtkWidget *combobox;

  // Saving Stack pointer
  gdata.stack = stack;

  /* create a new window, and set its title */
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW (window), "TicTacToe");

  // Saving Window Pointer
  gdata.window = window;

  // Setup for the player setup page
  grid = create_player_setup();
  gtk_stack_add_named(GTK_STACK(stack), grid, "Setup Players");

  // Setup for the bot difficulty setup page if nPlayers = 1
  grid = create_bot_setup(1);
  gtk_stack_add_named(GTK_STACK(stack), grid, "Setup Bots 1");

  // Setup for the bot difficulty setup page if nPlayers = 0
  grid = create_bot_setup(0);
  gtk_stack_add_named(GTK_STACK(stack), grid, "Setup Bots 0");

  // Setup for the tictactoe board
  grid = create_board();
  gtk_stack_add_named(GTK_STACK(stack), grid, "TicTacToe");

  // Pack the Grid into the window
  gtk_window_set_child(GTK_WINDOW (window), stack);

  gtk_widget_show(window);

  // Switching to the game if Settings were set in cli
  if(gdata.noPlayers != -1){
    gtk_stack_set_visible_child_name(GTK_STACK (stack), "TicTacToe");

    // Making a Move if AI/bot is moving first
    int choice = -1;
    choice = bot_logic(gdata.cBoard, gdata.botDiff, gdata.noPlayers, gdata.cPlayer);
    if(choice != -1) gtk_widget_activate(gdata.buttons[choice]);
  }
}

int playGameGUI(int argc, char **argv, int noPlayers, int botDiff[]) {
  // GUI Variables
  GtkApplication *app;
  int status;

  // TicTacToe Variables
  gdata.cPlayer = rand() % 2 + 1;
  for(int i = 0; i < 9; i++) gdata.cBoard[i] = 0;
  gdata.noPlayers = noPlayers;
  gdata.botDiff[0] = botDiff[0];
  gdata.botDiff[1] = botDiff[1];
  gdata.noMoves = 0;

  // Starting GUI
  app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run(G_APPLICATION (app), 0, NULL);
  g_object_unref(app);

  return status;
}
