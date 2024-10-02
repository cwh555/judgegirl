#include <stdlib.h>
#include <stdio.h>
 
 
int main(){
    int k;
    scanf("%d", &k);
 
    int len_now = 0;
    int len_before = 0;
    int alternate_len_now = 0;
    int max_len = 0;
 
    int input = 1;
    int before = 1;
    //輸入第一個數字
    scanf("%d", &input);
    before = input;
    len_now = 1;
    while(scanf("%d", &input) != EOF && input != 0){
 
 
        if(input * before > 0){
            //沒變號
            len_now++;
        }
        else{
            //變號
            len_before = len_now;
            len_now = 1;
        }
 
        #ifdef debug
        printf("input %d before %d len_now %d len_before %d\n", input, before, len_now, len_before);
        #endif
 
        //第一次更新alternating_len_now
        if(alternate_len_now == 0 && before > 0 && input < 0 && len_before >= k)
            alternate_len_now = k;
        else if(input > 0 && len_before == k && len_now == k){
            alternate_len_now += 2 * k;
            if(alternate_len_now > max_len)
                max_len = alternate_len_now;
        }
        else if(len_now > k)
            alternate_len_now = 0;
 
        before = input;
    }
 
    printf("%d\n", max_len);
 
    return 0;
}