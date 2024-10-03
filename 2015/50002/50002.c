#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define debug

int main(){
    int size, step;
    scanf("%d %d", &size, &step);

    //輸入初始狀態
    bool (**map)[2] = (bool(**)[2])malloc(sizeof(bool(*)[2]) * size);
    for(int i = 0; i < size; i++){
        map[i] = (bool(*)[2])calloc(size, sizeof(bool[2]));
        for(int j = 0; j < size; j++){
            int temp;
            scanf("%d", &temp);
            map[i][j][0] = (temp == 1);
        }
    }

    #ifdef debug
    printf("check input data\n");
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++)
            printf("%d ", map[i][j][0] ? 1 : 0);   
        printf("\n");
    }
    #endif


}