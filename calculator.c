#include "calculator.h"

//returns -1 for convergent and number of iterations if divergent
int calculator_iterate_point(double x_c, double y_c){
   double x_alt = 0;
   double y_alt = 0;
   double x_new = 0;
   double y_new = 0;
   double d_sq = 0; //distance SQUARED

   for(int i = 0; i< N_ITERATIONS; i++){
        x_new = x_alt * x_alt - y_alt * y_alt + x_c;
        y_new = 2 * x_alt * y_alt + y_c;
        d_sq = x_new * x_new + y_new * y_new;

        if(d_sq >= 9){
            //printf("%lf / %lf : %d \n", x_c, y_c, i);
            return i;
        }
        else{
            x_alt = x_new;
            y_alt = y_new;
        }

   }
    //printf("%lf / %lf : -1 \n", x_c, y_c);
    return -1; // TODO: Genauer auf Konvergenz untersuchen
}

void calculator_make_color(Calculator_RGB * color, int iterations){
    if(iterations == -1){
        color->red = 0;
        color->green = 0;
        color->blue = 0;
    }
    else{
        color->red = 0 + 4* iterations;
        color->green = 30 + 3* iterations;
        color->blue = 100 + 2* iterations;
    }
    
}

//pix_component: x component of pixel, scalefactor, wdth or height
double calculator_pixel_to_point_X(int pix_comp, double factor, double max, double x_shift){
    double point_comp = pix_comp - max / 2; // Umwandlung in ein normales Koordinatensystem
    point_comp = (point_comp * factor - x_shift);
    return point_comp;
}

//pix_component: x component of pixel, scalefactor, wdth or height
double calculator_pixel_to_point_Y(int pix_comp, double factor, double max, double y_shift){
    double point_comp = pix_comp * (-1) + max / 2; // Umwandlung in ein normales Koordinatensystem
    point_comp = (point_comp * factor  - y_shift);
    return point_comp;
}