#include "game_of_cell.h"
#include <stdio.h>
#include <stdlib.h>
 
int neighbor_healthy(int grid[52][52], int row, int column){
    int dir_x[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dir_y[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
 
    int healthy = 0;
    for(int dir = 0; dir < 8; dir++){
        int neighbor_row = row + dir_x[dir];
        int neighbor_column = column + dir_y[dir];
 
 
 
        //check status
        healthy += (grid[neighbor_row][neighbor_column] / 2); 
    }
 
    return healthy;
}
 
void game_of_cell(int grid[50][50],int outcome[50][50],int N){
    int status_change[3][9] = {
        {0, 0, 0, 2, 0, 0, 0, 0, 0},
        {1, 1, 2, 1, 1, 1, 1, 1, 1},
        {0, 0, 2, 2, 1, 1, 1, 1, 1}
    };
 
    //copy data
    int bound_record[52][52] = {0};
    for(int i = 1; i <= 50; i++)
        for(int j = 1; j <= 50; j++)
            bound_record[i][j] = grid[i - 1][j - 1];
 
    for(int time = 0; time < N; time++){
        //record life num 
        int life[52][52] = {0};
        for(int row = 1; row <= 50; row++)
            for(int column = 1; column <= 50; column++)
                life[row][column] = neighbor_healthy(bound_record, row, column);
 
        for(int i = 1; i <= 50; i++)
            for(int j = 1; j <= 50; j++)
                bound_record[i][j] = status_change[bound_record[i][j]][life[i][j]];
 
 
 
    }
 
    //copy data 
    for(int i = 1; i <= 50; i++)
        for(int j = 1; j <= 50; j++)
            outcome[i - 1][j - 1] = bound_record[i][j];
 
    return;
 
}