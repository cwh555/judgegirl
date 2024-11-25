#include <stdio.h>
#include <math.h>

typedef struct line{
    double a, b, c;
}Line;

typedef struct position{
    double x, y;
}Position;

Position intersection(Line *data1, Line *data2){
    Position ans;
    double delta = data1->a * data2->b - data1->b * data2->a;
    ans.x = (data1->b * data2->c - data1->c * data2->b) / delta;
    ans.y = (data1->c * data2->a - data1->a * data2->c) / delta;

    return ans;
}

double distance(Position* a, Position *b){
    return sqrt((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
}

int main(){
    int num;
    scanf("%d", &num);
    Line first, before, now;
    scanf("%lf %lf %lf", &first.a, &first.b, &first.c);
    before = first;

    Position last, this, first_point;
    double perimeter = 0;
    for(int i = 1; i < num; i++){
        scanf("%lf %lf %lf", &now.a, &now.b, &now.c);

        this = intersection(&before, &now);
        if(i != 1)
            perimeter += distance(&last, &this);
        else
            first_point = this;
        
        before = now;
        last = this;
    }

    this = intersection(&first, &now);
    perimeter += distance(&first_point, &this);
    perimeter += distance(&this, &last);

    printf("%.3lf", perimeter);

    return 0;
}