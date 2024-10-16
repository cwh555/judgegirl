#define MAXSIDE 10
 
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
 
int compare(const void *a, const void *b){
    int data1 = *(int*)a;
    int data2 = *(int*)b;
 
    if(data1 > data2)
        return 1;
    else
        return -1;
}
 
bool solve(int data[], int data_num, int put[], int index, bool use[]){
    //speed up
    if(index == data_num / 2 + 1){
        //要開始放另外一邊前先檢查
        int temp[MAXSIDE] = {0};
        int temp_index = 0;
        for(int i = 0; i < data_num; i++)
            if(!use[i])
                temp[temp_index++] = data[i];
        assert(temp_index == data_num / 2);
 
        qsort(temp, temp_index, sizeof(int), compare);
        int sum = 0;
        for(int i = 0; i < temp_index; i++)
            sum += (i + 1) * temp[i];
        int left = 0;
        for(int i = 0; i < data_num / 2; i++)
            left += (i + 1) * put[i];
        if(left > sum)
            return false;
    }
    else if(index == data_num){
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