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
 
bool get_number(Board *data, int target, int bingo_size);
 
int main(){
    int people_num, bingo_size;
    scanf("%d%d", &people_num, &bingo_size);
 
    Board* record = (Board*)malloc(sizeof(Board) * people_num);
    for(int i = 0; i < people_num; i++){
        scanf("%s", record[i].name);
 
        record[i].row_pick = (int*)calloc(bingo_size, sizeof(int));
        record[i].column_pick = (int*)calloc(bingo_size, sizeof(int));
        record[i].diagonal[0] = 0;
        record[i].diagonal[1] = 0;
 
        record[i].data = (int(*)[2])malloc(sizeof(int[2]) * bingo_size * bingo_size);
 
        for(int bingo_row = 0; bingo_row < bingo_size; bingo_row++){
            for(int bingo_column = 0; bingo_column < bingo_size; bingo_column++){
                int temp;
                scanf("%d", &temp);
                record[i].data[temp - 1][0] = bingo_row;
                record[i].data[temp - 1][1] = bingo_column;
            }
        }
 
    }
 
    bool end = false;
 
    for(int i = 0; i < bingo_size * bingo_size; i++){
        int input;
        scanf("%d", &input);
 
        if(end)
            continue;
 
        for(int people_index = 0;people_index < people_num; people_index++){
            if(get_number(&record[people_index], input - 1, bingo_size)){
                if(!end)
                    printf("%d", input);
                printf(" %s", record[people_index].name);
 
                end = true;
            }
        }
    }
 
    for(int i = 0; i < people_num; i++){
        free(record[i].data);
    }
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