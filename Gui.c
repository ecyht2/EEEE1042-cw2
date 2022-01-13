#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include "Gui.h"

struct g_data gdata;

static void click(GtkWidget *widget, gpointer data){
  int *i = (int *)data;
  g_print ("Spot %d is chosen\n", *i + 1);
  gtk_widget_hide(GTK_WIDGET(widget));
  GtkWidget *label = gtk_label_new("X");
  gtk_grid_attach(GTK_GRID (gdata.grid), label, 3*(*i%3), *i/3, 3, 1);
}

static void activate(GtkApplication *app, gpointer user_data){
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  static int array[9];

  /* create a new window, and set its title */
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");

  /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new ();
  // Setting up grid for data
  gdata.grid = grid;

  /* Pack the container in the window */
  gtk_window_set_child (GTK_WINDOW (window), grid);

  for(int i = 0; i < 9; i++) {
    array[i] = i;
    // Setting up button
    button = gtk_button_new();
    g_signal_connect (button, "clicked", G_CALLBACK (click), &array[i]);
    /* Place the first button in the grid cell (0, 0), and make it fill
    * just 1 cell horizontally and vertically (ie no spanning)
    */
    gtk_grid_attach (GTK_GRID (grid), button, 3*(i%3), i/3, 3, 1);
  }

  button = gtk_button_new_with_label ("Quit");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_window_destroy), window);

  /* Place the Quit button in the grid cell (0, 1), and make it
   * span 2 columns.
   */
  gtk_grid_attach (GTK_GRID (grid), button, 0, 4, 9, 1);

  gtk_widget_show (window);
}

int main (int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
