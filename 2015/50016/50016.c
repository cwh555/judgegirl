#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool solve(int puzzle[4][4], int move_num, int right_position, int zero_position);


int main(){
    int move_num;
    while(scanf("%d", &move_num) != EOF){
        int puzzle[4][4];

        int right_position = 0;     //紀錄有幾著在正確的位置
        int zero_position = 0;      //紀錄0的位置（攤成一維紀錄 從0開始）
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++){
                scanf("%d", &puzzle[i][j]);
                if(puzzle[i][j] == 1 + i * 4 + j)
                    right_position++;
                if(puzzle[i][j] == 0)
                    zero_position = i * 4 + j;
            }


        if(solve(puzzle, move_num, right_position, zero_position))
            printf("1\n");
        else
            printf("0\n");
        
        


    } 



}


bool solve(int puzzle[4][4], int move_num, int right_position, int zero_position){
    //遞迴終止條件
    if(right_position == 15)
        return true;
    else if(15 - right_position > move_num)
        return false;

    //遞迴0的所有移動方式
    int x_dir[4] = {-1, 1, 0, 0};
    int y_dir[4] = {0, 0, 1, -1};

    int x_zero = zero_position / 4;
    int y_zero = zero_position % 4; 

    bool done = false;
    for(int dir = 0; dir < 4 && !done; dir++){
        int x_move = x_zero + x_dir[dir];
        int y_move = y_zero + y_dir[dir];

        //超出邊界continue
        if(x_move < 0 || x_move >= 4 || y_move < 0 || y_move >= 4)
            continue;
        
        //遞迴往下
        //更新right_position
        int right_change = 0;
        if(puzzle[x_move][y_move] == 1 + x_move * 4 + y_move)
            right_change = -1;
        else if(puzzle[x_zero][y_zero] == 1 + x_move * 4 + y_move)
            right_change = 1;
        
        //移動
        puzzle[x_zero][y_zero] = puzzle[x_move][y_move];        
        puzzle[x_move][y_move] = 0;

        //遞迴
        if(solve(puzzle, move_num - 1, right_position + right_change, x_move * 4 + y_move))
            done = true;
        else{
            //移回來
            puzzle[x_move][y_move] = puzzle[x_zero][y_zero];
            puzzle[x_zero][y_zero] = 0;
        }
    }


    return done;

}