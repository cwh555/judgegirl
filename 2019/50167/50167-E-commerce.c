
#include "payment.h"

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define EQUAL(x, y) (fabs(x - y) < 0.0005)

double findPrice(int myItemID, int itemID[], double price[]){
    int index = 0;
    while(itemID[index] != 0){
        if(itemID[index] == myItemID)
            return price[index];
        index++;
    }

    return -1.0;
}

bool checkOnSale(int itemID, int onSaleItemID[]){
    int index = 0;
    while(onSaleItemID[index] != 0){
        if(onSaleItemID[index] == itemID)
            return true;
        index++;
    }

    return false;
}

double payment(int itemID[], double price[], int orderItemID[],
               int orderQuantity[], int onSaleItemID[]){
    int index = 0;
    double pay = 0;
    while(orderItemID[index] != 0){
        double itemPrice = findPrice(orderItemID[index], itemID, price);
        if(!EQUAL(itemPrice, -1.0)){
            bool onSale = checkOnSale(orderItemID[index], onSaleItemID);

            pay += itemPrice * orderQuantity[index] * (onSale ? 0.8 : 1);
        }
        index++;
    }

    if(pay < 490.0)
        pay += 80;
    return pay;
}