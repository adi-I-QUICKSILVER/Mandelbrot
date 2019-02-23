#include "calculator.h"

//Will test whether a given point is in the Mandelbrot set or not
//returns -1 for convergent and number of iterations if divergent
int calculator_iterate_point_MB(double x_c, double y_c){
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

void calculator_make_color(Cal_col * color, int iterations){
    cal_color_generate(color, iterations);
    
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

void calculator_randomize_color_settings(Cal_col * color){
    cal_color_random(color);
}

void calculator_search_point_in_mandelbrot(
    int x, int y, 
    double x_shift, double y_shift, 
    double scale, int width, int height, Cal_col * color){

    //converting to another coord-syst.
    double x_point = calculator_pixel_to_point_X(x, scale, width, x_shift);
    double y_point = calculator_pixel_to_point_Y(y, scale, height, y_shift);
    //calculating color
    int iterations = calculator_iterate_point_MB(x_point, y_point);
    calculator_make_color(color,iterations);
}