#define MAXLEN 100005
#define MAXSIZE 12505

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool encode(void){
    char input[MAXLEN];
    if(scanf("%s", input) == EOF)
        return false;

    int len = strlen(input);
    unsigned long long output = 0;
    for(int i = 0; i <= len; i++){
        unsigned char data = input[i];

        if(i != 0 && i % 8 == 0){
            printf("%llu\n", output);
            output = 0;
        }

        output |= (unsigned long long)data << ((7 - i % 8) * 8);
    }

    printf("%llu\n", output);

    return true;
}

bool decode(void){
    int size;
    if(scanf("%d", &size) == EOF)
        return false;

    bool end = false;
    for(int i = 0; i < size; i++){
        unsigned long long data;
        scanf("%llu", &data);

        for(int j = 7; j >= 0 && !end; j--){
            unsigned char getdata = (data >> j * 8) & ((1 << 8) - 1);

            if(getdata == 0)
                end = true;
            printf("%c", getdata);
        }

    }

    printf("\n");
    return true;
}

int main(){
    int type;
    scanf("%d", &type);

    if(type == 0)
        while(encode())
            ;
    else
        while(decode())
            ;

}