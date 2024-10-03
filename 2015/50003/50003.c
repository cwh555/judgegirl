#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define debug

typedef struct line{
    int x_start, y_start;
    int x_end, y_end;
}Line;

typedef struct vector{
    int data_num;
    int size;
    Line *data;
}Vector;

void initiate(Vector*);
void push(Vector*, int x_s, int y_s, int x_e, int y_e);
void swap(int *x, int *y);

int main(){
    
    //讀入資料 按照垂直 水平 對角線
    int X, Y, L;
    scanf("%d%d%d", &L, &X, &Y);
    
    Vector *vertical = (Vector*)malloc(sizeof(Vector));
    Vector *horizon = (Vector*)malloc(sizeof(Vector));
    Vector *diagonal = (Vector*)malloc(sizeof(Vector));
    initiate(vertical);
    initiate(horizon);
    initiate(diagonal);

    bool check = true;
    bool end = false;

    for(int i = 0; i < L; i++){
        int point_num;
        scanf("%d", &point_num);

        int x_now, x_before, y_now, y_before;
        scanf("%d%d", &x_before, &y_before);
        for(int j = 1; j < point_num; j++){
            scanf("%d%d", &x_now, &y_now);
            
            if(!end){
                //越界檢查
                if(x_now < 0 || x_now >= X || y_now < 0 || y_now >= Y)
                    check = false;
                //分辨類別
                else if(x_now == x_before)
                    //鉛直
                    push(vertical, x_before, y_before, x_now, y_now);
                else if(y_now == y_before)
                    //水平
                    push(horizon, x_before, x_now, y_before, y_now);
                else if(abs(x_before - x_now) == abs(y_before - y_now))
                    //對角
                    push(diagonal, x_before, x_now, y_before, y_now);
                else
                    check = false;

                if(!check){
                    printf("ERROR %d %d\n", i + 1, j + 1);
                    end = true;
                }
                x_before = x_now;
                y_before = y_now;
            
            }
            
        }


    }

    #ifdef debug
    printf("check input data\n");
    printf("vertical\n");
    for(int i = 0; i < vertical->data_num; i++)
        printf("%d %d to %d %d\n", vertical->data[i].x_start, vertical->data[i].x_end,
                    vertical->data[i].y_start, vertical->data[i].y_end);
    printf("horizon\n");
    for(int i = 0; i < horizon->data_num; i++)
        printf("%d %d to %d %d\n", horizon->data[i].x_start, horizon->data[i].x_end,
                    horizon->data[i].y_start, horizon->data[i].y_end);
    printf("diagonal\n");
    for(int i = 0; i < diagonal->data_num; i++)
        printf("%d %d to %d %d\n", diagonal->data[i].x_start, diagonal->data[i].x_end,
                    diagonal->data[i].y_start, diagonal->data[i].y_end);
    printf("check end\n");
    #endif



}

void initiate(Vector *vector){
    vector->size = 10;
    vector->data_num = 0;
    vector->data = (Line*)malloc(sizeof(Line) * vector->size);

    return;
}

void push(Vector *vector, int x_s, int y_s, int x_e, int y_e){
    //將start調整成x_s較小 相同則y_s較小
    if(x_s > x_e){
        swap(&x_s, &x_e);
        swap(&y_s, &y_e);
    }
    else if(x_s == x_e && y_s > y_e){
        swap(&x_s, &x_e);
        swap(&y_s, &y_e);
    }

    if(vector->size == vector->data_num){
        vector->size += 10;
        vector->data = (Line*)realloc(vector->data, sizeof(Line) * vector->size);
    }

    vector->data[vector->data_num].x_start = x_s;
    vector->data[vector->data_num].x_end = x_e;
    vector->data[vector->data_num].y_start = y_s;
    vector->data[vector->data_num].y_end = y_e;

    vector->data_num++;
    return;
}

void swap(int *x, int *y){
    int temp = *x;
    *x = *y; 
    *y = temp;
    return;
}
