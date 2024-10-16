#define MAXSIDE 10
 
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
 
bool solve(int data[], int data_num, int put[], int index, bool use[]){
    if(index == data_num){
        int left = 0;
        for(int i = 0; i < data_num / 2; i++)
            left += (i + 1) * put[i];
 
        int right = 0;
        for(int j = data_num / 2 + 1; j < data_num; j++)
            right += (j - data_num / 2) * put[j];
 
        if(right != left)
            return false;
        else{
            for(int i = data_num / 2 - 1; i >= 0; i--)
                printf("%d ", put[i]);
            printf("_^_");
            for(int j = data_num / 2 + 1; j < data_num; j++)
                printf(" %d", put[j]);
            printf("\n");
 
            return true;
        }
    }
 
    for(int i = 0; i < data_num; i++){
        if(!use[i]){
            use[i] = true;
            put[index] = data[i];
            if(solve(data, data_num, put, index + 1, use))
                return true;
 
            use[i] = false;       
        }
    }
 
    return false;
 
}
 
 
int main(){
    int size;
    while(scanf("%d", &size) != EOF){
        int data[MAXSIDE * 2];
        for(int i = 0; i < size; i++)
            scanf("%d", &data[i]);
 
        int put[MAXSIDE * 2] = {0};
        bool use[MAXSIDE * 2] = {0};
 
        if(!solve(data, size, put, 0, use))
            printf("N\n");
    }
 
 
}