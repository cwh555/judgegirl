#include "snake.h"
#include <stdbool.h>

int snake(int *ptr, int *row, int *column) {
    
    //先決定column長度
    *column = 0;
    while(*ptr == *column){
        (*column)++;
        ptr++;
    }
    *row = 1;
    return 1;
}

