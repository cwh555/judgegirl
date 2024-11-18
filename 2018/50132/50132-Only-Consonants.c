#define MAXLEN 50

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char input[MAXLEN];
    scanf("%s", input);

    int count = 0;
    char last = 'z';
    do{
        char *token = strtok(input, "aeiou");
        
        while(token != NULL){
            int len = strlen(token);
            for(int i = 0; i < len; i++){
                if(token[i] > last)
                    count++;
                last = token[i];
            }

            token = strtok(NULL, "aeiou");
        }

    }while(scanf("%s", input) != EOF);

    printf("%d\n", count);
}