#include <stdio.h>

int discount(int a, int b, int v, int w, int x, int y, int z, int payment){
    if(payment < a)
        return 0;
    else if(payment < b)
        return (payment % 2 == 0 ? w : v);
    else{
        int return_value[3] = {x, y, z};

        return return_value[payment % 3];
    }
}

int main(){
    int a, b, v, w, x, y, z;

    scanf("%d %d %d %d %d %d %d", &a, &b, &v, &w, &x, &y, &z);

    //p = a, p = a + 1, p = b, p = b + 1, p = b + 2
    int payment[6] = {1, a, a + 1, b, b + 1, b + 2};
    int d[6];
    d[0] = discount(a, b, v, w, x, y, z, 1);
    d[1] = discount(a, b, v, w, x, y, z, a);
    d[2] = discount(a, b, v, w, x, y, z, a + 1);
    d[3] = discount(a, b, v, w, x, y, z, b);
    d[4] = discount(a, b, v, w, x, y, z, b + 1);
    d[5] = discount(a, b, v, w, x, y, z, b + 2);

    int max_index = 0;
    for(int i = 1; i < 6; i++){
        if((d[i] * payment[max_index] > d[max_index] * payment[i])
            || ((d[i] * payment[max_index] == d[max_index] * payment[i]) && payment[i] < payment[max_index]))
            max_index = i;
    }
    
    printf("%d\n", payment[max_index]);

}