#include "Board.h"
#include <stdlib.h>
#include <stdbool.h>

Board *initBoard(const int bingoSize){
    Board *board = (Board *)malloc(sizeof(Board));
    scanf("%s", board->name);

    board->boardSize = bingoSize;
    board->row_pick = (int*)calloc(bingoSize, sizeof(int));
    board->column_pick = (int*)calloc(bingoSize, sizeof(int));
    board->diagonal[0] = 0;
    board->diagonal[1] = 0;
    board->data = (Position *)malloc(sizeof(Position) * bingoSize * bingoSize);

    for(int bingoRow = 0; bingoRow < bingoSize; bingoRow++){
        for(int bingoColumn = 0; bingoColumn < bingoSize; bingoColumn++){
            int temp;
            scanf("%d", &temp);
            board->data[temp - 1].x = bingoRow;
            board->data[temp - 1].y = bingoColumn;
        }
    }
    return board;
}

bool win(Board *people, Position numPlace){
    return (people->row_pick[numPlace.x] == people->boardSize) ||
            (people->column_pick[numPlace.y] == people->boardSize) ||
            (numPlace.x == numPlace.y && people->diagonal[0] == people->boardSize) ||
            (numPlace.x + numPlace.y == people->boardSize - 1 && people->diagonal[1] == people->boardSize);
}
 
bool get_number(Board* people, int target){
    Position numPlace = people->data[target];
    //get the target 
    people->column_pick[numPlace.y]++;
    people->row_pick[numPlace.x]++;
    if(numPlace.x == numPlace.y)
        people->diagonal[0]++;
    if(numPlace.x + numPlace.y == people->boardSize - 1)
        people->diagonal[1]++;

    return win(people, numPlace);
}

void destroyBoard(Board *board){
    free(board->data);
    free(board);
}