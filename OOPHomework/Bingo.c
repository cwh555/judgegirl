#include "Bingo.h"
#include <stdio.h>
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

bool playOneBingo(const int people_num, const bool gameEnd, 
        const int choice, Board *board){

    if(get_number(board, choice - 1)){
        if(!gameEnd)
            printf("%d", choice);
        printf(" %s", board->name);

        return true;
    }
    return false;
}

bool OneRound(const int people_num, Board **record, bool gameEnd){
    int input;
    scanf("%d", &input);

    //no need to play
    if(gameEnd)
        return true;

    for(int people_index = 0; people_index < people_num; people_index++)
        gameEnd |= playOneBingo(people_num, gameEnd, input, record[people_index]);
    return gameEnd;
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