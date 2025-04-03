#ifndef BINGO_H_
#define BINGO_H_

#include <stdbool.h>
#include <stdlib.h>
#include "Board.h"

typedef struct game{
    int peopleNum, bingoSize;
    bool gameEnd;
    Board **record;
}Game;

Game *initGame();
void playGame(Game *game);
void endGame(Game *game);
void OneRound(Game *game);
bool playOneBingo(Game *game, const int choice, int peopleIndex);

#endif