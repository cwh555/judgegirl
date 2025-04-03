#include "Bingo.h"
#include <stdio.h>
#include <stdbool.h>

struct game{
    int peopleNum, bingoSize;
    bool gameEnd;
    Board **record;
};


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

void endGame(Game *game){
    for(int i = 0; i < game->peopleNum; i++)
        destroyBoard(game->record[i]);
    free(game->record);
    free(game);
}

bool playOneBingo(Game *game, const int choice, int peopleIndex){
    if(get_number(game->record[peopleIndex], choice - 1)){
        if(!game->gameEnd)
            printf("%d", choice);
        printf(" %s", getName(game->record[peopleIndex]));

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