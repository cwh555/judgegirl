#include <stdio.h>
#include <stdlib.h>

void find(int *num, char *ans, int ans_index, int len, char before, int dist){
    if(*num == 0)
        return;
    else if(ans_index == len){
        ans[ans_index] = '\0';
        printf("%s\n", ans);

        (*num)--;
        return;
    }

    for(int i = 0; i < 26; i++){
        int compare = ('a' + i - before + 26) % 26;
        if(compare == 0 || compare > dist)
            continue;

        ans[ans_index] = 'a' + i;
        find(num, ans, ans_index + 1, len, 'a' + i, dist);
    }

    return;
}

int main(){
    char before;
    int dist, len, num;
    scanf(" %c %d %d %d", &before, &dist, &len, &num);

    char *ans = (char *)malloc(sizeof(char) * (len + 1));
    ans[0] = before;

    find(&num, ans, 1, len, before, dist);


}