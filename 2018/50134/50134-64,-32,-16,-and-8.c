#include <stdio.h>
#include <stdlib.h>

void encode(void){
    char form[10];
    if(scanf("%s", form) == EOF)
        exit(EXIT_SUCCESS);

    unsigned int a;
    unsigned short b;
    unsigned char c[2];
    char str[10];
    scanf("%u %hu %s", &a, &b, str);
    c[0] = str[0];
    c[1] = str[1];

    unsigned long long result = 0;
    int left_index = 64;
    int c_index = 0;


    for(int i = 0; i < 4; i++){
        switch(form[i]){
            case 'C':
                left_index -= 8;
                result |= ((unsigned long long)c[c_index++] << left_index);
                break;
            case 'S':
                left_index -= 16;
                result |= ((unsigned long long)b << left_index);
                break;
            case 'L':
                left_index -= 32;
                result |= ((unsigned long long)a << left_index);
                break;
        }
    }

    printf("%llu\n", result);
}

void decode(void){
    char form[10];
    if(scanf("%s", form) == EOF)
        exit(EXIT_SUCCESS);

    unsigned long long code;
    scanf("%llu", &code);

    unsigned int a; 
    unsigned short b;
    unsigned char c[2];
    int c_index = 1;

    for(int i = 3; i >= 0; i--){
        switch(form[i]){
            case 'C':
                c[c_index--] = code & ((1ULL << 8) - 1);
                code >>= 8;
                break;
            case 'S':
                b = code & ((1ULL << 16) - 1);
                code >>= 16;
                break;
            case 'L':
                a = code & ((1ULL << 32) - 1);
                code >>= 32;
                break;
        }
    }

    printf("%u %hu %c%c\n", a, b, c[0], c[1]);
    return;
}

int main(){
    int type;
    scanf("%d", &type);

    if(type == 0)
        while(1)
            encode();
    else
        while(1)
            decode();
}