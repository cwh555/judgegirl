#include <stdio.h>
#include <stdlib.h>

typedef struct position{
    int x, y;
}Position;

int radius(Position a){
    return a.x * a.x + a.y * a.y;
}

int compare(const void *a, const void *b){
    Position *data1 = (Position *)a;
    Position *data2 = (Position *)b;

    int dist1 = radius(*data1);
    int dist2 = radius(*data2);

    if(dist1 > dist2)
        return -1;
    else
        return 1;
}

int main(){
    int num;
    scanf("%d", &num);

    Position data[num];
    for(int i = 0; i < num; i++)
        scanf("%d %d", &data[i].x, &data[i].y);
    
    qsort(data, num, sizeof(Position), compare);


    int max_radius = 0, max_num = 0;
    int before_radius = 0, num_now = 0;
    for(int i = 0; i < num; i++){
        int radius_now = radius(data[i]);
        if(before_radius != radius_now){

            if(num_now > max_num){
                max_radius = before_radius;
                max_num = num_now;
            }

            num_now = 0;
        }

        num_now++;
        before_radius = radius_now;
    }

    if(num_now > max_num){
        max_radius = before_radius;
        max_num = num_now;
    }

    printf("%d\n", max_radius);

}