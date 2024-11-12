#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> 

typedef struct position{
    int x, y;
}Position;

int edgeLen(Position a, Position b){
    return abs(a.x - b.x) + abs(a.y - b.y);
}

bool conflict(Position vert1, Position vert2, Position hori1, Position hori2){
    if((hori1.y - vert1.y) * (hori1.y - vert2.y) < 0 && (vert1.x - hori1.x) * (vert1.x - hori2.x) < 0)
        return true;
    return false;
}

int cross(Position a, Position b){
    return (a.x * b.y) - (a.y * b.x);
}

int main(){
    Position a, b, c, d;
    scanf("%d %d %d %d %d %d %d %d", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y, &d.x, &d.y);
    //平移
    b.x -= a.x;
    b.y -= a.y;
    c.x -= a.x;
    c.y -= a.y;
    d.x -= a.x;
    d.y -= a.y;
    a.x = a.y = 0;

    //翻轉
    if(c.x < 0){
        b.x = -b.x;
        c.x = -c.x;
        d.x = -d.x;
    }
    if(c.y < 0){
        b.y = -b.y;
        c.y = -c.y;
        d.y = -d.y;
    }

    int perimeter = edgeLen(a, b) + edgeLen(b, c) + edgeLen(c, d) + edgeLen(d, a);

    int area = 0;
    Position ab = {.x = b.x, .y = a.y}, bc = {.x = c.x, .y = b.y};
    Position cd = {.x = d.x, .y = c.y}, da = {.x = a.x, .y = d.y};

    bool vert = conflict(bc, c, a, ab) && conflict(cd, d, a, ab) 
                && conflict(ab, b, c, cd) && conflict(ab, b, d, da)
                && conflict(cd, d, b, bc) && conflict(da, a, b, bc)
                && conflict(bc, c, d, da) && conflict(da, a, c, cd);

    if(vert){
        ab.x = a.x, ab.y = b.y;
        bc.x = b.x, bc.y = c.y;
        cd.x = c.x, cd.y = d.y;
        da.x = d.x, da.y = a.y;
    }

    area = abs(cross(a, ab) + cross(ab, b) + cross(b, bc) + cross(bc, c) +\
            cross(c, cd) + cross(cd, d) + cross(d, da) + cross(da, a)) / 2;
    
    printf("%d\n%d\n", perimeter, area);
}