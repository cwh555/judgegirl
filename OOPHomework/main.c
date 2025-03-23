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
    
    bool end = false;
 
    for(int i = 0; i < bingo_size * bingo_size; i++){
        int input;
        scanf("%d", &input);
 
        if(end)
            continue;
 
        for(int people_index = 0;people_index < people_num; people_index++)
            end |= playOneBingo(people_num, bingo_size, end, input, record[people_index]);
    }
 
    for(int i = 0; i < people_num; i++)
        free(record[i]->data);
    free(record);
 
    return 0;
}