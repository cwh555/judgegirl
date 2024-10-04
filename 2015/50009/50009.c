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

    //開始檢查
    bool rule = true;
    while(*ptr != 0 && rule){
        //反向
        for(int i = 0; i < *column && rule; i++, ptr++){
            if(*ptr != (*row + 1) * (*column) - i - 1)
                rule = false;
        }
        (*row) ++;

        //正向
        if(*ptr != 0 && rule){
            for(int i = 0; i < *column && rule; i++, ptr++)
                if(*ptr != (*row) * (*column) + i)
                    rule = false;
        }
        (*row) ++;
    }

    return 1;
}

