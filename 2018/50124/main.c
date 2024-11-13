#include "validMoveNum.h"
#include "nextMove.h"
#include <stdio.h>


int main(){
    int size, k;
    scanf("%d %d", &size, &k);

    int board[100][100] = {0};
    
    int position[k][2];
    for(int i = 0; i < k; i++){
        scanf("%d %d", &position[i][0], &position[i][1]);
        board[position[i][0]][position[i][1]] = ( i + 1 ) * 10000;
    }

    int move[8][2] = {{-2,1},{-1,2},{1,2},{2,1},
                    {2,-1},{1,-2},{-1,-2},{-2,-1}};

    int move_num = 1;
    while(move_num > 0){
        move_num = 0;
        for(int i = 0; i < k; i++){
            int dir = nextMove(position[i][0], position[i][1], size, board);

            if(dir == -1)
                continue;
            else{
                board[position[i][0] + move[dir][0]][position[i][1] + move[dir][1]] =\
                    board[position[i][0]][position[i][1]] + 1;
                position[i][0] += move[dir][0];
                position[i][1] += move[dir][1];

                move_num++;
            }
        
        }
    }

    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            printf("%d%c", board[i][j], " \n"[j == size - 1]);

}