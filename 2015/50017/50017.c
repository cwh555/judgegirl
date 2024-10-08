#define FALSENUM -2147483648

#include "expression.h"
#include <ctype.h>
#include <stdbool.h>


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
            if(opd2 == 0)
                return FALSENUM;
            return opd1 / opd2;
        default:
            return FALSENUM;
    }
}

int expression_eval(char *string, int *length, bool first, bool in){
    if(isdigit(string[0]) && (in || string[1] == '\0')){
        *length = 1;
        return (int)(string[0] - '0');
    }
    else if(string[0] == '-'){
        int value =  expression_eval(string + 1, length, first, in);
        
        if(value == FALSENUM)
            return FALSENUM;

        (*length) ++;
        return -value;
    }
    else if(string[0] == '(' && (in || first)){
        int len;
        *length = 1;
        int value1 =  expression_eval(string + (*length), &len, false, true);
        *length += len;
        int opr = string[*length];
        (*length)++;    //經過運算子

        #ifdef debug
            printf("value1 : %d\n", value1);
            printf("opr %d\n", opr);
            printf("length after value1: %d\n", *length);
        #endif

        int value2 = expression_eval(string + (*length), &len, false, true);
        (*length) += len;

        #ifdef debug
            printf("value2: %d\n", value2);
            printf("length after value2: %d\n", *length);
        #endif

        if(string[*length] != ')' || value1 == FALSENUM || value2 == FALSENUM)
            return FALSENUM;
        (*length)++;    //經過後括號

        //後括號後必須結束
        if(!in && string[*length] != '\0')
            return FALSENUM;
            
        return caculate(value1, opr, value2);
    }
    else
        return FALSENUM;
    


}


int expression(char *string){
    int len;
    return expression_eval(string, &len, true, false);
}
 