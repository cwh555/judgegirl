#include <stdio.h>
#include <stdlib.h>

typedef struct function{
    int degree;
    double *data;
}Function;

Function *readFunc(void){
    Function *result = (Function *)malloc(sizeof(Function));
    scanf("%d", &result->degree);

    result->data = (double *)malloc(sizeof(double) * (result->degree + 1));
    for(int i = result->degree; i >= 0; i --)
        scanf("%lf", &result->data[i]);

    return result;
}

Function *derivative(Function *func){
    Function *result = (Function *)malloc(sizeof(Function));
    result->data = (double *)malloc(sizeof(double) * func->degree);
    result->degree = func->degree - 1;

    for(int i = 0; i < func->degree; i++)
        result->data[i] = func->data[i + 1] * (i + 1);
    return result; 
}

void freeFunc(Function *func){
    free(func->data);
    free(func);
    return ;
}

double getValue(Function *func, double x){
    double value = 0;
    double power = 1;
    for(int i = 0; i <= func->degree; i++){
        value += power * func->data[i];
        power *= x;
    }

    return value;
}

int main(){
    Function *func = readFunc();
    Function *derv = derivative(func);

    int iteration;
    scanf("%d", &iteration);

    double last;
    scanf("%lf", &last);

    double funcValueLast = getValue(func, last);
    for(int i = 0; i < iteration; i++){
        printf("%.4f %.4f\n", last, funcValueLast);
        
        double now = last;
        now -= funcValueLast / getValue(derv, last);

        last = now;
        funcValueLast = getValue(func, last);
    }  

    freeFunc(func);
    freeFunc(derv);

}