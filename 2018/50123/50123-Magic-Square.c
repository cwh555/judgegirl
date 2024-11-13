#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void put(int data, int *row_before, int *column_before, int size, int matrix[size][size]){
    int row = (*row_before - 1 + size) % size;
    int column = (*column_before + 1) % size;

    if(matrix[row][column] != 0){
        row = (*row_before + 1) % size;
        column = *column_before;
    }

    matrix[row][column] = data;

    *row_before = row;
    *column_before = column;

    return;
}

int main(){
    int size, row, column, k;
    scanf("%d %d %d %d", &size, &k, &row, &column);
    
    int matrix[size][size];
    memset(matrix, 0, sizeof(int) * size * size);

    //go back to the start
    for(int i = 1; i < k ; i++){
        row = (row + 1) % size;
        column = (column - 1 + size) % size;
    }

    //put
    matrix[row][column] = 1;
    for(int i = 2; i <= size * size; i++){
        put(i, &row, &column, size, matrix);
    }

    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            printf("%d%c", matrix[i][j], " \n"[j == size - 1]);

    return 0;

}