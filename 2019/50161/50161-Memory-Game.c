#include <stdio.h>
#include <stdlib.h>

int main(){
    int num;
    scanf("%d", &num);

    int flip[105];
    for(int i = 0; i < 105; i++)
        flip[i] = -1;

    int *data = (int *)malloc(sizeof(int) * num);
    for(int i = 0; i < num; i++)
        scanf("%d", &data[i]);

    for(int i = 0; i < num; i++){
        int now = data[i];

        if(flip[now] != -1){
            printf("%d %d %d\n", i, flip[now], now);
            flip[now] = -1;
        }else{
            printf("%d\n", i);
            flip[now] = i;
        }
    }

    free(data);
}