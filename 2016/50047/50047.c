#include "game_of_cell.h"
#include <stdio.h>
#include <stdlib.h>
 
int neighbor_healthy(int grid[50][50], int row, int column){
    int dir_x[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dir_y[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
 
    int healthy = 0;
    for(int dir = 0; dir < 8; dir++){
        int neighbor_row = row + dir_x[dir];
        int neighbor_column = column + dir_y[dir];
 
        //check the bound
        if(neighbor_column < 0 || neighbor_column >= 50 || neighbor_row < 0 || neighbor_row >= 50)
            continue;
 
        //check status
        if(grid[neighbor_row][neighbor_column] == 2)
            healthy ++;
    }
 
    return healthy;
}
 
void game_of_cell(int grid[50][50],int outcome[50][50],int N){
    int record[50][50];
    int status_change[3][9] = {
        {0, 0, 0, 2, 0, 0, 0, 0, 0, 0},
        {1, 1, 2, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 2, 2, 1, 1, 1, 1, 1, 1}
    };
 
    //copy data
    for(int i = 0; i < 50; i++)
        for(int j = 0; j < 50; j++)
            record[i][j] = grid[i][j];
 
    for(int time = 0; time < N; time++){
        //record life num 
        int life[50][50] = {0};
        for(int row = 0; row < 50; row++)
            for(int column = 0; column < 50; column++)
                life[row][column] = neighbor_healthy(record, row, column);
 
        for(int i = 0; i < 50; i++)
            for(int j = 0; j < 50; j++)
                record[i][j] = status_change[record[i][j]][life[i][j]];
 
 
 
    }
 
    //copy data 
    for(int i = 0; i < 50; i++)
        for(int j = 0; j < 50; j++)
            outcome[i][j] = record[i][j];
 
    return;
 
}