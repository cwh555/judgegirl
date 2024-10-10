#define MAXPEOPLE 100
 
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
 
bool choose(bool friend[MAXPEOPLE][MAXPEOPLE], int people_num, int require_num
            , int select[MAXPEOPLE], int select_num, int index_now, bool unable[MAXPEOPLE]);
 
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
        bool unable[MAXPEOPLE] = {0};
 
        bool find = choose(friend, people_num, choose_num, select, 
                            0, 0, unable);
 
        if(!find)
            printf("no solution\n");
 
 
    }
 
 
}
 
 
bool choose(bool friend[MAXPEOPLE][MAXPEOPLE], int people_num, int require_num
            , int select[MAXPEOPLE], int select_num, int index_now,
            bool unable[MAXPEOPLE]){
    if(require_num == 0){
        for(int i = 0; i < select_num; i++)
            printf("%d%c", select[i], " \n"[i == select_num - 1]);
        return true;
    }
    else if(people_num - index_now < require_num)
        return false;
 
    //選此或不選
    if(!unable[index_now]){
        bool copy[MAXPEOPLE] = {0};
        for(int i = index_now; i < people_num; i++)
            if(unable[i] || friend[index_now][i])
                copy[i] = true;
        select[select_num] = index_now;
        copy[index_now] = true;
 
        return choose(friend, people_num, require_num - 1,
                     select, select_num + 1, index_now + 1, copy) ||
                choose(friend, people_num, require_num, 
                    select, select_num, index_now + 1, unable);
 
 
    }
    else
        return  choose(friend, people_num, require_num,
                     select, select_num, index_now + 1, unable);
 
}