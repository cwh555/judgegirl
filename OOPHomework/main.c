#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Bingo.h"

int main(){
    Game *game = initGame();
    playGame(game);
    endGame(game);
    return 0;
}