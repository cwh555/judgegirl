#include "map.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void init(Map *map){
    map->data_num = 0;

    return;
}

int map(Map *map, const int key, const char *value){
    //初始條件處理
    if(map->data_num == 0){
        map->data_by_key[0].key = key;
        strcpy(map->data_by_key[0].value, value);
        map->data_num++;
        return 1;
    }

    int position = -1;  //key小於插入值的最大數
    bool find = false;  //是否找到
    int left = 0, right = map->data_num - 1;
    //找到插入key位置
    while(left <= right && !find){
        int middle = (left + right) / 2;

        if(map->data_by_key[middle].key > key)
            right = middle - 1;
        else if(map->data_by_key[middle].key < key){
            left = middle + 1;
            position = middle;
        }
        else{
            position = middle;
            find = true;
        }
    }

    //插入key
    if(find)
        strcpy(map->data_by_key[position].value, value);
    else{
        //要插入的位置在position + 1
        memmove(map->data_by_key + position + 2,
                map->data_by_key + position + 1,
                sizeof(Element) * (map->data_num - position - 1));
        map->data_by_key[position + 1].key = key;
        strcpy(map->data_by_key[position + 1].value, value);
        map->data_num++;
    }
    
    return !find;

}

const char *getValue(Map *map, const int key){
    int left = 0, right = map->data_num - 1, result = -1;
    while(left <= right && result == -1){
        int middle = (left + right) / 2;

        if(map->data_by_key[middle].key > key)
            right = middle - 1;
        else if(map->data_by_key[middle].key < key)
            left = middle + 1;
        else
            result = middle;
    }

    if(result == -1)
        return NULL;
    else
        return map->data_by_key[result].value;

}

int get_index(Map *map, const int key){
    int left = 0, right = map->data_num - 1, result = -1;
    while(left <= right && result == -1){
        int middle = (left + right) / 2;

        if(map->data_by_key[middle].key > key)
            right = middle - 1;
        else if(map->data_by_key[middle].key < key)
            left = middle + 1;
        else
            result = middle;
    }

    return result;
}


void print(Map *map){
    printf("----- map begin -----\n");
    for(int i = 0; i < map->data_num; i++)
        printf("%d %s\n", map->data_by_key[i].key, map->data_by_key[i].value);
    printf("----- end       -----\n");

    return;
}

int numPairs(Map *map){
    return map->data_num;
}

int unmap(Map *map, int key){
    int index = get_index(map, key);
    if(index == -1)
        return 0;
    else{
        memmove(map->data_by_key + index, 
                map->data_by_key + index + 1, 
                sizeof(Element) * (map->data_num - index - 1));
            map->data_num--;
        return 1;
    }
}

int compare(const void *a, const void *b){
    if(*(int*)a > *(int*)b)
        return 1;
    else
        return -1;
}

int reverseMap(Map *map, const char *value, int keys[]){
    int num = 0;
    for(int i = 0; i < map->data_num; i++)
        if(strcmp(value, map->data_by_key[i].value) == 0)
            keys[num++] = map->data_by_key[i].key;
    
    qsort(keys, num, sizeof(int), compare);

    return num;
}