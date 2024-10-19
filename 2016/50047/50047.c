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
    //recursion
    if(N == 0){
        //copy data to outcome
        for(int i = 0; i < 50; i++)
            for(int j = 0; j < 50; j++)
                outcome[i][j] = grid[i][j];
 
        return;
    }
 
    for(int row = 0; row < 50; row++){
        for(int column = 0; column < 50; column++){
            int healthy = neighbor_healthy(grid, row, column);
            outcome[row][column] = grid[row][column];
 
            switch ((grid[row][column])){
                case 0: 
                    //dead
                    if(healthy == 3)
                        outcome[row][column] = 2;
                    break;
                case 1:
                    //dying
                    if(healthy == 2)
                        outcome[row][column] = 2;
                    break;
                case 2:
                    //healthy
                    if(healthy < 2)
                        outcome[row][column] = 0;
                    else if(healthy > 3)
                        outcome[row][column] = 1;
                    break;
                default:
                    fprintf(stderr, "cell status error\n");
                    exit(-1);
            }
        }
    }
 
    //next time
    game_of_cell(outcome, grid, N - 1);
    return;
 
}