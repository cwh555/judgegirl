#include <stdio.h>

int main(){
    int a, b, c, d, e, f, g;
    scanf("%d %d %d %d %d %d %d", &a, &b, &c, &d, &e, &f, &g);

    int area_new = (a * b) - (e * f);
    int water = a * b * d;


    int height = d;
    if(area_new != 0){
        height = (water) / area_new;
        if(height > g)
            height = g + (water - area_new * g) / (a * b);
        if(height > c)
            height = c;
    }
    else{
        height = (height == 0 ? 0 : d + g);
        if(height > c)
            height = 0;
    }


    printf("%d\n", height);
}