#ifndef CALCULATOR_H
#define CALCULATOR_H

#include<stdio.h>
#include<stdlib.h>
#include "color.h"

#define N_ITERATIONS 1000

enum{
    NO_SET,
    MB_SET,
    J_SET
};

int calculator_iterate_point_MB(double x, double y);
int calculator_iterate_point_JM(double x, double y);
void calculator_make_color(Cal_col * color, int iterations);
double calculator_pixel_to_point_X(int pix_comp, double factor, double max, double x_shift);
double calculator_pixel_to_point_Y(int pix_comp, double factor, double max, double y_shift);
void calculator_randomize_color_settings(Cal_col * color);
void calculator_search_point_in_set(
    int x, int y, 
    double x_shift, double y_shift, 
    double scale, int width, int height, 
    Cal_col * color, int iterate(double x, double y));


#endif