#include <stdlib.h>
#include "split.h"

void split(int A[], int *a[], int *head[], int k){
    //init
    int *tail = (int *)malloc(sizeof(int) * k); //record the last index of each class
    for(int i = 0; i < k; i++){
        head[i] = NULL;
    }
    
    int end = 0;
    for(int i = 0; !end; i++){
        if(a[i] == NULL)
            end = 1;
        
        int class = A[i] % k;
        if(head[class] == NULL)
            head[class] = &A[i];
        else
            a[tail[class]] = &A[i];

        tail[class] = i;
    }

    for(int i = 0; i < k; i++)
        if(head[i] != NULL)
            a[tail[i]] = NULL;

    return;

}