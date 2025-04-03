#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Bingo.h"

int main(){
    Game *game = initGame();
    
    for(int i = 0; i < game->bingoSize * game->bingoSize; i++)
        OneRound(game);
 
    for(int i = 0; i < game->peopleNum; i++)
        destroyBoard(game->record[i]);
    free(game->record);
 
    return 0;
}