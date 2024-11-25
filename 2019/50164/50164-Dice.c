#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


int check_dice(int *data, int max_column){
    //check row
    if(*data + *(data + 2) != 7 || *(data + 1) + *(data + 3) != 7)
        return 0;
    //check the other
    bool appear[7] = {0};
    for(int i = 0; i < 4; i++){
        if(!appear[*(data + i)])
            appear[*(data + i)] = true;
        else
            return 0;
    }

    int sum = 0;
    for(int i = 0; i < 4; i++){
        int value1 = *(data - max_column + i);
        if(!appear[value1]){
            for(int j = 0; j < 4; j++){
                int value2 = *(data + max_column + j);
                if(value1 + value2 == 7)
                    sum++;
            }
        }
    }

    return sum;
}

int main(){
    int max_row, max_column;
    scanf("%d %d", &max_row, &max_column);

    //創造連續區塊
    int *buffer = (int *)malloc(sizeof(int) * max_row * max_column);
    int **data = (int **)malloc(sizeof(int *) * max_row);
    for(int i = 0; i < max_row; i++){
        data[i] = buffer + i * max_column;
        for(int j = 0; j < max_column; j++)
            scanf("%d", &data[i][j]);
    }

    int sum = 0;
    for(int row = 1; row < max_row - 1; row++)
        for(int column = 0; column < max_column - 3; column++)
            sum += check_dice(&data[row][column], max_column);

    printf("%d\n", sum);

    free(data);
    free(buffer);

    return 0;
}