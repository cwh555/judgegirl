#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
 
typedef struct board{
    char name[100];
    int (*data)[2]; //紀錄index所在的位置
    int* row_pick; //紀錄每列有幾個已經被選擇
    int* column_pick;   //紀錄每行有幾個已經被選擇
    int diagonal[2];   //紀錄右下、左下對角線
}Board;

Board *initBoard(const int bingoSize){
    Board *board = (Board *)malloc(sizeof(Board));
    scanf("%s", board->name);

    board->row_pick = (int*)calloc(bingoSize, sizeof(int));
    board->column_pick = (int*)calloc(bingoSize, sizeof(int));
    board->diagonal[0] = 0;
    board->diagonal[1] = 0;
    board->data = (int(*)[2])malloc(sizeof(int[2]) * bingoSize * bingoSize);

    for(int bingoRow = 0; bingoRow < bingoSize; bingoRow++){
        for(int bingoColumn = 0; bingoColumn < bingoSize; bingoColumn++){
            int temp;
            scanf("%d", &temp);
            board->data[temp - 1][0] = bingoRow;
            board->data[temp - 1][1] = bingoColumn;
        }
    }
    return board;
}

bool get_number(Board *data, int target, int bingo_size);

bool playOneBingo(const int people_num, const int bingo_size, const bool gameEnd,
                    const int choice, Board *board){

    if(get_number(board, choice - 1, bingo_size)){
        if(!gameEnd)
            printf("%d", choice);
        printf(" %s", board->name);

        return true;
    }
    return false;
}

int main(){
    int people_num, bingo_size;
    scanf("%d%d", &people_num, &bingo_size);
    
    Board **record = (Board **)malloc(sizeof(Board*) * people_num);
    for(int i = 0; i < people_num; i++)
        record[i] = initBoard(bingo_size);
    
    bool end = false;
 
    for(int i = 0; i < bingo_size * bingo_size; i++){
        int input;
        scanf("%d", &input);
 
        if(end)
            continue;
 
        for(int people_index = 0;people_index < people_num; people_index++)
            end |= playOneBingo(people_num, bingo_size, end, input, record[people_index]);
    }
 
    for(int i = 0; i < people_num; i++)
        free(record[i]->data);
    free(record);
 
    return 0;
}   
 
bool get_number(Board* people, int target, int bingo_size){
    //找到此數字的位置
    int x = people->data[target][0];
    int y = people->data[target][1];
 
    //檢查連線
    if(++people->column_pick[y] == bingo_size)
        return true;
    if(++people->row_pick[x] == bingo_size)
        return true;
    if(x == y && ++people->diagonal[0] == bingo_size)
        return true;
    if(x + y == bingo_size - 1 && ++people->diagonal[1] == bingo_size)
        return true;
 
 
 
 
    return false;
}