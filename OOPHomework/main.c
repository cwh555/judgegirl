#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Bingo.h"

int main(){
    int people_num, bingo_size;
    scanf("%d%d", &people_num, &bingo_size);
    
    Board **record = (Board **)malloc(sizeof(Board*) * people_num);
    for(int i = 0; i < people_num; i++)
        record[i] = initBoard(bingo_size);
    
    bool gameEnd = false;
 
    for(int i = 0; i < bingo_size * bingo_size; i++)
        gameEnd |= OneRound(bingo_size, people_num, record, gameEnd);
 
    for(int i = 0; i < people_num; i++)
        free(record[i]->data);
    free(record);
 
    return 0;
}