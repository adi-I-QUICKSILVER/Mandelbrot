#ifndef COLOR_H
#define COLOR_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct{
    //Three 8-bit channels to store RGB-values
    int red;
    int green;
    int blue;

    //Parameters for linear transformation into a color
    int red_delt;
    int green_delt;
    int blue_delt;

    int red_m;
    int green_m;
    int blue_m;
}Cal_col;

Cal_col * cal_color_new();
void cal_color_free(Cal_col * color);
void cal_color_random(Cal_col * color);
void cal_color_generate(Cal_col * color, int x);

#endif