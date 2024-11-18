#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#include "loops.h"
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

void loops(int N, int *A, int *B[], int ans[4]){
    bool *visited = (bool *)calloc(N, sizeof(bool));
    ans[0] = 0;
    ans[1] = INT_MAX;

    ans[2] = 0;
    ans[3] = INT_MAX;

    for(int i = 0; i < N; i++){
        if(visited[i])
            continue;

        int loop_len = 0;
        int max = 0;
        int min = INT_MAX;

        int now = i;
        while(!visited[now]){
            visited[now] = true;
            loop_len++;

            if(max < *(A + now))
                max = *(A + now);
            if(min > *(A + now))
                min = *(A + now);

            now = B[now] - A;
        }

        if(loop_len > ans[0]){
            ans[0] = loop_len;
            ans[2] = max;
        }
        else if(loop_len == ans[0])
            ans[2] = MAX(ans[2], max);

        if(loop_len < ans[1]){
            ans[1] = loop_len;
            ans[3] = min;
        }
        else if(loop_len == ans[1])
            ans[3] = MIN(ans[3], min);
    }

    free(visited);
    return;
}
