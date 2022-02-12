#ifndef GUI_H_
#define GUI_H_

#include <gtk/gtk.h>

struct g_data{
  GtkWidget *grid;
  GtkWidget *stack;
  GtkWidget *buttons[9];
  GtkWidget *window;
  int cPlayer;
  int cBoard[9];
  int noPlayers;
  int botDiff[2];
  int noMoves;
};

static void select_players(GtkWidget *, gpointer);
static void select_bots(GtkWidget *, gpointer);
static void select_choice(GtkWidget *, gpointer);
static void play_again(GtkWidget *, gpointer);
GtkWidget * create_player_setup();
GtkWidget * create_bot_setup(int);
GtkWidget * create_board();
GtkWidget * create_results(int);
static void activate(GtkApplication *, gpointer);
int playGameGUI(int, char **, int, int []);

#endif // GUI_H_
