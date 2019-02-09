#include "gui.h"

void on_destroy(GtkWidget * src, gpointer data){
    gui_free((GuiModel *) data);
    gtk_main_quit();
}

void on_zoom(GtkWidget *src, gpointer data){
    if(data == NULL || src == NULL){
        printf("ERROR in on_zoom: NULLPOINTER");
        return;
    }
    GuiModel * gm = (GuiModel*) data;
    double factor = atof(gtk_entry_get_text(GTK_ENTRY(gm->entry_zoom)));
    if(factor == 0.0){
        return;
    }
    if(src == gm->btn_zoom){
        gm->zoom =  gm->zoom / factor;
    }
    else if(src == gm->btn_zoom_out){
        gm->zoom =  gm->zoom * factor;
    }
    gui_image_paint_set( gm->zoom, gm, 0, 0);
    gui_stats_refresh(gm);
}

void on_move(GtkWidget * src, gpointer data){
    if(data == NULL || src == NULL){
        printf("ERROR in on_move");
        return;
    }

    GuiModel  * gm = (GuiModel *) data;


    if(src == gm->btn_up){
        gui_image_paint_set(gm->zoom, gm, 0, -MOVE_STEPS);
    }
    else if(src == gm->btn_down){
        gui_image_paint_set(gm->zoom, gm, 0, MOVE_STEPS);

    }
    else if(src == gm->btn_left){
        gui_image_paint_set(gm->zoom, gm, MOVE_STEPS, 0);

    }
    else if(src == gm->btn_right){
        gui_image_paint_set(gm->zoom, gm, -MOVE_STEPS, 0);

    }
    gui_stats_refresh(gm);
}

void gui_free(GuiModel * model){
    free(model);
}

GuiModel * gui_init(){
    GuiModel * gm = calloc(1, sizeof(GuiModel));

    gm->zoom = 0.05;
    gm->y_shift = 0;
    gm->x_shift = 0;

    gm->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gm->grid = gtk_grid_new();
    gm->grid_controls = gtk_grid_new();
    gm->image = gtk_image_new();
    gm->pbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, 0, 8, IMAGE_WIDTH, IMAGE_HEIGHT);

    gm->btn_up = gtk_button_new_with_label("UP");
    gm->btn_down = gtk_button_new_with_label("DOWN");
    gm->btn_left = gtk_button_new_with_label("LEFT");
    gm->btn_right = gtk_button_new_with_label("RIGHT");
    gm->btn_zoom = gtk_button_new_with_label("ZOOM");
    gm->btn_zoom_out = gtk_button_new_with_label("ZOOM OUT");
    gm->entry_zoom = gtk_entry_new();
    gm->label_stats = gtk_label_new("Hier steht ihr Text !!");
    

    gtk_container_add(GTK_CONTAINER(gm->window), gm->grid);

    //Großes Grid
    gtk_grid_attach(GTK_GRID(gm->grid), gm->image, 0, 0 ,1, 1);
    gtk_grid_attach(GTK_GRID(gm->grid), gm->grid_controls, 1, 0 ,1, 1);

    //Kleines Grid
    gtk_grid_attach(GTK_GRID(gm->grid_controls), gm-> entry_zoom, 0,0,4,1);
    gtk_grid_attach(GTK_GRID(gm->grid_controls), gm-> btn_zoom, 0,1,4,1);
    gtk_grid_attach(GTK_GRID(gm->grid_controls), gm-> btn_zoom_out, 0,2,4,1);
    gtk_grid_attach(GTK_GRID(gm->grid_controls), gm-> btn_up, 0,3,1,1);
    gtk_grid_attach(GTK_GRID(gm->grid_controls), gm-> btn_down, 0,4,1,1);
    gtk_grid_attach(GTK_GRID(gm->grid_controls), gm-> btn_left, 0,5,1,1);
    gtk_grid_attach(GTK_GRID(gm->grid_controls), gm-> btn_right, 0,6,1,1);
    gtk_grid_attach(GTK_GRID(gm->grid_controls), gm-> label_stats, 0,7,4,1);


    g_signal_connect(gm->window, "destroy", G_CALLBACK(on_destroy), gm);
    g_signal_connect(gm->btn_up, "clicked", G_CALLBACK(on_move), gm);
    g_signal_connect(gm->btn_down, "clicked", G_CALLBACK(on_move), gm);
    g_signal_connect(gm->btn_left, "clicked", G_CALLBACK(on_move), gm);
    g_signal_connect(gm->btn_right, "clicked", G_CALLBACK(on_move), gm);
    g_signal_connect(gm->btn_zoom, "clicked", G_CALLBACK(on_zoom), gm);
    g_signal_connect(gm->btn_zoom_out, "clicked", G_CALLBACK(on_zoom), gm);

    gui_stats_refresh(gm);

    return gm;

}

void gui_image_put_pixel (GuiModel * gm, int x, int y, guchar red, guchar green, guchar blue, guchar alpha){
    GdkPixbuf *pixbuf = gm->pbuf;
    int width, height, rowstride, n_channels;
    guchar *pixels, *p;

        n_channels = gdk_pixbuf_get_n_channels (pixbuf);

    //Will fail if those tests fail
    g_assert (gdk_pixbuf_get_colorspace (pixbuf) == GDK_COLORSPACE_RGB);
    g_assert (gdk_pixbuf_get_bits_per_sample (pixbuf) == 8);
    //g_assert (gdk_pixbuf_get_has_alpha (pixbuf));
    g_assert (n_channels == 3);

    width = gdk_pixbuf_get_width (pixbuf);
    height = gdk_pixbuf_get_height (pixbuf);

    g_assert (x >= 0 && x < width); 
    g_assert (y >= 0 && y < height);

    rowstride = gdk_pixbuf_get_rowstride (pixbuf);
    pixels = gdk_pixbuf_get_pixels (pixbuf);

    p = pixels + y * rowstride + x * n_channels;
    p[0] = red;
    p[1] = green;
    p[2] = blue;
    //p[3] = alpha;
}

void gui_image_paint_test(GuiModel * gmodel){
    for(int y = 0; y < IMAGE_HEIGHT; y++){
        for(int x = 0; x < IMAGE_WIDTH; x++){
            gui_image_put_pixel(gmodel, x,y, 255,0,0,1);
        }
    }
}

void gui_image_refresh(GuiModel* gm){
    if(gm == NULL){
        printf("ERROR_NULLPOINTER in gui_image_refresh");
    }
    if(gm->pbuf == NULL){
        printf("Pixelbuff NULL");
    }   
    gtk_image_set_from_pixbuf(GTK_IMAGE(gm->image), gm->pbuf);
}

void gui_image_paint_set(double scale, GuiModel * model, double p_x_shift, double p_y_shift){

    Calculator_RGB  * color = calloc(1, sizeof(Calculator_RGB));

    if(color == NULL || model == NULL || scale == 0){
        printf("ERROR in gui_image_paint_set");
        return;
    }
  
    model->pbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, 0, 8, IMAGE_WIDTH, IMAGE_HEIGHT);
    model->x_shift = model->x_shift + p_x_shift * scale;
    model->y_shift = model->y_shift + p_y_shift * scale;

  
    double x_point = 0;
    double y_point = 0;
    for(int y = 0; y<IMAGE_HEIGHT; y++){
        for(int x = 0; x<IMAGE_WIDTH; x++){
            //converting to another coord-syst.
            x_point = calculator_pixel_to_point_X(x, scale, IMAGE_WIDTH, model->x_shift);
            y_point = calculator_pixel_to_point_Y(y, scale, IMAGE_HEIGHT, model->y_shift);
            //calculating color
            int iterations = calculator_iterate_point(x_point, y_point);
            calculator_make_color(color,iterations);

            //painting

            gui_image_put_pixel(model,x,y,color->red,color->green,color->blue,0);
        }
    }
    gui_image_refresh(model);
    free(color);
    gui_image_paint_cross(model);
}

void gui_image_paint_cross(GuiModel * gm){
    gui_image_put_pixel(gm, 599, 399, 255, 255, 255, 0);
}

void gui_stats_refresh(GuiModel * gm){
    char buf[512] = {0};
    char buf_x[96] = {0};
    char buf_y[96] = {0};
    char buf_zoom[96] = {0};

    sprintf(buf_x, "X: %10lf\n", (-1) * gm->x_shift);
    sprintf(buf_y, "Y: %10lf\n", (-1) * gm->y_shift);
    sprintf(buf_zoom, "Zoom: %lf\n", gm->zoom);

    strcat(buf,buf_x);
    strcat(buf,buf_y);
    strcat(buf,buf_zoom);

    gtk_label_set_label(GTK_LABEL(gm->label_stats), buf);
}