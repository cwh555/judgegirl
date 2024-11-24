#include <stdio.h>
#include <stdbool.h>

int main(){
    int longest = 0;
    int longest_left = 0;
    int longest_start = -1;


    int before_len = 0, now_len = 2;
    int before, now;
    scanf("%d", &before);
    scanf("%d", &now);
    bool now_increasing = (now > before);
    before = now;

    int count = 2;
    while(scanf("%d", &now) != EOF){
        //change dir
        bool change = (now > before && !now_increasing) \
                        || (now < before && now_increasing);

        if(change){
            if(before_len != 0 &&
                ((before_len + now_len > longest) ||\
                 (before_len + now_len == longest && before_len > longest_left))){

                longest = before_len + now_len;
                longest_start = count - longest + 1;
                longest_left = before_len;

            }


            before_len = now_len + (before_len != 0);
            now_len = 0;


            now_increasing = (now > before);
        }

        before = now;
        now_len++;
        count++;
    }

    if(before_len != 0 &&
        ((before_len + now_len > longest) ||\
            (before_len + now_len == longest && before_len > longest_left))){

        longest = before_len + now_len;
        longest_start = count - longest + 1;
        longest_left = before_len;

    }


    if(longest_start != -1)
        printf("%d %d\n", longest, longest_start);
    else
        printf("0\n");

}