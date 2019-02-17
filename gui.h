#ifndef GUI_H
#define GUI_H
#include <string.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "calculator.h"
#include "color.h"

#define IMAGE_WIDTH 1200 //Übergangslösung
#define IMAGE_HEIGHT 800
#define MOVE_STEPS 100

typedef struct{

    GtkWidget * window;
    GtkWidget * grid;
    GtkWidget * grid_controls;
    GtkWidget * btn_up;
    GtkWidget * btn_down;
    GtkWidget * btn_left;
    GtkWidget * btn_right;
    GtkWidget * btn_zoom;
    GtkWidget * btn_zoom_out;
    GtkWidget * btn_rand;
    GtkWidget * entry_zoom;
    GtkWidget * label_stats; 
    GtkWidget * image;
    GdkPixbuf * pbuf;
    Cal_col * color;
    double zoom;
    double x_shift;
    double y_shift;
}GuiModel;

GuiModel * gui_init();
void gui_free(GuiModel * model);
void gui_image_put_pixel (GuiModel * gm, int x, int y, guchar red, guchar green, guchar blue, guchar alpha);
void gui_image_refresh(GuiModel* gm);
void gui_image_paint_test(GuiModel * gmodel);
void gui_image_paint_set(double scale, GuiModel * model, double p_x_shift, double p_y_shift);
void gui_image_paint_cross(GuiModel * gm);
void gui_stats_refresh(GuiModel * model);
void on_move(GtkWidget * src, gpointer data);
void on_destroy(GtkWidget * src, gpointer data);
void on_zoom(GtkWidget * src, gpointer data);

#endif