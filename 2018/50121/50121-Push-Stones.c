#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool move_stone(int *energy, int **map, int row, int column,
                int *player_r, int *player_c, int dr, int dc){
    
    //check the sum of stone
    int row_now = *player_r + dr, column_now = *player_c + dc;
    int total_weight = 0;
    while(row_now >= 0 && column_now >= 0 && row_now < row && column_now < column && map[row_now][column_now] != 0){
        total_weight += map[row_now][column_now];
        row_now += dr;
        column_now += dc;
    }
    
    if(total_weight > *energy || row_now == row || column_now == column
        || row_now == -1 || column_now == -1)
        return false;

    //move
    while(row_now != *player_r || column_now != *player_c){
        map[row_now][column_now] = map[row_now - dr][column_now - dc];
        row_now -= dr;
        column_now -= dc;
    }

    (*energy) -= total_weight;

    (*player_r) += dr;
    (*player_c) += dc;

    return true;
}


int main(){
    int row, column;
    scanf("%d %d", &row, &column);

    int **map = (int **)malloc(sizeof(int *) * row);
    for(int i = 0; i < row ;i++)
        map[i] = (int*)calloc(column, sizeof(int));

    int player_r, player_c, energy;
    scanf("%d %d %d", &player_r, &player_c, &energy);

    int stone_num;
    scanf("%d", &stone_num);
    for(int i = 0; i < stone_num; i++){
        int r, c, weight;
        scanf("%d %d %d", &r, &c, &weight);

        map[r][c] = weight;
    }

    int instruction;
    while(scanf("%d", &instruction) != EOF){
        switch(instruction){
            case 0:
                for(int i = 0; i < row; i++)
                    for(int j = 0; j < column; j++)
                        printf("%d%c", (i == player_r && j == player_c ? energy : map[i][j]),
                                " \n"[j == column - 1]);
                break;
            case 1:
                move_stone(&energy, map, row, column, &player_r, &player_c, 0, 1);
                break;
            case 2:
                move_stone(&energy, map, row, column, &player_r, &player_c, 1, 0);
                break;
            case 3:
                move_stone(&energy, map, row, column, &player_r, &player_c, 0, -1);
                break;
            case 4:
                move_stone(&energy, map, row, column, &player_r, &player_c, -1, 0);
                break;    
        }

    }


}