#include "setmatrix.h"
#include <stdlib.h>
#include <stdio.h>

void processSetMatrix(int **matrix){
    while(*matrix != NULL){
        int *array = *matrix;
        int index = 0;
        while(array[index] != 0)
            printf("%d ", array[index++]);

        matrix++;
    }
}