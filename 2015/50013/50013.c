#include "bingo.h"
#include <stdbool.h>


int bingo(const unsigned long long int *board, int *rowColumn){
    int find = 0;
    unsigned long long int checker = 0;
    //檢查row
    checker = ((1ULL << 8 ) - 1ULL) << 56;
    for(int i = 0; i < 8 && find != 1; i++){
        if((*board & checker) == checker){
            find = 1;
            *rowColumn = i;
        }
        checker >>= 8;
    }

    //檢查column
    checker = (0x8080808080808080ULL);
    for(int i = 0; i < 8 && find == 0; i++){
        if((*board & checker) == checker){
            if(find == 0){
                find = 2;
                *rowColumn = i;
            }
        }
        checker >>= 1;
    }

    //檢查左上對角線
    bool leftup = false;
    checker = (0x8040201008040201ULL);
    if((checker & *board) == checker){
        if(find == 0)
            find = 3;
        leftup = true;
    }

    //檢查右上對角線
    checker = (0x0102040810204080ULL);
    bool rightup = false;
    if((checker & *board) == checker){
        if(find == 0)
            find = 3;
        rightup = true;
    }

    if(rightup)
        *rowColumn = 1;
    if(leftup)
        *rowColumn = 0;

    return find;
}