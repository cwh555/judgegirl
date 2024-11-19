#define MAXLEN 10005
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
        int len;

        //print i
        for(int count = 0; count < i; count++){
            len = strlen(slice[count]) + (vowel[count] != '\0' ? 1 : 0);
            for(int t = 0; t < len; t++)
                printf("+");
        }
        printf("%s%c", slice[i], vowel[i]);
        for(int count = i + 1; count < slice_num; count++){
            len = strlen(slice[count]) + (vowel[count] != '\0' ? 1 : 0);
            for(int t = 0; t < len; t++)
                printf("+");
        }
        printf("\n");


        //print j
        for(int count = 0; count < j; count++){
            len = strlen(slice[count]) + (vowel[count] != '\0' ? 1 : 0);
            for(int t = 0; t < len; t++)
                printf("+");
        }
        printf("%s%c", slice[j], vowel[j]);
        for(int count = j + 1; count < slice_num; count++){
            len = strlen(slice[count]) + (vowel[count] != '\0' ? 1 : 0);
            for(int t = 0; t < len; t++)
                printf("+");
        }
        printf("\n");


        //print rest
        int min = (i < j ? i : j);
        int max = (i > j ? i : j);

        for(int count = 0; count < min; count++)
            printf("%s%c", slice[count], vowel[count]);
        len = strlen(slice[min]) + (vowel[min] != '\0' ? 1 : 0);
        for(int count = 0; count < len; count++)
            printf("+");
        for(int count = min + 1; count < max; count++)
            printf("%s%c", slice[count], vowel[count]);
        len = strlen(slice[max]) + (vowel[max] != '\0' ? 1 : 0);
        for(int count = 0; count < len; count++)
            printf("+");
        for(int count = max + 1; count < slice_num; count++)
            printf("%s%c", slice[count], vowel[count]);

        printf("\n");

    }


}