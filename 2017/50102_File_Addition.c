#define MAXNAME 40
#define MAX(a, b) ((a) > (b) ? (a) : (b));

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#ifdef debug
#define DEBUG(format, var) printf(format, var)
#else
#define DEBUG(format, var)
#endif

int main(){
    char finname1[MAXNAME], finname2[MAXNAME], foutname[MAXNAME];
    scanf("%s %s %s", finname1, finname2, foutname);

    FILE *fin1 = fopen(finname1, "rb");
    FILE *fin2 = fopen(finname2, "rb");
    FILE *fout = fopen(foutname, "wb");

    if(fin1 == NULL){
        fprintf(stderr, "cannot open the file1\n");
        exit(-1);
    }

    if(fin2 == NULL){
        fprintf(stderr, "cannot open the file2\n");
        exit(-1);
    }

    if(fout == NULL){
        fprintf(stderr, "cannot open the fileout\n");
        exit(-1);
    }

    DEBUG("%s", "open the file\n");
    
    //輸入都移動到文件尾部
    fseek(fin1, 0, SEEK_END);
    fseek(fin2, 0, SEEK_END);

    long long len1 = ftell(fin1);
    long long len2 = ftell(fin2);

    //先將fout全部寫上0
    long long len = MAX(len1, len2);
    unsigned char buffer = 0;
    for(int i = 0; i < len; i++)
        fwrite(&buffer, sizeof(buffer), 1, fout);


    DEBUG("%s", "begin add\n");

    //加法
    int carry = 0;
    int sum = 0;

    long long read_size1 = 0, read_size2 = 0;
    while(read_size1 < len1 || read_size2 < len2){
        unsigned char data1 = 0, data2 = 0;
        //read the data
        if(read_size1 < len1){
            assert(fseek(fin1, -1, SEEK_CUR) == 0);
            assert(fread(&data1, sizeof(data1), 1, fin1) == 1);
            read_size1 ++;
            assert(fseek(fin1, -1, SEEK_CUR) == 0);
        }

        if(read_size2 < len2){
            assert(fseek(fin2, -1, SEEK_CUR) == 0);
            assert(fread(&data2, sizeof(data2), 1, fin2) == 1);
            read_size2++;
            assert(fseek(fin2, -1, SEEK_CUR) == 0);
        }

        sum = carry + data1 + data2;
        carry = sum / 256;
        sum %= 256;

        unsigned char write = sum;
        //write
        assert(fseek(fout, -1, SEEK_CUR) == 0);
        assert(fwrite(&write, sizeof(write), 1, fout) == 1); 
        assert(fseek(fout, -1, SEEK_CUR) == 0);
    }
    DEBUG("%s", "end add\n");

    fclose(fin1);
    fclose(fin2);
    fclose(fout);
}
