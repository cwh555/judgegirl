#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int func_f(const int a, const int b, const int c, int x){
    return (a * x + b) % c;
}

int func_C(const int a, const int b, const int c, const int d, const int e, int x){
    int num = 0;
    while(x < d || x > e){
        x = func_f(a, b, c, x);
        num++;
    }

    return num;
}

int compare(const void *a, const void *b){
    if(*(int *)a > *(int *)b)
        return 1;
    else
        return -1;
}

bool consecutive(int value[3]){
    //sort
    int temp[3] = {value[0], value[1], value[2]};
    qsort(temp, 3, sizeof(int), compare);

    return (temp[2] - temp[1] == 1) && (temp[1] - temp[0] == 1);
}

int main(){
    int a, b, c, d, e;
    scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);

    int x;
    int value[3] = {-2, -2, -2};
    int input[3];
    bool find = false;
    while(scanf("%d", &x) != EOF){
        if(!find){
            value[0] = value[1];
            value[1] = value[2];
            value[2] = func_C(a, b, c, d, e, x);

            input[0] = input[1];
            input[1] = input[2];
            input[2] = x;

            if(consecutive(value))
                find = true;
        }
    }

    if(find)
        printf("%d %d %d\n", input[0], input[1], input[2]);
    else
        printf("Not found\n");
}