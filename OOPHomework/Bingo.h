#ifndef BINGO_H_
#define BINGO_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct position{
    int x, y;
}Position;

typedef struct board{
    char name[100];
    Position *data; //紀錄index所在的位置
    int* row_pick; //紀錄每列有幾個已經被選擇
    int* column_pick;   //紀錄每行有幾個已經被選擇
    int diagonal[2];   //紀錄右下、左下對角線
    int boardSize;
}Board;

typedef struct game{
    int peopleNum, bingoSize;
    bool gameEnd;
    Board **record;
}Game;

Game *initGame();
void playGame(Game *game);
void endGame(Game *game);

Board *initBoard(const int bingoSize);
bool get_number(Board *data, int target);
void OneRound(Game *game);
bool playOneBingo(Game *game, const int choice, int peopleIndex);

void destroyBoard(Board *board);

#endif