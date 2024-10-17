#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define detail

enum{
    DOWN, UP, RIGHT, LEFT
};

typedef struct position{
    int row, column;
}Position;

bool move(Position *record, int *head_index, int len, int dir, int row, int column){
    //change head to next position
    Position head = record[*head_index];
    switch(dir){
        case UP:
            head.row--;
            break;
        case DOWN:
            head.row++;
            break;
        case RIGHT:
            head.column++;
            break;
        case LEFT:
            head.column--;
            break;
        default:
            //dir error
            return false;
    }
    
    #ifdef debug
    printf("after dir\n");
    #endif

    //check the bound
    if(head.row < 0 || head.row >= row || head.column < 0 || head.column >= column)
        return false;
    //check whether touching itself
    for(int i = 0; i < len; i++)
        if(head.row == record[i].row && head.column == record[i].column)
            return false;

    //move
    (*head_index) = (*head_index - 1 + len) % len ;
    record[*head_index] = head;

    #ifdef detail
    //put it on the grid
    bool **grid = (bool**)malloc(sizeof(bool*) * row);
    for(int i = 0; i < row; i++)
        grid[i] = (bool*)calloc(column, sizeof(bool));
    
    for(int i = 0; i < len; i++)
        grid[record[i].row][record[i].column] = 1;

    //print
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++)
            printf("%d", (grid[i][j] ? 1 : 0));
        printf("\n");
    }
    for(int i = 0; i < row; i++)
        free(grid[i]);
    free(grid);

    #endif


    return true;
}

int main(){
    int row, column;
    scanf("%d %d", &row, &column);
    Position head, end;
    scanf("%d%d", &head.row, &head.column);
    scanf("%d%d", &end.row, &end.column);

    //initiate
    int len = abs(head.row - end.row) + abs(head.column - end.column) + 1;
    //紀錄位置
    Position *record = (Position*)malloc(sizeof(Position) * len);
   
    if(head.row == end.row){
        int dir = (end.column > head.column ? 1 : -1);
        for(int i = 0; i < len; i++){
            record[i].row = head.row;
            record[i].column = head.column + i * dir;
        }
    }
    else{
        int dir = (end.row > head.row ? 1 : -1);
        for(int i = 0; i < len; i++){
            record[i].column = head.column;
            record[i].row = head.row + i * dir;
        }
    }

    int head_index = 0;
    
    int action_num;
    scanf("%d", &action_num);
    bool rule = true;
    for(int i = 0; i < action_num; i++){
        int dir;
        scanf("%d", &dir);

        if(rule){
            rule = move(record, &head_index, len, dir, row, column);
            #ifdef debug
                printf("move\n");
            #endif
        }
    }

    //put it on the grid
    bool **grid = (bool**)malloc(sizeof(bool*) * row);
    for(int i = 0; i < row; i++)
        grid[i] = (bool*)calloc(column, sizeof(bool));
    
    for(int i = 0; i < len; i++)
        grid[record[i].row][record[i].column] = 1;

    //print
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++)
            printf("%d", (grid[i][j] ? 1 : 0));
        printf("\n");
    }

    //free
    free(record);
    for(int i = 0; i < row; i++)
        free(grid[i]);
    free(grid);

}