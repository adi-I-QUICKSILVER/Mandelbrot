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

        double hue = iterations % 360;
        double sat = 1 - (iterations % 50) * 0.02;
        double val = 1;

        double c = sat * val;
        double x = c * (1 - abs(hue / 60) % 2 -1);
        double m = val - c;

        double re = 0;
        double gr = 0;
        double bl = 0;

        if(hue < 60){
            re = c;
            gr = x;
            bl = 0;

        }else if(hue < 120){
            re = x;
            gr = c;
            bl = 0;

        }else if(hue < 180){
            re = 0;
            gr = c;
            bl = x;
        }else if(hue < 240){
            re = 0;
            gr = x;
            bl = c;
        }else if(hue < 300){
            re = x;
            gr = 0;
            bl = c;
        }else if(hue < 360){
            re = c;
            gr = 0;
            bl = x;
        }

        color->red = (re + m) * 255;
        color->green = (gr + m) * 255;
        color->blue = (bl + m) * 255;

        //color->red = color->green_delt + color->red_m * iterations;
        //color->green = color->red_delt + color->green_m * iterations;
        //color->blue = color->blue_delt + color->blue_m * iterations;


    }
}



