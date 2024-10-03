#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


void swap(int *a, int *b);
bool check_end(int table[4][4]);

int main(){
    int table[4][4];
    int zero_row, zero_column;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            scanf("%d", &table[i][j]);
            if(table[i][j] == 0){
                zero_row = i;
                zero_column = j;
            }
        }
    }

    #ifdef debug
    printf("\nzero at %d %d\n", zero_row, zero_column);
    #endif

    bool end = false;
    int end_move = -1;
    int move;
    int x_dir[4] = {1, -1, 0, 0};
    int y_dir[4] = {0, 0, 1, -1};
    while(scanf("%d", &move) != EOF && move != 0){
        if(end)
            continue;

        bool find = false;

        int next_x, next_y;
        for(int dir = 0; dir < 4 && !find; dir++){
            next_x = zero_row + x_dir[dir];
            next_y = zero_column + y_dir[dir];

            if(next_x < 0 || next_y < 0 || next_x >= 4 || next_y >= 4)
                continue;
            
            if(move == table[next_x][next_y])
                find = true;
        }

        if(!find){
            continue;
        }
        else{
            swap(&table[zero_row][zero_column], &table[next_x][next_y]);
            zero_row = next_x; 
            zero_column = next_y;
            if(check_end(table)){
                end_move = move;
                end = true;
            }
        }

    }

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++)
            printf("%d%c", table[i][j], " \n"[j == 3]);
    }
    if(end)
        printf("1 %d", end_move);
    else
        printf("0");


}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;

    return;
}

bool check_end(int table[4][4]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(table[i][j] != (i * 4 + j + 1) % 16)
                return false;
        }
    }

    return true;
}