#include <stdio.h>
#include "subset.h"
 
int finding(int numbers[], int n, int K, int S, int number_sum){
    if(S == 0){
        if(K == 0)
            return 1;
        else
            return 0;
    }
    else if(K <= 0 || K > number_sum)
        return 0;
    else if(n == 0)
        return 0;

    //選這個或不選
    int ans = finding(numbers + 1, n - 1, K - numbers[0], S - 1, number_sum - numbers[0]);
    if(!ans)
        ans = finding(numbers + 1, n - 1, K, S, number_sum - numbers[0]);
    
    return ans;
}

int subset(int numbers[], int n, int K, int S){
    //明顯錯誤判斷
    if(S > n)
        return 0;


    int sum = 0;
    for(int i = 0; i < n; i++)
        sum += numbers[i];

    int ans = finding(numbers, n, K, S, sum);

    return ans;
}
