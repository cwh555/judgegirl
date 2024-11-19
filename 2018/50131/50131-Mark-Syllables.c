#define MAXLEN 10005
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void print_slice(char *slice[], int slice_num, char vowel[]){
    if(slice_num <= 0)
        return;

    for(int i = 0; i < slice_num; i++)
        printf("%s%c", slice[i], vowel[i]);

    return;
}

void print_plus(char *slice[], int slice_num, char vowel[]){
    if(slice_num <= 0)
        return;

    for(int i = 0; i < slice_num; i++){
        int len = strlen(slice[i]);

        for(int j = 0; j < len; j++)
            printf("+");
        
        if(vowel[i] != '\0')
            printf("+");
        else
            printf("\0");
    }

    return;
}

int main(){
    char string[MAXLEN];
    int i, j;
    while(scanf("%s %d %d", string, &i, &j) != EOF){
        char *slice[MAXLEN];
        int slice_num = 0;
        char vowel[MAXLEN];
        
        slice[0] = string;

        char *find = strpbrk(slice[slice_num], "aeiou");
        while(find != NULL){
            vowel[slice_num++] = *find;

            *find = '\0';
            slice[slice_num] = find + 1;
            find = strpbrk(slice[slice_num], "aeiou");
        }
        
        //last
        if(*slice[slice_num] != '\0'){
            vowel[slice_num] = '\0';
            slice_num++;
        }

        //print i
        print_plus(slice, i, vowel);
        print_slice(slice + i, 1, vowel + i);
        print_plus(slice + i + 1, slice_num - i - 1, vowel + i + 1);
        printf("\n");

        //print j
        print_plus(slice, j, vowel);
        print_slice(slice + j, 1, vowel + j);
        print_plus(slice + j + 1, slice_num - j - 1, vowel + j + 1);
        printf("\n");

        //print rest
        int min = (i < j ? i : j);
        int max = (i > j ? i : j);

        print_slice(slice, min, vowel);
        print_plus(slice + min, 1, vowel + min);
        print_slice(slice + min + 1, max - min - 1, vowel + min + 1);
        print_plus(slice + max, 1, vowel + max);
        print_slice(slice + max + 1, slice_num - max - 1, vowel + max + 1);
        printf("\n");
    }


}