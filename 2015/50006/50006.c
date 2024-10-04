#include "eval.h"
#include <stdio.h>
#include <stdlib.h>

#define debug
 
int eval(int exp[]) {
    int len = exp[0];
    //先處理乘除
    int new_len = 0;
    for(int i = 1; i <= len;){
        int new_value = exp[i++];
        int opr = exp[i++];

        while((opr == 3 || opr == 4) && i <= len){
            int opd = exp[i++];
            switch(opr){
                case 3:
                    new_value *= opd;
                    break;
                case 4:
                    new_value /= opd;
                    break;
                default:
                    fprintf(stderr, "impossible\n");
                    exit(-1);
            }

            opr = exp[i++];
        }

        exp[new_len++] = new_value;
        if(i <= len)
            exp[new_len++] = opr;
    }

    #ifdef debug
    printf("after */\n");
    for(int i = 0; i < new_len; i++)
        printf("%d ", exp[i]);
    printf("end\n");
    #endif

    //僅計算加減 
    int ans = exp[0];
    for(int i = 1; i < new_len; i += 2){
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