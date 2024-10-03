#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


int live_num(bool** map, int size, int x, int y);



int main(){
    int size, step;
    scanf("%d %d", &size, &step);

    //輸入初始狀態
    bool (***map) = (bool(***))malloc(sizeof(bool(**)) * 2);
    
    for(int k = 0; k < 2; k++){ 
        map[k] = (bool**)malloc(sizeof(bool*) * size);
        for(int i = 0; i < size; i++){
            map[k][i] = (bool(*))calloc(size, sizeof(bool));
            if(k == 0){ 
                for(int j = 0; j < size; j++){
                    int temp;
                    scanf("%d", &temp);
                    map[k][i][j] = (temp == 1);
                }
            }
        }
    }       

    #ifdef debug
    printf("check input data\n");
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++)
            printf("%d ", map[0][i][j] ? 1 : 0);   
        printf("\n");
    }
    #endif

    //record live time
    int **alive = (int**)malloc(sizeof(int*) * size);
    for(int i = 0; i < size; i++){
        alive[i] = (int *)malloc(sizeof(int) * size);
        for(int j = 0; j < size; j++)
            alive[i][j] = (map[0][i][j] ? 1 : 0);
    }
    //simulation
    int from = 0, to = 1;
    while(step--){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                int live = live_num(map[from], size, i, j);
                if(map[from][i][j] && (live == 2 || live == 3))
                    map[to][i][j] = true;
                else if(!map[from][i][j] && live == 3)
                    map[to][i][j] = true;
                else 
                    map[to][i][j] = false;
                
                //record alive
                if(map[to][i][j])
                    alive[i][j]++;
            }
        }
        
        from = (from == 1 ? 0 : 1);
        to = (from == 1 ? 0 : 1);
    }

    //output simulation
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            printf("%d%c", (map[from][i][j] ? 1 : 0), " \n"[j == size - 1]);   
    

    //output max
    int max_x = 0, max_y = 0, max_alive = alive[0][0];
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            if(alive[i][j] >= max_alive){
                max_alive = alive[i][j];
                max_x = i;
                max_y = j;
            }
    printf("%d %d\n", max_x + 1, max_y + 1);

}

int live_num(bool** map, int size, int x, int y){
    int count = 0;
    int x_dir[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int y_dir[8] = {1, 1, 1, 0, 0, -1, -1, -1};
    for(int dir = 0; dir < 8; dir++){
        int x_next = x + x_dir[dir];
        int y_next = y + y_dir[dir];

        if(x_next >= 0 && x_next < size && y_next >= 0 && y_next < size 
            && map[x_next][y_next])
            count += 1;
    }

    return count;
}