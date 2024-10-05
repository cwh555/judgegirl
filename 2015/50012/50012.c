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
    // your implementation here
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