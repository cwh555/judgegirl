#include <stdio.h>

int len(int data, int *msb){
    int len = 1;
    while(data >= 10){
        len++;
        data /= 10;
    }

    *msb = data;

    return len;
}

int main(){
    int num;
    int prev;
    int max_len = 0;
    int len_now = 0;
    
    //init
    scanf("%d", &num);
    len_now = len(num, &prev);
    max_len = len_now;
    prev = num % 10;

    while(scanf("%d", &num) != EOF){
        int msb, data_len;
        data_len = len(num, &msb);

        if(msb != prev){
            if(max_len < len_now)
                max_len = len_now;
            len_now = 0;
        }

        prev = num % 10;
        len_now += data_len;
    }

    if(len_now > max_len)
        max_len = len_now;
    printf("%d\n", max_len);
}