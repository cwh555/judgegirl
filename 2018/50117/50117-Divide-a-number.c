#include <stdio.h>
#include <stdbool.h>

int main(){
    int k;
    scanf("%d", &k);
    
    int digit;
    int prev = 0;

    bool first = true;

    while(scanf("%d", &digit) != EOF){
        prev *= 10;
        int division = 0;
    
        prev += digit;
        division += prev / k;
        prev %= k;

        if(first && division == 0)
            continue;
        else{
            printf("%d\n", division);
            first = false;
        }
    }

    if(first)
        printf("0\n");
}