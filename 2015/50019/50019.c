#include "medicine.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


void init(Medicine *medicine){
    medicine->active_num = 0;
    medicine->inactive_num = 0;
    medicine->sort = true;
    return;
}

int add(Ingredient *data, int *data_num, int data_max, char *new_name, int weight){
    int index = 0;

    bool find = false;
    for(; index < *data_num && !find; index++)
        if(strcmp(data[index].name, new_name) == 0)
            find = true;
    index--;

    if(find)
        return (data[index].weight += weight);
    else{
        if(*data_num == data_max)
            return -1;
        else{
            strcpy(data[*data_num].name, new_name);
            data[(*data_num)++].weight = weight;
            return weight;
        }
    }

}


int addActive(Medicine *medicine, char *name, int weight){
    int ans =  add(medicine->active, &medicine->active_num, 2, name, weight);
    if(ans != -1)
        medicine->sort = false;
    return ans;
}


int addInactive(Medicine *medicine, char *name, int weight){
    int ans = add(medicine->inactive, &medicine->inactive_num, 5, name, weight);
    if(ans != -1)
        medicine->sort = false;
    return ans;

}

int compare(const void *a, const void *b){
    Ingredient *data1 = (Ingredient*)a;
    Ingredient *data2 = (Ingredient*)b;

    if(data1->weight > data2->weight)
        return -1;
    else if(data1->weight < data2->weight)
        return 1;
    else{
        return strcmp(data1->name, data2->name);
    }
}

void print(Medicine *medicine){
    if(!medicine->sort){
        qsort(medicine->active, medicine->active_num, sizeof(Ingredient), compare);
        qsort(medicine->inactive, medicine->inactive_num, sizeof(Ingredient), compare);
    }
    printf("----- Active Ingredient begin   -----\n");
    for(int i = 0; i < medicine->active_num; i++)
        printf("%d %s\n", medicine->active[i].weight, medicine->active[i].name);
    printf("----- end                       -----\n");

    printf("----- Inactive Ingredient begin -----\n");
    for(int i = 0; i < medicine->inactive_num; i++)
        printf("%d %s\n", medicine->inactive[i].weight, medicine->inactive[i].name);
    printf("----- end                       -----\n");

    medicine->sort = true;
    return;
    
}

int totalWeight(Medicine *medicine){
    int total = 0;
    for(int i = 0; i < medicine->active_num; i++)
        total += medicine->active[i].weight;
    for(int i = 0; i < medicine->inactive_num; i++)
        total += medicine->inactive[i].weight;

    return total;
}

char *maxIngredient(Medicine *medicine){
    if(!medicine->sort){
        qsort(medicine->active, medicine->active_num, sizeof(Ingredient), compare);
        qsort(medicine->inactive, medicine->inactive_num, sizeof(Ingredient), compare);
    }

    medicine->sort = true;

    if(medicine->active_num == 0 && medicine->inactive_num == 0)
        return NULL;
    else if(medicine->active_num == 0)
        return medicine->inactive[0].name;
    else if(medicine->inactive_num == 0)
        return medicine->active[0].name;

    //比較inactive, active較大的
    Ingredient first = medicine->active[0];
    Ingredient second = medicine->inactive[0];

    if(first.weight > second.weight)
        return medicine->active[0].name;
    else if(first.weight < second.weight)
        return medicine->inactive[0].name;
    else{
        if(strcmp(first.name, second.name) > 0)
            return medicine->inactive[0].name;
        else
            return medicine->active[0].name;
    }


}