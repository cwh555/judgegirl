#include "eval.h"

 
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
                    if(opd == 0)
                        return -2147483647;
                    new_value /= opd;
                    break;
                default:
                    return -2147483646;
            }

            opr = exp[i++];
        }

        exp[new_len++] = new_value;
        if(i <= len)
            exp[new_len++] = opr;
    }
    
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
                return -2147483646;

        }
    }

    return ans;
}