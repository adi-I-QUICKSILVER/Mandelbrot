#include "color.h"

Cal_col * cal_color_new(){

    Cal_col * color = calloc(1, sizeof(Cal_col));

    color->red_delt = 0;
    color->green_delt = 30;
    color->blue_delt = 100;

    color->red_m = 4;
    color->green_m = 3;
    color->blue_m = 2;

    color->red = 0;
    color->green = 0;
    color->blue = 0;

    return color;
}

void cal_color_free(Cal_col * color){
    free(color);
}

void cal_color_random(Cal_col * color){
    if(color == NULL){
        printf("NULLPOINTER_ERROR in cal_color_random");
        return;
    }

    color->red_delt = rand() % 100;
    color->green_delt = rand() % 100;
    color->blue_delt = rand() % 100;

    color->red_m = rand() % 5;
    color->blue_m = rand() % 5;
    color->red_m = rand() % 5;
}

void cal_color_generate(Cal_col * color, int iterations){
    if(iterations == -1){
        color->red = 0;
        color->green = 0;
        color->blue = 0;
    }
    else{

        color->red = color->green_delt + color->red_m * iterations;
        color->green = color->red_delt + color->green_m * iterations;
        color->blue = color->blue_delt + color->blue_m * iterations;
    }
}

