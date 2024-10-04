#include "setmatrix.h"
#include <stdlib.h>
#include <stdio.h>

void processSetMatrix(int *ptr){
    int index = 0;
    while(ptr[index] != 0)
        printf("%d ", ptr[index++]);
}