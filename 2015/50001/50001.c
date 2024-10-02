#include <stdlib.h>
#include <stdio.h>

enum {
    NORTH, EAST, SOUTH, WEST
}Direction;

int direction(int x, int y, int a, int b){
    return abs(a * x + b * y) % 4;
}

int gold(int x, int y, int c, int d, int e){
    return abs(c * x + d * y) % e;
}

//if not transport return gold else return 0
int transport(int *x, int *y, int p, int q, int r, int s, int c, int d, int e){
    if(*x == p && *y == q){
        *x = r;
        *y = s;
        return 0;
    }
    else if(*x == r && *y == s){
        *x = p;
        *y = q;
        return 0;
    }
    else
        return gold(*x, *y, c, d, e);
}

int main(){
    int a, b, c, d, e;
    int p, q, r, s;
    int x, y, F;

    scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
    scanf("%d %d %d %d", &p, &q, &r, &s);
    scanf("%d %d %d", &x, &y, &F);

    //首筆資料處理
    int sum = gold(x, y, c, d, e);
    
    while(F--){
        //移動到下一個位置
        int dir = direction(x, y, a, b);
        switch(dir){
            case NORTH:
                y += 1;
                break;
            case EAST:
                x += 1;
                break;
            case WEST:
                x -= 1;
                break;
            case SOUTH:
                y -= 1;
                break;
            default:
                fprintf(stderr, "dir error\n");
                exit(-1);
        }

        sum += transport(&x, &y, p, q, r, s, c, d, e);
    }


    printf("%d\n", sum);
    printf("%d %d\n", x, y);

}