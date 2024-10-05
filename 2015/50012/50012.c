#include <stdio.h>                                                                              
#include "blockmover.h"
 
void printBlock(unsigned long long int *block) {
    long long int value = *block;
    int index = 1;
    while(index <= 64){
        printf("%lld%c", value & 1LL, "\0\n"[index % 8 == 0]);
        index++;
        value >>= 1LL;
    }
    
}
 
void initialize(unsigned long long int *block, int row, int column, int size) {
    unsigned long long int value = 0;
    for(int i = 0; i < size; i++){
        //把之前的值推到下一row
        value <<= 8;
        //在末位放上size個1 推到column的位置
        value |= (((1LL << size) - 1LL) << column);
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
        left_bound |= 1LL;
    }

    if(left_bound & *block)
        return 0;
    else{
        *block >>= 1LL;     
        return 1; 
    }
}
 
int moveRight(unsigned long long int *block) {
    //check right bound
    unsigned long long right_bound = 0;
    for(int i = 0; i < 8; i++){
        right_bound <<= 8;
        right_bound |= (1LL << 7);
    }

    if(right_bound & *block)
        return 0;
    else{
        *block <<= 1LL;  
        return 1;
    }
}
 
int moveUp(unsigned long long int *block) {
    //check up bound
    unsigned long long upper_bound = (1LL << 8) - 1;
    
    if(upper_bound & *block)
        return 0;
    else{
        *block >>= 8LL;
        return 1;
    }
}
 
int moveDown(unsigned long long int *block) {
    //check down bound
    unsigned long long down_bound = (1LL << 8) - 1;
    down_bound <<= 56;

    if(down_bound & *block)
        return 0;
    else{
        *block <<= 8LL;  
        return 1;
    }
}