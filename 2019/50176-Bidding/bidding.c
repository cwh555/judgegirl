#include "bidding.h"
#include <stdlib.h>
#include <stdio.h>

int compare(const void *a, const void *b){
    ItemMinPrice *data1 = (ItemMinPrice *)a;
    ItemMinPrice *data2 = (ItemMinPrice *)b;

    if(data1->itemID > data2->itemID)
        return 1;
    else
        return -1;
}

int findIndex(ItemMinPrice table[], int n, int target){
    int left = 0, right = n - 1;
    while(left <= right){
        int middle = (left + right) / 2;
        
        if(table[middle].itemID > target)
            right = middle - 1;
        else if(table[middle].itemID < target)
            left = middle + 1;
        else
            return middle;
    }

    fprintf(stderr, "cannot find %d\n", target);
    exit(-1);
}

int compare_sort(const void *a, const void *b){
    Bid *data1 = *(Bid **)a;
    Bid *data2 = *(Bid **)b;

    if(data1 == NULL)
        return 1;
    else if(data2 == NULL)
        return -1;

    if(data1->bidderID > data2->bidderID)
        return 1;
    else if(data1->bidderID < data2->bidderID)
        return -1;
    else{
        if(data1->itemID > data2->itemID)
            return 1;
        else
            return -1;
    }
}

void bidding(Bid bidSeq[], int m, ItemMinPrice minPriceSeq[], int n){
    //sort minPrice by item id
    qsort(minPriceSeq, n, sizeof(ItemMinPrice), compare);
    
    //record each item
    Bid **sold = (Bid **)calloc(n, sizeof(Bid*));

    for(int i = 0; i < m; i++){
        int index = findIndex(minPriceSeq, n, bidSeq[i].itemID);
        if(bidSeq[i].bidPrice < minPriceSeq[index].minPrice)
            continue;

        if(sold[index] == NULL || sold[index]->bidPrice < bidSeq[i].bidPrice){
            //update
            sold[index] = &bidSeq[i];
        }
    }

    qsort(sold, n, sizeof(Bid *), compare_sort);
    for(int i = 0; i < n; i++){
        if(sold[i] == NULL)
            continue;
        printf("Bidder %d gets item %d with %d dollars\n", sold[i]->bidderID,
                    sold[i]->itemID, sold[i]->bidPrice);
    }

    free(sold);
    return;
}