#include <stdio.h>
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
    bool find_column = false;
    for(int i = 0; i < 8 && !find_column; i++){
        if((*board & checker) == checker){
            if(find == 0){
                find = 2;
                *rowColumn = i;
            }
            else if(i < *rowColumn)
                *rowColumn = i;
            find_column = true;
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

    if(leftup || rightup){
        *rowColumn = 0;
        if(!leftup && rightup)
            *rowColumn = 1;
    }

    return find;
}


int main(void)
{
    unsigned long long int board;
    int res = 0, rowColumn = 0;
    scanf("%llu", &board);
    res = bingo(&board, &rowColumn);
    if(res == 0) printf("no\n");
    else printf("%d %d\n", res, rowColumn);
    return 0;
}
