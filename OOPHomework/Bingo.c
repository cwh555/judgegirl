#include "Bingo.h"
#include <stdio.h>
#include <stdbool.h>

Game *initGame(){
    Game *game = (Game *)malloc(sizeof(Game));
    scanf("%d %d", &game->peopleNum, &game->bingoSize);
    game->record = (Board **)malloc(sizeof(Board*) * game->peopleNum);
    for(int i = 0; i < game->peopleNum; i++)
        game->record[i] = initBoard(game->bingoSize);
    game->gameEnd = false;
    return game;
}

void playGame(Game *game){
    for(int i = 0; i < game->bingoSize * game->bingoSize; i++)
        OneRound(game);
    return;
}

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

bool playOneBingo(Game *game, const int choice, int peopleIndex){
    if(get_number(game->record[peopleIndex], choice - 1)){
        if(!game->gameEnd)
            printf("%d", choice);
        printf(" %s", game->record[peopleIndex]->name);

        return true;
    }
    return false;
}

void OneRound(Game *game){
    int input;
    scanf("%d", &input);

    //no need to play
    if(game->gameEnd)
        return;

    for(int people_index = 0; people_index < game->peopleNum; people_index++)
        game->gameEnd |= playOneBingo(game, input, people_index);
    return;
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