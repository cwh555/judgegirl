#define MAXPEOPLE 8
#define TESTTIME 1000000
#define M_PI 3.14159265358979323846
 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
 
typedef struct position{
    int x;
    int y; 
    int z;
}Position;
 
double distance(double x1, double y1, double z1, double x2, double y2, double z2){
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2);
}
 
// generate uniformly distributed random numbers in [0 ... 1]
double frandom() {
    return rand() * 1.f / RAND_MAX;
}
 
int near(Position data[MAXPEOPLE], int people_num, double x, double y, double z){
    int min_index = 0;
    double min_dist = distance(data[0].x, data[0].y, data[0].z, x, y, z);
 
    for(int i = 1; i < people_num; i++){
        double dist = distance(data[i].x, data[i].y, data[i].z, x, y, z);
        if(dist < min_dist){
            min_index = i;
            min_dist = dist;
        }
    }
 
    return min_index;
}
 
int main(){
 
    int radius, people_num;
    int case_index = 1;
    while(scanf("%d %d", &radius, &people_num) == 2){
 
        Position people[MAXPEOPLE];
        for(int i = 0; i < people_num; i++)
            scanf("%d %d %d", &people[i].x, &people[i].y, &people[i].z);
 
        int possibility[MAXPEOPLE] = {0};
        for(int i = 0; i < TESTTIME; i++){
            double p = radius * cbrt(frandom());
            double theta = 2 * M_PI * frandom();
            double phi = acos(-2 * frandom() + 1);
 
            int index = near(people, people_num, p * sin(phi) * cos(theta),
                        p * sin(phi) * sin(theta), p * cos(phi));
            possibility[index]++;
        }
 
        printf("Case #%d:\n", case_index);
        for(int i = 0; i < people_num; i++)
            printf("%d\n", (int)round((double)possibility[i] / TESTTIME * 100));
        case_index++;
    }
 
    return 0;
}