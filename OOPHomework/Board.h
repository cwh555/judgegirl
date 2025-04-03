#ifndef BOARD_H
#define BOARD_H

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


Board *initBoard(const int bingoSize);
bool get_number(Board *data, int target);
void destroyBoard(Board *board);
bool win(Board *people, Position numPlace);
#endif
