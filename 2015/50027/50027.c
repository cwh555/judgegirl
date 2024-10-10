#define MAXNUM 1100
 
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
 
typedef struct {
    int balance;
    char name[128];
    int gender;
} Account;
 
 
bool check_name(char *name);
int compare(const void *a, const void *b);
 
int main(){
    char filename[100];
    while(scanf("%s", filename) != EOF){
        FILE *fin = fopen(filename, "rb");
        if(fin == NULL){
            fprintf(stderr, "not able to open file\n");
            exit(-1);
        }
 
        Account data[MAXNUM];
        int data_num = 0;
        Account temp;
        while(fread(&temp.balance, sizeof(int), 1, fin) == 1){
            assert(fread(&temp.name, sizeof(char[128]), 1, fin) == 1);
            assert(fread(&temp.gender, sizeof(int), 1, fin) == 1);
 
            //錯誤資料不儲存
            if(temp.balance < 0 || !check_name(temp.name) 
                || (temp.gender != 0 && temp.gender != 1))
                continue;
            else{
                data[data_num++] = temp;
            }
        }
        fclose(fin);
 
        //sort data
        qsort(data, data_num, sizeof(Account), compare);
 
        //write out 
        scanf("%s", filename);
        FILE *fout = fopen(filename, "wb");
        if(fout == NULL){
            fprintf(stderr, "not able to open file\n");
            exit(-1);
        }
 
        fwrite(data, sizeof(Account), data_num, fout);
 
        fclose(fout);
    }
 
}
 
 
bool check_name(char *name){
    int len = strlen(name);
    bool check = true;
    for(int i = 0; i < len && check; i++){
        if(!isalpha(name[i]) && name[i] != ' ')
            check = false;
    }
 
    return check;
}
 
 
int compare(const void *a, const void *b){
    Account *data1 = (Account*)a;
    Account *data2 = (Account*)b;
 
    return strcmp(data1->name, data2->name);
}