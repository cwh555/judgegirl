#define MAXNAME 25

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

//a <= b return 1; else return 0
int compare(char *a, char *b, int len){
    if(len == 0)
        return 1;

    if(a[0] < b[0])
        return 1;
    else if(a[0] > b[0])
        return 0;
    else
        return compare(a + 1, b + 1, len - 1);

}

int main(){
    int num;
    scanf("%d", &num);

    //open all file
    FILE *fin[num];
    for(int i = 0; i < num; i++){
        char fname[MAXNAME];
        scanf("%s", fname);

        fin[i] = fopen(fname, "r");
        if(fin[i] == NULL){
            fprintf(stderr, "fail to open input file\n");
            exit(-1);
        }
    }

    char fname[MAXNAME];
    scanf("%s", fname);
    FILE *fout = fopen(fname, "w");
    if(fout == NULL){
        fprintf(stderr, "fail to open outfile\n");
        exit(-1);
    }

    //always store one string from each file
    char data[num][4];
    bool end[num];
    for(int i = 0; i < num; i++)
        end[i] = false;

    int rest_file = num;
    //init data
    for(int i = 0; i < num; i++){
        if(fread(&data[i], sizeof(char[3]), 1, fin[i]) != 1){
            end[i] = true;
            rest_file--;
        }
    }

    while(rest_file > 0){
        //find the min
        int min_index = -1;
        char min_value[4] = "zzz";

        for(int i = 0; i < num; i++){
            if(end[i])
                continue;

            if(compare(data[i], min_value, 3)){
                min_index = i;
                min_value[0] = data[i][0];
                min_value[1] = data[i][1];
                min_value[2] = data[i][2];
            }
        }

        if(min_index == -1){
            fprintf(stderr, "find error\n");
            exit(-1);
        }

        //write
        assert(fwrite(&data[min_index], sizeof(char[3]), 1, fout) == 1);
        if(fread(&data[min_index], sizeof(char[3]), 1, fin[min_index]) != 1){
            rest_file--;
            end[min_index] = true;
        }

    }

    for(int i = 0; i < num; i++)
        fclose(fin[i]);
    fclose(fout);

}