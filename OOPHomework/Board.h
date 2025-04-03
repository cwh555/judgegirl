#ifndef BOARD_H
#define BOARD_H

typedef struct position Position;
typedef struct board Board;

Board *initBoard(const int bingoSize);
bool get_number(Board *data, int target);
void destroyBoard(Board *board);
bool win(Board *people, Position numPlace);
char *getName(Board *people);
#endif
