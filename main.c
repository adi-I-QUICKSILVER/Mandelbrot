
#include <gtk/gtk.h>
#include "gui.h"
#include "calculator.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
    gtk_init(&argc, &argv);
    GuiModel * model = gui_init();
    gui_image_paint_set(model->zoom,model,0,0);
    gtk_widget_show_all(model->window);
    gtk_main();
    return 0;
}