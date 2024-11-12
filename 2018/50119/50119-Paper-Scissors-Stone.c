#include <stdio.h>

//0 x win; 1 y win; -1 tie
int combat(int x, int y){
    x %= 3;
    y %= 3;
    if((x + 1) % 3 == y % 3)
        return 1;
    else if((y + 1) % 3 == x % 3)
        return 0;
    else
        return -1;
}

int main(){
    int x, a, b, c, y, d, e, f;
    scanf("%d %d %d %d", &x, &a, &b, &c);
    scanf("%d %d %d %d", &y, &d, &e, &f);
    int target_round;
    scanf("%d", &target_round);

    int round_now = 0;
    int pair_now = 0;

    while(round_now < target_round){
        int result = combat(x, y);
        pair_now++;

        if(result != -1){
            printf("%d %d\n", result, pair_now);

            pair_now = 0;
            round_now++;
        }

        x = (x * a + b) % c;
        y = (y * d + e) % f;

    }
    


}