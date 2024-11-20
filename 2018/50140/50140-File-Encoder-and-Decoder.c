#include <assert.h>
#include <stdio.h>

void bin2ascii(char input_file[32], char output_file[32], char dict[17]){
    FILE *fin = fopen(input_file, "rb");
    FILE *fout = fopen(output_file, "w");

    unsigned char data;
    while(fread(&data, sizeof(unsigned char), 1, fin) == 1){
        assert(fwrite(&dict[data >> 4], sizeof(char), 1, fout) == 1);
        assert(fwrite(&dict[data & ((1 << 4) - 1)], sizeof(char), 1, fout) == 1);
    }

    fclose(fin);
    fclose(fout);

    return;
}

unsigned char find(char dict[17], unsigned char data){
    for(int i = 0; i < 16; i++)
        if(dict[i] == data)
            return i;
    return -1;
}

void ascii2bin(char input_file[32], char output_file[32], char dict[17]){
    FILE *fin = fopen(input_file, "r");
    FILE *fout = fopen(output_file, "wb");

    unsigned char data1, data2;
    while(fread(&data1, sizeof(unsigned char), 1, fin) == 1){
        assert(fread(&data2, sizeof(unsigned char), 1, fin) == 1);

        //find data1 and data2 in dict
        data1 = find(dict, data1);
        data2 = find(dict, data2);

        data1 = (data1 << 4) | data2;

        assert(fwrite(&data1, sizeof(unsigned char), 1, fout) == 1);
    }

    fclose(fin);
    fclose(fout);

    return;
}
