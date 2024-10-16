#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
 
#define debug
 
typedef struct position{
    int row;
    int column;
}Position;
 
void generate_path(Position *path, int row_max, int column_max, int *path_num){
    //從0, 0開始 往上 （向右到底 往下一格 向左到底 向下一格） 循環
    path[0].column = 0;
    path[0].row = 0;
    path[1].column = 0;
    path[1].row = row_max - 1;
    path[2].column = column_max - 1;
    path[2].row = row_max - 1;
    *path_num = 3;
 
    if(column_max == 2){
        path[3].column = 1;
        path[3].row = 0;
        *path_num = 4;
        return ;
    }
 
    for(int i = row_max - 2; i >= 1; i--){
        path[(*path_num)].column = path[(*path_num) - 1].column;
        path[(*path_num)].row = path[(*path_num) - 1].row - 1;
        path[(*path_num) + 1].column = (path[(*path_num)].column == column_max - 1 ? 1 : column_max - 1);
        path[(*path_num) + 1].row = path[(*path_num)].row;
 
        (*path_num) += 2;       
    }
    path[(*path_num)].column = column_max - 1;
    path[(*path_num)++].row = 0;
 
    #ifdef debug
    printf("path\n");
    for(int i = 0; i < *path_num; i++){
        printf("%d %d\n", path[i].column, path[i].row);
    }
    printf("end\n");
    #endif
 
 
    return;
 
 
 
}
 
void print_path(Position start, Position end){
    int dir_x, dir_y;
    if(start.column == end.column)
        dir_x = 0;
    else
        dir_x = (end.column - start.column) / abs(end.column - start.column);
 
    if(start.row == end.row)
        dir_y = 0;
    else
        dir_y = (end.row - start.row) / abs(end.row - start.row);
 
    while(start.column != end.column || start.row != end.row){
        printf("%d %d\n", start.column, start.row);
 
        start.column += dir_x;
        start.row += dir_y;
    }
 
    return;
}
 
int main(){
    int row_max, column_max;
    int row_start, column_start;
    while(scanf("%d%d%d%d", &column_max, &row_max, &column_start, &row_start) == 4){
        assert(row_max % 2 == 0);
 
        Position *path = (Position*)malloc(sizeof(Position) * 2 * (row_max + column_max));
        int path_num = 0;
        generate_path(path, row_max, column_max, &path_num);
 
        //找到起始點在哪一段路徑中
        int index = 0;
        bool bound = false;
        for(int i = 1; i < path_num + 1; i = (i + 1) % path_num){
            //恰在邊界點
            if(path[i].column == column_start && path[i].row == row_start){
                index = i;
                bound = true;
                break;
            }
            else if((column_start - path[i].column) * (column_start - path[i - 1].column) < 0 &&
                    (row_start - path[i].row) * (row_start - path[i - 1].row) < 0){
                //兩點中間
                index = i;
                break;
            }
 
        }
        //位在起始點
        if(column_start == 0 && row_start == 0){
            bound = true;
            index = 0;
        }
 
        Position start;
        start.column = column_start;
        start.row = row_start;
        if(!bound)
            print_path(start, path[index]);
        for(int i = index, count = 0; count < path_num; count++, i = (i+1) % path_num){
            print_path(path[i], path[i + 1]);
        }
        if(!bound)
            print_path(path[(index - 1 + path_num) % path_num], start);
 
        printf("%d %d\n", start.column, start.row);
 
 
        free(path);
 
    }
 
 
 
 
 
}