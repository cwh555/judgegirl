#include <stdio.h>

int main(){
    int digit;

    int num = 0, zero = 0;
    int even, eleven;
    int diff = 0; 
    while(scanf("%d", &digit) != EOF){
        num++;
        if(digit == 0)
            zero++;

        diff += (num % 2 == 0 ? 1 : -1) * digit;
        even = (digit % 2 == 0);
        eleven = (diff % 11 == 0);
    }

    printf("%d\n%d\n%d\n%d\n", num, even, zero, eleven);


}