#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include "Gui.h"
#include "TicTacToe.h"

struct g_data gdata;

static void click(GtkWidget *widget, gpointer data){
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
  gtk_grid_attach(GTK_GRID (gdata.grid), label, 3*(*i%3), *i/3, 3, 1);

  // Updating Board
  gdata.cBoard[*i] = gdata.cPlayer;

  // Printing Winner
  if(check_win(gdata.cBoard) > 0 || gdata.noMoves > 7){
    print_winner(check_win(gdata.cBoard));
    gtk_widget_activate(gdata.quit);
    print_board(gdata.cBoard);
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

static void activate(GtkApplication *app, gpointer user_data){
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  static int array[9];

  /* create a new window, and set its title */
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW (window), "Window");

  /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new ();
  // Setting up grid for data
  gdata.grid = grid;

  /* Pack the container in the window */
  gtk_window_set_child (GTK_WINDOW (window), grid);

  for(int i = 0; i < 9; i++) {
    array[i] = i;
    // Setting up a new button
    button = gtk_button_new();
    gdata.buttons[i] = button;
    g_signal_connect (button, "clicked", G_CALLBACK (click), &array[i]);

    // Attaching Each Button On it's respective grid
    gtk_grid_attach (GTK_GRID (grid), button, 3*(i%3), i/3, 3, 1);
  }

  button = gtk_button_new_with_label("Quit");
  gdata.quit = button;
  g_signal_connect_swapped(button, "clicked", G_CALLBACK (gtk_window_destroy), window);

  /* Place the Quit button in the grid cell (0, 4), and make it
   * span 9 columns.
   */
  gtk_grid_attach(GTK_GRID (grid), button, 0, 4, 9, 1);

  gtk_widget_show(window);

  int choice = -1;
  choice = bot_logic(gdata.cBoard, gdata.botDiff, gdata.noPlayers, gdata.cPlayer);
  if(choice != -1) gtk_widget_activate(gdata.buttons[choice]);
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
  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
