#include "validMoveNum.h"

int nextMove(int r, int c, int n, int visited[100][100]){
    int move[8][2] = {{-2,1},{-1,2},{1,2},{2,1},
                        {2,-1},{1,-2},{-1,-2},{-2,-1}};

    int min = 10;
    int min_index = -1;

    for(int i = 0; i < 8; i++){
        int num = validMoveNum(r + move[i][0], c + move[i][1], n, visited);

        if(num == -1)
            continue;
        
        if(min > num){
            min = num;
            min_index = i;
        }
    }

    return min_index;

}