#define MAXPEOPLE 100
 
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
 
bool choose(bool friend[MAXPEOPLE][MAXPEOPLE], int require_num
            , int select[MAXPEOPLE], int select_num,
            int wait[MAXPEOPLE], int wait_num);
 
int main(){
    int people_num, choose_num;
    while(scanf("%d%d", &people_num, &choose_num) != EOF){
        bool friend[MAXPEOPLE][MAXPEOPLE];
        for(int i = 0; i < people_num; i++){
            for(int j = 0; j < people_num; j++){
                int temp;
                scanf("%d", &temp);
                friend[i][j] = (temp == 1);
            }
        }
 
        int select[MAXPEOPLE] = {0};
        int wait[MAXPEOPLE];
        for(int i = 0; i < people_num; i++)
            wait[i] = i;
 
        bool find = choose(friend, choose_num, select, 0,
                        wait, people_num);
 
        if(!find)
            printf("no solution\n");
 
 
    }
 
 
}
 
 
bool choose(bool friend[MAXPEOPLE][MAXPEOPLE], int require_num
            , int select[MAXPEOPLE], int select_num,
            int wait[MAXPEOPLE], int wait_num){
    if(require_num == 0){
        for(int i = 0; i < select_num; i++)
            printf("%d%c", select[i], " \n"[i == select_num - 1]);
        return true;
    }
    else if(wait_num < require_num)
        return false;
 
    int choose_index = wait[0];
    int index = 0;
    int next[MAXPEOPLE];
    select[select_num] = wait[0];
    for(int i = 1; i < wait_num; i++){
        if(!friend[choose_index][wait[i]])
            next[index++] = wait[i];
    }
 
    return choose(friend, require_num - 1,
                select, select_num + 1, next, index) ||
            choose(friend, require_num, 
                select, select_num, wait + 1, wait_num - 1);
 
}