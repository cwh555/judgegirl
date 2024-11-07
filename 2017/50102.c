#define MAXNAME 40
#define MAX(a, b) ((a) > (b) ? (a) : (b));

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define debug

#ifdef debug
#define DEBUG(message) printf("%s", message)
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

    DEBUG("open the file\n");
    
    //輸入都移動到文件尾部
    fseek(fin1, 0, SEEK_END);
    fseek(fin2, 0, SEEK_END);

    //先將fout全部寫上0
    long long len = MAX(ftell(fin1), ftell(fin2));
    char buffer[8];
    memset(buffer, 0, sizeof(buffer));
    for(int i = 0; i < len; i++)
        fwrite(buffer, sizeof(buffer), 1, fout);


    DEBUG("begin add\n");
    //加法
    int carry = 0;
    int sum = 0;
    //fread失敗時變數值不會變
    while(ftell(fin1) != 0 || ftell(fin2) != 0){
        if(ftell(fin1) == 0 || ftell(fin2) == 0){
            fprintf(stderr, "end of file\n");
            exit(-1);
        }

        //移動到前一個字元才可以書寫
        fseek(fin1, -1, SEEK_CUR);
        fseek(fin2, -1, SEEK_CUR);
        fseek(fout, -1, SEEK_CUR);

        //讀取資料
        int data1 = 0, data2 = 0;
        fread(&data1, sizeof(int), 1, fin1);
        fread(&data2, sizeof(int), 1, fin2);

        //加法
        sum = data1 + data2 + carry;
        carry = sum / 256;
        sum %= 256;

        //輸出
        fwrite(&sum, sizeof(int), 1, fout);

        //因為讀取與輸出，需要再往前一個字元
        fseek(fin1, -1, SEEK_CUR);
        fseek(fin2, -1, SEEK_CUR);
        fseek(fout, -1, SEEK_CUR);
    }

    DEBUG("end add\n");

    fclose(fin1);
    fclose(fin2);
    fclose(fout);
}
