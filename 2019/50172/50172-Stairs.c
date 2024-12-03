#define MAXLEN 35

#include <stdio.h>
#include <string.h>

void printStar(int space){
    for(int i = 0; i < space; i++)
        printf("*");
    return;
}

int main(){
    char input[35];
    int space = 0;
    int input_num = 0;
    char lastChar = '\0';

    while(scanf("%s", input) != EOF){
        input_num ++;
        int len = strlen(input);

        if(input_num % 2 == 1){
            //horizon
            if(input_num != 1 && input[0] != lastChar){
                printf("\n");
                printStar(space);
                printf("%s\n", input);
            }
            else if(input_num != 1){
                printf("%s\n", &(input[0]) + 1);
            }
            else
                printf("%s\n", input);

            space += len - 1;
        }
        else{
            //vertical
            for(int i = 0; i < len; i++){
                if(i == 0 && lastChar == input[0])
                    continue;
                printStar(space);
                printf("%c", input[i]);

                if(i != len - 1)
                    printf("\n");
            }
        }

        lastChar = input[len - 1];
    }

}
