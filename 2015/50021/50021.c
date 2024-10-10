#include "polynomial.h"
#include <stdlib.h>
#include <stdio.h>
 
void init(Polynomial *poly, int coefficient[], int n){
    poly->degree = n - 1;
    poly->data_num = 0;
    for(int i = 0; i < n; i++){
        if(coefficient[i] != 0){
            poly->coef[poly->data_num].coef = coefficient[i];
            poly->coef[poly->data_num++].power = i;
        }
    }
 
    return;
}
 
Polynomial add(Polynomial *poly1, Polynomial *poly2){
    printf("inside\n");
    Polynomial c;
    c.data_num = 0;
    int index1 = 0;
    int index2 = 0;
    while(index1 < poly1->data_num && index2 < poly2->data_num){
        //比較係數冪次
        if(poly1->coef[index1].power > poly2->coef[index2].power)
            c.coef[c.data_num++] = poly2->coef[index2++];
        else if(poly1->coef[index1].power < poly2->coef[index2].power)
            c.coef[c.data_num++] = poly1->coef[index1++];
        else{
            int result = poly1->coef[index1].coef + poly2->coef[index2].coef;
            if(result != 0){
                c.coef[c.data_num].power = poly1->coef[index1].power;
                c.coef[c.data_num++].coef = result;
            }
 
            index1++;
            index2++;
        } 
    }
 
    //各自殘留
    while(index1 < poly1->data_num)
        c.coef[c.data_num++] = poly1->coef[index1++];
    while(index2 < poly2->data_num)
        c.coef[c.data_num++] = poly2->coef[index2++];
 
    c.degree = c.coef[c.data_num - 1].power;
 
    return c;
 
}
 
Polynomial multiply(Polynomial *poly1, Polynomial *poly2){
    int record[4100] = {0};
 
    for(int i = 0; i < poly1->data_num; i++){
        Var first = poly1->coef[i];
        for(int j = 0; j < poly2->data_num; j++){
            Var second = poly2->coef[j];
 
            record[first.power + second.power]+= first.coef * second.coef;
        }
    }
 
    Polynomial c;
    c.data_num = 0;
    for(int i = 0; i < 4100; i++){
        if(record[i] != 0){
            c.coef[c.data_num].power = i;
            c.coef[c.data_num++].coef = record[i];
        }
    }
 
    c.degree = c.coef[c.data_num - 1].power;
 
    return c;
}
 
void print(Polynomial *poly){
    for(int i = poly->data_num - 1; i >= 0; i--){
        if(poly->coef[i].power == 0)
            printf("%+d", poly->coef[i].coef);
        else if(poly->coef[i].power == 1)
            printf("%+dx", poly->coef[i].coef);
        else
            printf("%+dx^%d", poly->coef[i].coef, poly->coef[i].power);
    }
    printf("\n");
    return;
 
}