/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: topisani
 *
 * Created on February 20, 2017, 11:39 PM
 */

#include <gtk/gtk.h>
#include "ui/drawing/colour.h"

static void do_drawing(cairo_t *, GtkWidget *);

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,
    gpointer user_data)
{
  do_drawing(cr, widget);

  return FALSE;
}

static void do_drawing(cairo_t *cr, GtkWidget *widget)
{
  using namespace ui::drawing::tools;
  GtkWidget *win = gtk_widget_get_toplevel(widget);

  int width, height;
  gtk_window_get_size(GTK_WINDOW(win), &width, &height);

  rectangle(cr, 0, 0, width, height);
  fill(cr, BLACK);

  cairo_set_line_width(cr, 2);

  circle(cr, 0.3*width, height/2, 45);
  stroke(cr, RED);

  circle(cr, 0.3*width, height/2, 15);
  fill(cr, RED);

  circle(cr, width - 0.3*width, height/2, 45);
  stroke(cr, RED);

  circle(cr, width - 0.3*width, height/2, 15);
  fill(cr, RED);
}


int main (int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *darea;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  darea = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER(window), darea);

  g_signal_connect(G_OBJECT(darea), "draw",
      G_CALLBACK(on_draw_event), NULL);
  g_signal_connect(G_OBJECT(window), "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
  gtk_window_set_resizable (GTK_WINDOW(window), FALSE);
  gtk_window_set_title(GTK_WINDOW(window), "Tapedeck");

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
