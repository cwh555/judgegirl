#define MAXNAME 40
#define MAX(a, b) ((a) > (b) ? (a) : (b));

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define debug

#ifdef debug
#define DEBUG(format, var) printf(format, var)
#else
#define DEBUG(message)
#endif

int main(){
    char finname1[MAXNAME], finname2[MAXNAME], foutname[MAXNAME];
    scanf("%s %s %s", finname1, finname2, foutname);

    FILE *fin1 = fopen(finname1, "rb");
    FILE *fin2 = fopen(finname2, "rb");
    FILE *fout = fopen(foutname, "wb");

    if(fin1 == NULL || fin2 == NULL || fout == NULL){
        fprintf(stderr, "cannot open the file\n");
        exit(-1);
    }

    DEBUG("%s", "open the file\n");
    
    //輸入都移動到文件尾部
    fseek(fin1, 0, SEEK_END);
    fseek(fin2, 0, SEEK_END);

    //先將fout全部寫上0
    long long len = MAX(ftell(fin1), ftell(fin2));
    char buffer[8];
    memset(buffer, 0, sizeof(buffer));
    for(int i = 0; i < len; i++)
        fwrite(buffer, sizeof(buffer), 1, fout);


    DEBUG("%s", "begin add\n");
    //加法
    int carry = 0;
    int sum = 0;
    //fread失敗時變數值不會變
    bool end1 = false, end2 = false;
    while(!end1 || !end2){
        int data1 = 0, data2 = 0;

        if(!end1){
            if(fseek(fin1, -1, SEEK_CUR) == -1)
                end1 = true;
            else{
                fread(&data1, sizeof(int), 1, fin1);
                fseek(fin1, -1, SEEK_CUR);
            }
        }

        if(!end2){
            if(fseek(fin2, -1, SEEK_CUR) == -1)
                end2 = true;
            else{
                fread(&data2, sizeof(int), 1, fin2);
                fseek(fin2, -1, SEEK_CUR);
            }
        }

        //加法
        sum = data1 + data2 + carry;
        carry = sum / 256;
        sum %= 256;

        //輸出
        fseek(fout, -1, SEEK_CUR);
        fwrite(&sum, sizeof(int), 1, fout);
        fseek(fout, -1, SEEK_CUR);

    }

    DEBUG("%s", "end add\n");

    fclose(fin1);
    fclose(fin2);
    fclose(fout);
}
