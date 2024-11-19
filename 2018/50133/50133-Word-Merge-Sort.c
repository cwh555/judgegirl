#define MAXLEN 100005

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void merge(char *buffer, char *new){
    int buffer_index = 0, new_index = 0;
    char record[MAXLEN] = {0};
    int record_index = 0;
    
    while(buffer[buffer_index] != '\0' && new[new_index] != '\0'){
        int buffer_value = buffer[buffer_index] * 26 * 26 +
             buffer[buffer_index + 1] * 26 + buffer[buffer_index + 2];
        int new_value = new[new_index] * 26 * 26 +
            new[new_index + 1] * 26 + new[new_index + 2];

        if(buffer_value < new_value){
            for(int i = 0; i < 3; i++)
                record[record_index++] = buffer[buffer_index++];
        }
        else{
            for(int i = 0; i < 3; i++)
                record[record_index++] = new[new_index++];
        }
    }

    if(buffer[buffer_index] == '\0')
        strcat(record + record_index, new + new_index);
    else
        strcat(record + record_index, buffer + buffer_index);

    strcpy(buffer, record);

    return;
}

int main(){
    char buffer[MAXLEN];
    scanf("%s", buffer);

    char new[MAXLEN];
    while(scanf("%s", new) != EOF){
        merge(buffer, new);

        printf("%s\n", buffer);
    }

}