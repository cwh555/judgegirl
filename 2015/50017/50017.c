#include "expression.h"
#include <ctype.h>
#include <stdbool.h>

enum {
    ADD, MINUS, MUL, DIV
};

//length為需要計算的長度
int expressionEval(char *string, int *length){

}

int expression(char *string){
    int len = strlen(string);

    int value = 0;
    bool negative = false;
    for(int i = 0; i < len; i++){
        if(isdigit(string[i])){
            value = (string[i] - '0') * (negative ? -1 : 1);
            negative = false;
        }
        else if(string[i] == '-');
            negative = !negative;
    }

    return value;
}

