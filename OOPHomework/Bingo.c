#include "Bingo.h"
#include <stdio.h>
#include <stdbool.h>

Board *initBoard(const int bingoSize){
    Board *board = (Board *)malloc(sizeof(Board));
    scanf("%s", board->name);

    board->row_pick = (int*)calloc(bingoSize, sizeof(int));
    board->column_pick = (int*)calloc(bingoSize, sizeof(int));
    board->diagonal[0] = 0;
    board->diagonal[1] = 0;
    board->data = (int(*)[2])malloc(sizeof(int[2]) * bingoSize * bingoSize);

    for(int bingoRow = 0; bingoRow < bingoSize; bingoRow++){
        for(int bingoColumn = 0; bingoColumn < bingoSize; bingoColumn++){
            int temp;
            scanf("%d", &temp);
            board->data[temp - 1][0] = bingoRow;
            board->data[temp - 1][1] = bingoColumn;
        }
    }
    return board;
}

bool playOneBingo(const int people_num, const int bingo_size, 
            const bool gameEnd, const int choice, Board *board){

    if(get_number(board, choice - 1, bingo_size)){
        if(!gameEnd)
            printf("%d", choice);
        printf(" %s", board->name);

        return true;
    }
    return false;
}
 
bool get_number(Board* people, int target, int bingo_size){
    //找到此數字的位置
    int x = people->data[target][0];
    int y = people->data[target][1];
 
    //檢查連線
    if(++people->column_pick[y] == bingo_size)
        return true;
    if(++people->row_pick[x] == bingo_size)
        return true;
    if(x == y && ++people->diagonal[0] == bingo_size)
        return true;
    if(x + y == bingo_size - 1 && ++people->diagonal[1] == bingo_size)
        return true;

    return false;
}