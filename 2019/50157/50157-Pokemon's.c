#include <stdio.h>


int main(){
    int k;
    scanf("%d", &k);

    int cp;
    int max = -1;
    int second_max = -1;
    int count[3] = {0};
    int sum = 0;
    while(scanf("%d", &cp) != EOF){
        count[cp % 3]++;

        if(cp >= max){
            second_max = max;
            max = cp;
        }
        else if(cp >= second_max)
            second_max = cp;

        //this team finish
        if(count[0] >= k && count[1] >= k && count[2] >= k){
            count[0] = 0;
            count[1] = 0;
            count[2] = 0;

            sum += second_max;
            max = -1, second_max = -1;
        }
    }

    if(max != -1)
        sum += (second_max != -1 ? second_max : cp);

    printf("%d\n", sum);

}