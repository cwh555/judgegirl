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
    *block >>= 1LL;     
    return 0; // You may change this return value.
}
 
int moveRight(unsigned long long int *block) {
    *block <<= 1LL;  
    return 0; // You may change this return value.
}
 
int moveUp(unsigned long long int *block) {
    *block >>= 8LL;
    return 0; // You may change this return value.
}
 
int moveDown(unsigned long long int *block) {
    *block <<= 8LL;  
    return 0; // You may change this return value.
}