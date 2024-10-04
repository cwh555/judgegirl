#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
 
int eval(int exp[]) {
    int len = exp[0];
    //僅計算加減 
    int ans = exp[1];
    for(int i = 2; i <= len; i += 2){
        switch(exp[i]){
            case 1:
                ans += exp[i + 1];
                break;
            case 2:
                ans -= exp[i + 1];
                break;
            default:
                fprintf(stderr, "not + or -\n");    
                exit(-1);

        }
    }

    return ans;
}