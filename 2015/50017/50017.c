#include "expression.h"
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>


enum {
    ADD = '+', MINUS = '-', MUL = '*', DIV = '/'
};

int caculate(int opd1, int opr, int opd2){
    switch(opr){
        case '+':
            return opd1 + opd2;
        case '-':
            return opd1 - opd2;
        case '*':
            return opd1 * opd2;
        case '/':
            return opd1 / opd2;
    }
}

int expression_eval(char *string, int *length){
    if(isdigit(string[0])){
        *length = 1;
        return (int)(string[0] - '0');
    }
    else if(string[0] == '-'){
        int value =  -expression_eval(string + 1, length);
        (*length) ++;
        return value;
    }
    else if(string[0] == '('){
        int len;
        int value1 =  expression_eval(string + 1, &len);
        int opr = string[len + 1];
        *length = len + 1;
        
        #ifdef debug
            printf("value1 : %d\n", value1);
            printf("opr %d\n", opr);
            printf("length after value1: %d\n", *length);
        #endif

        int value2 = expression_eval(string + len + 2, &len);
        *length += len + 1;

        #ifdef debug
            printf("value2: %d\n", value2);
        #endif

        assert(string[*length] == ')');
        return caculate(value1, opr, value2);
    }
    else if(string[0] == ')'){
        return 0;
    }
    


}

int expression(char *string){
    int len;
    return expression_eval(string, &len);
}
