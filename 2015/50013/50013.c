#include "bingo.h"
#include <stdbool.h>


int bingo(const unsigned long long int *board, int *rowColumn){
    int find = 0;
    unsigned long long int checker = 0;
    //檢查row
    checker = (1ULL << 8 ) - 1ULL;
    for(int i = 0; i < 8 && find != 1; i++){
        if((*board & checker) == checker){
            find = 1;
            *rowColumn = 7 - i;
        }
        checker <<= 8;
    }

    //檢查column
    checker = (0x0101010101010101ULL);
    bool find_column = false;
    for(int i = 0; i < 8 && !find_column; i++){
        if((*board & checker) == checker){
            if(find == 0){
                find = 1;
                *rowColumn = 7 - i;
            }
            else
                *rowColumn = 0;
            find_column = true;
        }
    }

    //檢查左上對角線
    checker = (0x8040201008040201ULL);
    if((checker & *board) == checker){
        if(find == 0)
            find = 3;
        *rowColumn = 0;
    }

    //檢查右上對角線
    checker = (0x0102040810204080ULL);
    if((checker & *board) == checker){
        if(find == 0){
            find = 3;
            *rowColumn = 1;
        }
        else
            *rowColumn = 0;
    }

    return find;
}
