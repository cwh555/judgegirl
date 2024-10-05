#define MAXSIZE 100000

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

void print(int record[26], bool rule[26][26], int before,
     int index_now, int total_num, char output[MAXSIZE]);

int main(){
    int record[26] = {0};
    char c;
    int len = 0 ;
    while(scanf("%c", &c) != EOF && isalpha(c)){
        record[c - 'a']++;
        len++;
    }

    int rule_num;
    scanf("%d", &rule_num);
    bool rule[26][26] = {{0}};  //[i]的下一項[j]是否在rule中
    for(int i = 0; i < rule_num; i++){
        char temp[2];
        scanf("%s", temp);
        rule[temp[0] - 'a'][temp[1] - 'a'] = true;
    }

    char output[MAXSIZE];
    print(record, rule, -1, 0, len, output);

    return 0;
}

void print(int record[26], bool rule[26][26], int before, 
            int index_now, int total_num, char output[MAXSIZE]){
    //遞迴終止條件：輸出
    if(index_now == total_num){
        for(int i = 0; i < total_num; i++)
            printf("%c", output[i]);
        printf("\n");
        return;
    }
    
    //找到可放置的
    for(int i = 0; i < 26; i++){
        if(record[i] > 0 && (before == -1 || !rule[before][i])){
            record[i] --;
            output[index_now] = (char)('a' + i);
            print(record, rule, i, index_now + 1, total_num, output);
            record[i]++;
        }
    }

    return;
}