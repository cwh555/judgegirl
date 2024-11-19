#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct rectangle{
    int w, l;
    int value;
}Rectangle;

typedef struct solution{
    int num;
    int value_sum;
}Solution;

bool better_solution(Solution *best, Solution now){
    return((best->num < now.num) ||
        (best->num == now.num && best->value_sum < now.value_sum));
}

bool canput(Rectangle *now, Rectangle *top){
    return ((now->l <= top->l && now->w <= top->w) ||
            (now->w <= top->l && now->l <= top->w));
}


void find_solution(int data_num, int index_now, Rectangle *data,
    Rectangle *top, Solution now, Solution *best){
    
    if(index_now >= data_num){
        if(better_solution(best, now)){
            best->num = now.num;
            best->value_sum = now.value_sum;
        }
        return;
    }
    else if(data_num - index_now + now.num < best->num)
        return;
    
    //put or not put
    if(canput(&data[index_now], top)){
        now.num++;
        now.value_sum += data[index_now].value;

        find_solution(data_num, index_now + 1, data, &data[index_now], now, best);

        now.num--;
        now.value_sum -= data[index_now].value;
    }

    find_solution(data_num, index_now + 1, data, top, now, best);
    return;
}


int main(){
    int n;
    scanf("%d", &n);
    Rectangle data[n];

    for(int i = 0; i < n; i++){
        scanf("%d %d", &data[i].l, &data[i].w);
        data[i].value = i;
    }

    Solution best = {.num = 0, .value_sum = 0};
    Solution now = {.num = 0, .value_sum = 0};
    Rectangle top = {.w = 1005, .l = 1005};

    find_solution(n, 0, data, &top, now, &best);

    printf("%d %d\n", best.num, best.value_sum);
}