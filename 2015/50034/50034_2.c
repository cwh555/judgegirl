#define SIDEMAX 20
#define LEFT 0
#define RIGHT 1
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
 
int compare(const void *a, const void *b){
    int data1 = *(int*)a;
    int data2 = *(int*)b;
 
    if(data1 > data2)
        return 1;
    else
        return -1;
}
 
bool solve(int put[2][SIDEMAX], bool small_side, int weight[2], int index[2],
            int data[SIDEMAX * 2], int data_num, bool use[]);
 
//提早剪枝
bool try(int index[2], int diff, bool small_side,
            int data[SIDEMAX * 2], int data_num, bool use[]);
 
 
int main(){
    int data_num;
    while(scanf("%d", &data_num) != EOF){
        int data[SIDEMAX] = {0};
        for(int i = 0; i < data_num; i++)
            scanf("%d", &data[i]);
 
        //由小到大
        qsort(data, data_num, sizeof(int), compare);
 
        int put[2][SIDEMAX] = {0};
        int weight[2] = {0};
        int index[2] = {0};
        bool use[SIDEMAX * 2] = {0};
 
        if(!solve(put, 0, weight, index, data, data_num, use))
            printf("N\n");
    }
 
 
 
}
 
bool solve(int put[2][SIDEMAX], bool small_side, int weight[2], int index[2],
            int data[SIDEMAX * 2], int data_num, bool use[]){
    if(index[LEFT] == data_num / 2 && index[RIGHT] == data_num / 2){
        if(weight[0] != weight[1])
            return false;
 
        for(int i = index[LEFT] - 1; i >= 0; i--)
            printf("%d ", put[0][i]);
        printf("_^_");
        for(int i = 0; i < index[RIGHT]; i++)
            printf(" %d", put[1][i]);
        printf("\n");
 
        return true;
    }
    else if(index[small_side] == data_num / 2)
        return false;
 
    //避免重複的重量多次嘗試
    int prev = INT_MIN;
    for(int i = 0; i < data_num; i++){
        if(!use[i] && data[i] != prev){
            prev = data[i];
 
            //放在重量比較小的一邊
            use[i] = true;
            bool new_small_side = small_side;
            put[small_side][index[small_side]] = data[i];
            index[small_side]++;
            weight[small_side] += (index[small_side]) * data[i];
 
            if(weight[small_side] > weight[!small_side])
                new_small_side = !new_small_side;
 
            if(!try(index, weight[new_small_side] - weight[!new_small_side], new_small_side,
                    data, data_num, use)){
                use[i] = false;
                weight[small_side] -= (index[small_side]) * (data[i]);
                index[small_side]--;
            }
            else if(solve(put, new_small_side, weight, index, data, data_num, use))
                return true;
            else{
                //回溯
                use[i] = false;
                weight[small_side] -= (index[small_side]) * (data[i]);
                index[small_side]--;
            }
 
        }
    }
 
 
    return false;
 
 
 
}
 
//提早剪枝
bool try(int index[2], int diff, bool small_side,
            int data[SIDEMAX * 2], int data_num, bool use[]){
    assert(diff <= 0);
 
    //如果可以讓比較小的一邊大於等於另外一邊代表還有機會平衡
    int index_small = index[small_side];
    int index_big = index[!small_side];
 
 
    int put_index = data_num / 2;
    for(int i = data_num - 1; i >= 0 && put_index >= index_small; i--){
        if(!use[i]){
            diff += data[i] * put_index;
            put_index--;
        }
    }
 
    for(int i = 0; i < data_num && index_big < data_num / 2; i++){
        if(!use[i]){
            index_big ++;
            diff -= data[i] * (index_big);
        }
    }
 
    return diff >= 0;
}