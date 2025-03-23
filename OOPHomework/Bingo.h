#include <stdbool.h>

typedef struct board{
    char name[100];
    int (*data)[2]; //紀錄index所在的位置
    int* row_pick; //紀錄每列有幾個已經被選擇
    int* column_pick;   //紀錄每行有幾個已經被選擇
    int diagonal[2];   //紀錄右下、左下對角線
}Board;


Board *initBoard(const int bingoSize);
bool get_number(Board *data, int target, int bingo_size);
bool OneRound(const int bingo_size, const int people_num, Board **record, bool gameEnd);
bool playOneBingo(const int people_num, const int bingo_size, 
    const bool gameEnd, const int choice, Board *board);

