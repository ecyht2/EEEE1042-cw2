#ifndef GUI_H_
#define GUI_H_

#include <gtk/gtk.h>

struct g_data{
  GtkWidget *grid;
  int cPlayer;
  int cBoard[9];
  GtkWidget *buttons[9];
  int noPlayers;
  int botDiff[2];
  int noMoves;
  GtkWidget *quit;
};

int playGameGUI(int, char **, int, int []);
static void activate(GtkApplication *, gpointer);
static void click(GtkWidget *, gpointer);

#endif // GUI_H_
