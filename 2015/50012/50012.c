#include <stdio.h>                                                                              
#include "blockmover.h"
 
void printBlock(unsigned long long int *block) {
    unsigned long long value = *block;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            printf("%d", (value & 1ULL ? 1 : 0));
            value >>= 1;
        }
        printf("\n");
    }

}
 
void initialize(unsigned long long int *block, int row, int column, int size) {
    unsigned long long int value = 0;
    for(int i = 0; i < size; i++){
        //把之前的值推到下一row
        value <<= 8;
        //在末位放上size個1 推到column的位置
        value |= (((1ULL << size) - 1ULL) << column);
    }

    //推到row
    for(int i = 0; i < row; i++)
        value <<= 8;

    *block = value;

    return ;
}

int moveLeft(unsigned long long int *block) {
    //check left bound
    //make bound number
    unsigned long long left_bound = 0;
    for(int i = 0; i < 8; i++){
        left_bound <<= 8;
        left_bound |= 1ULL;
    }

    if(left_bound & *block)
        return 0;
    else{
        *block >>= 1;     
        return 1; 
    }
}
 
int moveRight(unsigned long long int *block) {
    //check right bound
    unsigned long long right_bound = 0;
    for(int i = 0; i < 8; i++){
        right_bound <<= 8;
        right_bound |= (1ULL << 7);
    }

    if(right_bound & *block)
        return 0;
    else{
        *block <<= 1;  
        return 1;
    }
}
 
int moveUp(unsigned long long int *block) {
    //check up bound
    unsigned long long upper_bound = (1ULL << 8) - 1ULL;
    
    if(upper_bound & *block)
        return 0;
    else{
        *block >>= 8;
        return 1;
    }
}
 
int moveDown(unsigned long long int *block) {
    //check down bound
    unsigned long long down_bound = (1ULL << 8) - 1ULL;
    down_bound <<= 56;

    if(down_bound & *block)
        return 0;
    else{
        *block <<= 8;  
        return 1;
    }
}