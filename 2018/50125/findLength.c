#include "findLength.h"

int findLength (int array[][256], int N, int r, int c, int dr, int dc){
    int max_count = 0;
    while(r >= 0 && r < N && c >= 0 && c < N){
        //jump through 0
        while(r >= 0 && r < N && c >= 0 && c < N && array[r][c] == 0){
            r += dr;
            c += dc;
        }

        //count 1
        int count = 0;
        while(r >= 0 && r < N && c >= 0 && c < N && array[r][c] == 1){
            count++;
            r += dr;
            c += dc;
        }

        if(count > max_count)
            max_count = count;
    }

    return max_count;
}