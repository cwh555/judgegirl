#define MAXNAME 20
 
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#ifdef debug
#define DEBUG(message) printf(message)
#else
#define DEBUG(message)
#endif

int main(){
    //read data
    char fin_name[MAXNAME], fout_name[MAXNAME];
    scanf("%s%s", fin_name, fout_name);

    FILE *fin = fopen(fin_name, "rb");
    FILE *fout = fopen(fout_name, "wb");
    if(fin == NULL || fout == NULL){
        fprintf(stderr, "fail to open the file\n");
        exit(-1);
    }

    int shift;
    scanf("%d", &shift);

    DEBUG("start operation\n");

    //minnor(read from the end)
    //shift N(begin with N bytes from the end)
    assert(fseek(fin, 0, SEEK_END) == 0);
    long long size = ftell(fin);
    assert(fseek(fin, -shift, SEEK_CUR) == 0);
    for(int i = 0; i < size - shift; i++){
        unsigned char data;
        assert(fseek(fin, -1, SEEK_CUR) == 0);
        assert(fread(&data, sizeof(data), 1, fin) == 1);
        assert(fseek(fin, -1, SEEK_CUR) == 0);

        unsigned char output = 0;
        //mirror
        for(int j = 0; j < 8; j++){
            output <<= 1;
            output |= (data >> j) & (unsigned char)1;
        }

        assert(fwrite(&output, sizeof(output), 1, fout) == 1);
    }
    
    assert(fseek(fin, 0, SEEK_END) == 0);
    for(int i = 0; i < shift; i++){
        unsigned char data;
        assert(fseek(fin, -1, SEEK_CUR) == 0);
        assert(fread(&data, sizeof(data), 1, fin) == 1);
        assert(fseek(fin, -1, SEEK_CUR) == 0);

        unsigned char output = 0;
        //mirror
        for(int j = 0; j < 8; j++){
            output <<= 1;
            output |= (data >> j) & (unsigned char)1;
        }

        assert(fwrite(&output, sizeof(output), 1, fout) == 1);
    }

    DEBUG("end operation\n");

    fclose(fin);
    return 0;
}