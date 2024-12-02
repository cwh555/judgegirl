#include "fill_rectangle.h"

void fill_rectangle_neg(int *upper_left, int *bottom_right, 
                        int n_row, int n_col, int fill){
    int *now = upper_left;
    int rectangleColumn = 0;
    while(now != bottom_right){
        *now = fill;
        rectangleColumn++;

        if((bottom_right - now) % n_col == 0){
            now += n_row + (1 - rectangleColumn);
            rectangleColumn = 0;
        }
        else
            now++;
    }
    *now = fill;

    return;
}


void fill_rectangle_pos(int *upper_right, int *bottom_left, int n_row, int n_col, int fill){
    int *now = upper_right;
    int rectangleColumn = 0;

    while(now != bottom_left){
        *now = fill;
        rectangleColumn++;

        if((bottom_left - now) % n_col == 0){
            now += n_row + rectangleColumn - 1;
            rectangleColumn = 0;
        }
        else
            now--;
    }
    *now = fill;

    return;
}