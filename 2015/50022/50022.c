#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
 
 
bool try(int **matrix, int num_now, int *row_sum, int *column_sum, int row, int column, int *, int *);
 
int main(){
    int row, column;
    while(scanf("%d %d", &row, &column) == 2){
        int *row_sum = (int*)malloc(sizeof(int) * row);
        for(int i = 0; i < row; i++)
            scanf("%d", &row_sum[i]);
        int *column_sum = (int*)malloc(sizeof(int) * column);
        for(int i = 0; i < column; i++)
            scanf("%d", &column_sum[i]);
 
        //初始化要填的matrix
        int **matrix = (int**)malloc(sizeof(int*) * row);
        for(int i = 0; i < row; i++)
            matrix[i] = (int*)calloc(column, sizeof(int));
 
        int *row_left = (int*)malloc(sizeof(int) * row);
        for(int i = 0; i < row; i++)
            row_left[i] = column;
        int *column_left = (int*)malloc(sizeof(int) * column);
        for(int i = 0; i < column; i++)
            column_left[i] = row;
 
        if(!try(matrix, row * column, row_sum, column_sum, row, column, row_left, column_left))
            printf("no solution\n");
 
        free(row_sum);
        free(row_left);
        free(column_left);
        free(column_sum);
        for(int i = 0; i < row; i++)
            free(matrix[i]);
        free(matrix);
    }
 
 
}
 
bool try(int **matrix, int num_now, int *row_sum, int *column_sum, int row, int column, int *row_left, int *column_left){
    //終止條件
    if(num_now == 0){
        //check
        for(int i = 0; i < row; i++)
            for(int j = 0; j < column; j++)
                printf("%d%c", matrix[i][j], " \n"[j == column - 1]);
 
        return true;
    }
 
 
    bool solve = false;
    //窮舉所有此數字放置位置
    for(int i = 0; i < row && !solve; i++){
        for(int j = 0; j < column && !solve; j++){
            int row_now_sum = row_sum[i];
            int column_now_sum = column_sum[j];
 
            if(matrix[i][j] == 0 && num_now <= row_now_sum && num_now <= column_now_sum){
                //遞迴
                row_sum[i] -= num_now;
                column_sum[j] -= num_now;
                matrix[i][j] = num_now;               
                row_left[i] --;
                column_left[j] --;
 
 
                if((row_left[i] == 0 && row_sum[i] != 0) || (row_left[i] != 0 && row_sum[i] == 0));
                else if((column_left[j] == 0 && column_sum[j] != 0) || (column_left[j] != 0 && column_sum[j] == 0));
                else
                    solve = try(matrix, num_now - 1, row_sum, column_sum, row, column, row_left, column_left);
 
                //變回來
                row_sum[i] += num_now;
                column_sum[j] += num_now;
                matrix[i][j] = 0;
                row_left[i]++;
                column_left[j]++;
 
            }
 
        }
 
    }
 
    return solve;
 
}