#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main(){
    int row, column, L;
    scanf("%d %d %d", &L, &row, &column);

    bool **map = (bool**)malloc(sizeof(bool*) * row);
    for(int i = 0; i < row; i++)
        map[i] = (bool*)calloc(column, sizeof(bool));

    bool output = true;
    for(int i = 0; i < L; i++){
        int n;
        scanf("%d", &n);

        int x_before, y_before, x_now, y_now;
        scanf("%d%d", &x_before, &y_before);


        for(int j = 1; j < n; j++){
            scanf("%d %d", &x_now, &y_now);

            if(!output)
                continue;
            

            //越界檢查
            if(x_now < 0 || x_now >= column || y_now < 0 || y_now >= row)
                output = false;
            //線斷檢查
            else if(x_now != x_before && y_now != y_before &&
                    abs(x_now - x_before) != abs(y_now - y_before))
                output = false;

            if(!output){
                printf("ERROR %d %d\n", i + 1, j + 1);
                continue;
            }
            int dir_x , dir_y;
            if(x_before == x_now)
                dir_x = 0;
            else
                dir_x = abs(x_now - x_before) / (x_now - x_before);

            if(y_before == y_now)
                dir_y = 0;
            else
                dir_y = abs(y_now - y_before) / (y_now - y_before);

            while(x_before != x_now || y_before != y_now){
                map[y_before][x_before] = true;

                x_before += dir_x;
                y_before += dir_y;
            }

            map[y_before][x_before] = true;
        }
    }

    for(int i = row - 1; i >= 0 && output; i--){
        for(int j = 0; j < column; j++)
            printf("%d", (map[i][j] ? 1 : 0));
        printf("\n");
    }


    for(int i = 0; i < row; i++)
        free(map[i]);
    free(map);
}  