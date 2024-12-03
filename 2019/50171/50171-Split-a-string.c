#include "splitAndMap.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int minIndex(int len[], int num){
    int min = INT_MAX;
    int minIndex = -1;
    for(int i = 0; i < num; i++){
        if(min > len[i]){
            min = len[i];
            minIndex = i;
        }
    }

    return minIndex;
}


void splitAndMap(char*** ptr, char* str){
    int num = 0;
    while(ptr[num] != NULL)
        num++;

    //init
    for(int i = 0; i < num; i++)
        ptr[i][0] = NULL;

    int *len = (int *)calloc(num, sizeof(int));
    int *cnt = (int *)calloc(num, sizeof(int));
    char *token = strtok(str, "*");
    while(token != NULL){
        int tokenLen = strlen(token);
        int addIndex = minIndex(len, num);

        ptr[addIndex][cnt[addIndex]++] = token;
        len[addIndex] += tokenLen;
        
        token = strtok(NULL, "*");
    }

    free(cnt);
    free(len);

    return;
}