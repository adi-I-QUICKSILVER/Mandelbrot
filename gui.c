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
    if(gtk_combo_box_get_active(GTK_COMBO_BOX(gm->combo_sets)) == NO_SET){
        return;
    }
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

    if(gtk_combo_box_get_active(GTK_COMBO_BOX(gm->combo_sets)) == NO_SET){
        return;
    }

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

void on_randomize(GtkWidget * src, gpointer data){
    if(data == NULL || src == NULL){
        printf("ERROR in on_randomize");
        return;
    }
    GuiModel  * gm = (GuiModel *) data;

    if(gtk_combo_box_get_active(GTK_COMBO_BOX(gm->combo_sets)) == NO_SET){
        return;
    }

    calculator_randomize_color_settings(gm->color);
    gui_image_paint_set(gm->zoom, gm, 0, 0);
}

void on_changed_combo_sets(GtkWidget * src, gpointer data){
    if(data == NULL || src == NULL){
        printf("ERROR in on_randomize");
        return;
    }
    GuiModel  * gm = (GuiModel *) data;
    gm->zoom = 0.05;
    gm->y_shift = 0;
    gm->x_shift = 0;
    gui_image_paint_set(gm->zoom, gm, gm->x_shift, gm->y_shift);
}

void gui_free(GuiModel * model){
    cal_color_free(model->color);
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
    gm->btn_rand = gtk_button_new_with_label("Randomize");
    gm->entry_zoom = gtk_entry_new();
    gm->label_stats = gtk_label_new("Hier steht ihr Text !!");
    gm->combo_sets = gtk_combo_box_text_new();

    gm->color = cal_color_new();

    //Builds combobox
    const char *sets[] = {"Select a set", "Mandelbrot set", "Julia set"};
    for (int i = 0; i < G_N_ELEMENTS (sets); i++){
  	    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (gm->combo_sets), sets[i]);
    }
    gtk_combo_box_set_active (GTK_COMBO_BOX (gm->combo_sets), 0);

    

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
    gtk_grid_attach(GTK_GRID(gm->grid_controls), gm-> btn_rand, 0,8,4,1);
    gtk_grid_attach(GTK_GRID(gm->grid_controls), gm-> combo_sets, 0,9,4,1);

    //Eventhandling
    g_signal_connect(gm->window, "destroy", G_CALLBACK(on_destroy), gm);
    g_signal_connect(gm->btn_up, "clicked", G_CALLBACK(on_move), gm);
    g_signal_connect(gm->btn_down, "clicked", G_CALLBACK(on_move), gm);
    g_signal_connect(gm->btn_left, "clicked", G_CALLBACK(on_move), gm);
    g_signal_connect(gm->btn_right, "clicked", G_CALLBACK(on_move), gm);
    g_signal_connect(gm->btn_zoom, "clicked", G_CALLBACK(on_zoom), gm);
    g_signal_connect(gm->btn_zoom_out, "clicked", G_CALLBACK(on_zoom), gm);
    g_signal_connect(gm->btn_rand, "clicked", G_CALLBACK(on_randomize), gm);
    g_signal_connect(gm->combo_sets, "changed", G_CALLBACK(on_changed_combo_sets), gm);

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
        return;
    }
    if(gm->pbuf == NULL){
        printf("Pixelbuff NULL");
        return;
    }   
    gtk_image_set_from_pixbuf(GTK_IMAGE(gm->image), gm->pbuf);
}

void gui_image_paint_set(double scale, GuiModel * model, double p_x_shift, double p_y_shift){
  
    model->pbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, 0, 8, IMAGE_WIDTH, IMAGE_HEIGHT);
    model->x_shift = model->x_shift + p_x_shift * scale;
    model->y_shift = model->y_shift + p_y_shift * scale;
    int iterations = 0;

    for(int y = 0; y<IMAGE_HEIGHT; y++){
        for(int x = 0; x<IMAGE_WIDTH; x++){

            if(gtk_combo_box_get_active(GTK_COMBO_BOX(model->combo_sets)) == MB_SET){
                //Converts coord of pixels to corresponding coord of points in MB set; will test if the point is in the set; generates a color
                iterations = calculator_search_point_in_set(x, y, model->x_shift, model->y_shift, scale, IMAGE_WIDTH, IMAGE_HEIGHT, &calculator_iterate_point_MB);
            }
            else if(gtk_combo_box_get_active(GTK_COMBO_BOX(model->combo_sets)) == J_SET){
                //Converts coord of pixels to corresponding coord of points in Julia set; will test if the point is in the set; generates a color
                iterations = calculator_search_point_in_set(x, y, model->x_shift, model->y_shift, scale, IMAGE_WIDTH, IMAGE_HEIGHT, &calculator_iterate_point_JM);
            }
            //Will set a pixel in the buffer
            calculator_make_color(model->color,iterations);
            gui_image_put_pixel(model,x,y,model->color->red, model->color->green, model->color->blue,0);
        }
    }
    //Refreshes image and draws the buffer
    gui_image_refresh(model);
    //Will paint a white pixel to mark the center
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
