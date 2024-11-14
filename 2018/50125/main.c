#define MAX(a, b) ((a) > (b) ? (a) : (b))

#include "findLength.h"
#include <stdio.h>

int main(){
    int size;
    scanf("%d", &size);

    int matrix[256][256];
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            scanf("%d", &matrix[i][j]);

    int max_len = 0;
    for(int i = 0; i < size; i++){
        //row
        int len = findLength(matrix, size, i, 0, 0, 1);
        max_len = MAX(len, max_len);
        
        //column
        len = findLength(matrix, size, 0, i, 1, 0);
        max_len = MAX(len, max_len);

        //diagonal
        len = findLength(matrix, size, i, 0, 1, 1);
        max_len = MAX(len, max_len);
        len = findLength(matrix, size, 0, i, 1, 1);
        max_len = MAX(len, max_len);

        //anti-diagonal
        len = findLength(matrix, size, i, size - 1, 1, -1);
        max_len = MAX(len, max_len);
        len = findLength(matrix, size, 0, i, 1, -1);
        max_len = MAX(len, max_len);
    }

    printf("%d\n", max_len);
}