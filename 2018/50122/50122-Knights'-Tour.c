#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef struct position{
    int row, column;
}Position;

bool move_chess(int size, int **matrix, Position *chess);
int possible_move(int size, int **matrix, int row, int column);

int main(){
    int size, knight_num;
    scanf("%d %d", &size, &knight_num);

    int **matrix = (int**)malloc(sizeof(int *) * size);
    for(int i = 0; i < size; i++)
        matrix[i] = (int*)calloc(size, sizeof(int));

    Position *chess = (Position *)malloc(sizeof(Position) * knight_num);
    for(int i = 0; i < knight_num; i++){
        scanf("%d %d", &chess[i].row, &chess[i].column);
        matrix[chess[i].row][chess[i].column] = (i + 1) * 10000;
    }

    bool *stop = (bool *)calloc(knight_num, sizeof(bool));
    int act_num = knight_num;

    while(act_num > 0){
        for(int i = 0; i < knight_num; i++){
            if(stop[i])
                continue;
            
            stop[i] = !(move_chess(size, matrix, &chess[i]));
            
            if(stop[i])
                act_num--;
        }
        
    }

    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            printf("%d%c", matrix[i][j], " \n"[j == size - 1]);
    
    for(int i = 0; i < size; i++)
        free(matrix[i]);
    free(stop);
    free(chess);

    return 0;
}

int possible_move(int size, int **matrix, int row, int column){
    if(row < 0 || row >= size || column < 0 || column >= size || matrix[row][column] != 0)
        return 10;

    int dir[8][2] = {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}
                    , {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};

    int count = 0;
    for(int i = 0; i < 8; i++){
        int row_next = row + dir[i][0];
        int column_next = column + dir[i][1];

        if(row_next >= 0 && row_next < size && column_next >= 0 && column_next < size 
            && matrix[row_next][column_next] == 0)
            count++;
    }

    return count;
}

bool move_chess(int size, int **matrix, Position *chess){
    int dir[8][2] = {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}
                    , {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};
    int move_dir = -1;
    int min_poss = 10;
    for(int i = 0; i < 8; i++){
        int poss = possible_move(size, matrix, chess->row + dir[i][0], chess->column + dir[i][1]);

        if(poss < min_poss){
            min_poss = poss;
            move_dir = i;
        }

    }

    if(move_dir == -1){
        //cannot move
        return false;
    }
    else{
        matrix[chess->row + dir[move_dir][0]][chess->column + dir[move_dir][1]] = matrix[chess->row][chess->column] + 1;
        chess->row += dir[move_dir][0];
        chess->column += dir[move_dir][1];

        return true;
    }
}