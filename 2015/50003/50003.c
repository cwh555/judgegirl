#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


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

int compare_horizon(const void *a, const void *b);
int compare_vertical(const void *a, const void *b);
int compare_left_up(const void *a, const void *b);
int compare_right_up(const void *a, const void *b);

bool find_vert(Vector* vertical, int x, int y);
bool find_left_up(Vector* left_up, int x, int y);
bool find_right_up(Vector* right_up, int x, int y);


int main(){
    
    //讀入資料 按照垂直 水平 對角線
    int X, Y, L;
    scanf("%d%d%d", &L, &X, &Y);
    
    Vector *vertical = (Vector*)malloc(sizeof(Vector));
    Vector *horizon = (Vector*)malloc(sizeof(Vector));
    Vector *left_up_diagonal = (Vector*)malloc(sizeof(Vector));
    Vector *right_up_diagonal = (Vector*)malloc(sizeof(Vector));
    initiate(vertical);
    initiate(horizon);
    initiate(left_up_diagonal);
    initiate(right_up_diagonal);

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
                if(x_now < 0 || x_now >= Y || y_now < 0 || y_now >= X)
                    check = false;
                //分辨類別
                else if(x_now == x_before)
                    //鉛直
                    push(vertical, x_before, y_before, x_now, y_now);
                else if(y_now == y_before)
                    //水平
                    push(horizon, x_before, y_before, x_now, y_now);
                else if(x_before - x_now == y_before - y_now)
                    //對角
                    push(right_up_diagonal, x_before, y_before, x_now, y_now);
                else if(x_before - x_now == y_now - y_before)
                    push(left_up_diagonal, x_before, y_before, x_now, y_now);
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
        printf("%d %d to %d %d\n", vertical->data[i].x_start, vertical->data[i].y_start,
                    vertical->data[i].x_end, vertical->data[i].y_end);
    printf("horizon\n");
    for(int i = 0; i < horizon->data_num; i++)
        printf("%d %d to %d %d\n", horizon->data[i].x_start, horizon->data[i].y_start,
                    horizon->data[i].x_end, horizon->data[i].y_end);
    printf("right up diagonal\n");
    for(int i = 0; i < right_up_diagonal->data_num; i++)
        printf("%d %d to %d %d\n", right_up_diagonal->data[i].x_start, right_up_diagonal->data[i].y_start,
                    right_up_diagonal->data[i].x_end, right_up_diagonal->data[i].y_end);
    printf("left up diagonal\n");
    for(int i = 0; i < left_up_diagonal->data_num; i++)
        printf("%d %d to %d %d\n", left_up_diagonal->data[i].x_start, left_up_diagonal->data[i].y_start,
                    left_up_diagonal->data[i].x_end, left_up_diagonal->data[i].y_end);

    printf("check end\n");
    #endif

    if(!end){
        //horizon排序
        qsort(horizon->data, horizon->data_num, sizeof(Line), compare_horizon);
        //vertical排序
        qsort(vertical->data, vertical->data_num, sizeof(Line), compare_vertical);
        //左上對角線排序
        qsort(left_up_diagonal->data, left_up_diagonal->data_num, sizeof(Line), compare_left_up);
        //右上對角線排序
        qsort(right_up_diagonal->data, right_up_diagonal->data_num, sizeof(Line), compare_right_up);
        int hori_index = 0;
        for(int y_now = X - 1; y_now >= 0; y_now--){
            for(int x_now = 0; x_now < Y; x_now++){
                bool in_line = false;

                //檢查水平線
                //切換hori_index
                while(hori_index < horizon->data_num && horizon->data[hori_index].y_start > y_now)
                    hori_index++;
                while(hori_index < horizon->data_num && horizon->data[hori_index].y_start == y_now &&
                        horizon->data[hori_index].x_end < x_now)
                    hori_index++;

                if(hori_index < horizon->data_num &&
                    horizon->data[hori_index].y_start == y_now && horizon->data[hori_index].x_start <= x_now)
                    in_line = true;

                //檢查垂直線
                in_line |= find_vert(vertical, x_now, y_now);

                //檢查左上對角線
                in_line |= find_left_up(left_up_diagonal, x_now, y_now);

                //檢查右上對角線
                in_line |= find_right_up(right_up_diagonal, x_now, y_now);
                
                //檢查對角線
                
                printf("%d", (in_line ? 1 : 0));
            }
            printf("\n");
        }
    }
    
    free(left_up_diagonal);
    free(right_up_diagonal);
    free(vertical);
    free(horizon);
}

void initiate(Vector *vector){
    vector->size = 10;
    vector->data_num = 0;
    vector->data = (Line*)malloc(sizeof(Line) * vector->size);

    return;
}

void push(Vector *vector, int x_s, int y_s, int x_e, int y_e){
    //線的起點靠近左下
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


int compare_horizon(const void *a, const void *b){
    //從左上排到右下   y較大先 相同則x較小先
    Line *data1 = (Line*)a;
    Line *data2 = (Line*)b;

    if(data1->y_start < data2->y_start)
        return 1;
    else if(data1->y_start > data2->y_start)
        return -1;
    else{
        if(data1->x_start > data2->x_start)
            return 1;
        else
            return -1;
    }
}

int compare_vertical(const void *a, const void *b){
    Line *data1 = (Line*)a;
    Line *data2 = (Line*)b;

    //按照x座標排序 相同則按照end的y座標排序 再相同按照start y排序 均為由小到大
    if(data1->x_end > data2->x_end)
        return 1;
    else if(data1->x_end < data2->x_end)
        return -1;
    else{
        if(data1->y_end > data2->y_end)
            return 1;
        else if(data1->y_end < data2->y_end)
            return -1;
        else{
            if(data1->y_start > data2->y_start)
                return 1;
            else
                return -1;
        }
    }
}

bool find_vert(Vector* vertical, int x, int y){
    int left = 0, right = vertical->data_num - 1;
    int result = -1;
    while(left <= right){
        int middle = (left + right) / 2;

        //先找到x座標相同的
        if(vertical->data[middle].x_end > x)
            right = middle - 1;
        else if(vertical->data[middle].x_end < x)
            left = middle + 1;
        else{
            result = middle;
            right = middle - 1;
        }
    }
    //此時result 會是第一個x座標符合的

    //檢查
    bool in_line = false;
    if(result == -1)
        return false;

    while(!in_line && result < vertical->data_num && vertical->data[result].x_end == x){
        if(vertical->data[result].y_end >= y && vertical->data[result].y_start <= y)
            in_line = true;
        result++;
    }

    return in_line;
}

int compare_left_up(const void *a, const void *b){
    Line *data1 = (Line*)a;
    Line *data2 = (Line*)b;

    int sum1 = data1->x_end + data1->y_end;
    int sum2 = data2->x_end + data2->y_end;

    if(sum1 > sum2)
        return 1;
    else
        return -1;

}

bool find_left_up(Vector* left_up, int x, int y){
    //找到對角線的第一條
    int left = 0, right = left_up->data_num - 1;
    int result = -1;

    while(left <= right){
        int middle = (left + right) / 2;
        int sum_now = left_up->data[middle].x_end + left_up->data[middle].y_end;
        if(sum_now > x + y)
            right = middle - 1;
        else if(sum_now < x + y)
            left = middle + 1;
        else{
            result = middle;
            right = middle - 1;
        }

    }

    bool in_line = false;
    if(result == -1)
        return false;
    
    while(!in_line && result < left_up->data_num 
            && left_up->data[result].x_end + left_up->data[result].y_end == x + y){
        if(left_up->data[result].x_end >= x && left_up->data[result].x_start <= x)
            in_line = true;
        result++;
    }

    return in_line;
}

int compare_right_up(const void *a, const void *b){
    Line *data1 = (Line*)a;
    Line *data2 = (Line*)b;

    int diff1 = data1->x_end - data1->y_end;
    int diff2 = data2->x_end - data2->y_end;

    if(diff1 > diff2)
        return 1;
    else 
        return -1;
}

bool find_right_up(Vector* right_up, int x, int y){

    int left = 0, right = right_up->data_num - 1;
    int result = -1;

    while(left <= right){
        int middle = (left + right) / 2;
        int diff = right_up->data[middle].x_end - right_up->data[middle].y_end;

        if(diff < x - y)
            left = middle + 1;
        else if(diff > x - y)
            right = middle - 1;
        else{
            result = middle;
            right = middle - 1;
        }
    }

    bool in_line = false;
    if(result == -1)
        return false;

    while(!in_line && result < right_up->data_num
            && right_up->data[result].x_end - right_up->data[result].y_end == x - y){
        if(right_up->data[result].x_start <= x && right_up->data[result].x_end >= x)
            in_line = true;
        result ++;            
    }
    
    return in_line;
}