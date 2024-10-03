#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool recognition(int **matrix, int **pattern, int pattern_size,
    int x, int y, int sum_diff, int mismatch);

int main(){
    int matrix_size, pattern_size, mismatch, sum_diff;
    scanf("%d%d%d%d", &matrix_size, &pattern_size, &mismatch, &sum_diff);

    //輸入資料
    int **matrix = (int**)malloc(sizeof(int*) * matrix_size);
    for(int i = 0; i < matrix_size; i++){
        matrix[i] = (int*)malloc(sizeof(int) * matrix_size);
        for(int j = 0; j < matrix_size; j++)
            scanf("%d", &matrix[i][j]);
    }

    int **pattern = (int**)malloc(sizeof(int*) * pattern_size);
    for(int i = 0; i < pattern_size; i++){
        pattern[i] = (int*)malloc(sizeof(int) * pattern_size);
        for(int j = 0; j < pattern_size; j++)
            scanf("%d", &pattern[i][j]);
    }

    int last_x = -1, last_y = -1;
    for(int i = 0; i <= matrix_size - pattern_size; i++)
        for(int j = 0; j <= matrix_size - pattern_size; j++)
            if(recognition(matrix, pattern, pattern_size,
                 i, j, sum_diff, mismatch)){
                last_x = i;
                last_y = j;
            }
    
    printf("%d %d\n", last_x, last_y);
    

    //free
    for(int i = 0; i < matrix_size; i++)
        free(matrix[i]);
    free(matrix);
    for(int i = 0; i < pattern_size; i++)
        free(pattern[i]);
    free(pattern);

}

bool recognition(int **matrix, int **pattern, int pattern_size,
    int x, int y, int sum_diff, int mismatch){
    
    int sum_pattern = 0;
    int sum_matrix = 0;
    for(int i = 0; i < pattern_size && mismatch >= 0; i++){
        for(int j = 0; j < pattern_size; j++){
            int x_matrix = i + x;
            int y_matrix = j + y;

            if(matrix[x_matrix][y_matrix] != pattern[i][j])
                mismatch--;
            
            sum_matrix += matrix[x_matrix][y_matrix];
            sum_pattern += pattern[i][j];

        }
    }

    if(mismatch < 0 || abs(sum_pattern - sum_matrix) > sum_diff)
        return false;
    else    
        return true;
}
