#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNSET -2147483647
#define OUT -2147483648


void init(ARRAY *a,  int left, int right){
    a->data = (int*)malloc(sizeof(int) * (right - left + 1));
    for(int i = 0; i < right - left + 1; i++)
        a->data[i] = UNSET;
    a->start_index = left;
    a->end_index = right;
    a->data_num = right - left + 1;
    return;
}

int set(ARRAY *a, int index, int value){
    if(index < a->start_index || index > a->end_index)
        return OUT;
    else{
        a->data[index - a->start_index] = value;
        return 1;
    }
    

}

int get(ARRAY *a, int index){
    if(index < a->start_index || index > a->end_index)
        return OUT;
    else
        //包含unset情況
        return a->data[index - a->start_index];

}
void print(ARRAY *a){
    for(int i = 0; i < a->data_num; i++){
        if(a->data[i] == UNSET)
            printf("No value\n");
        else
            printf("%d\n", a->data[i]);
    }

    return;
}

int compare(const void *a, const void *b){
    if(*(int*)a > *(int*)b)
        return 1;
    else
        return -1;
}

void sort(ARRAY *a){
    qsort(a->data, a->data_num, sizeof(int), compare);

    return ;
}
