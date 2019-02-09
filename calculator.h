#ifndef CALCULATOR_H
#define CALCULATOR_H

#include<stdio.h>

#define N_ITERATIONS 1000

//Contains a color wth three 8-Bit channels
typedef struct{
    int red;
    int green;
    int blue;
}Calculator_RGB;

int calculator_iterate_point(double x, double y);
void calculator_make_color(Calculator_RGB * color, int iterations);
double calculator_pixel_to_point_X(int pix_comp, double factor, double max, double x_shift);
double calculator_pixel_to_point_Y(int pix_comp, double factor, double max, double y_shift);

#endif