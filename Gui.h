#ifndef GUI_H_
#define GUI_H_

#include <gtk/gtk.h>

struct g_data{
  GtkWidget *grid;
};

int playGameGUI(int, char **);
static void activate(GtkApplication *, gpointer);
static void click(GtkWidget *, gpointer);

#endif // GUI_H_
