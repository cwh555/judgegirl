#define MAXSIZE 100005

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    char data[MAXSIZE] = "\0";
    scanf("%s", data);
    int len = strlen(data);
    char cmd[10], sx[10], sy[10];
    char cx, cy;

    while(scanf("%s", cmd) != EOF && strcmp(cmd, "end") != 0){
        if(strcmp(cmd, "replace") == 0){
            scanf("%s %s", sx, sy);
            cx = sx[0], cy = sy[0];

            for(int i = 0; i < len; i++)
                if(data[i] == cx)
                    data[i] = cy;
        }
        else if(strcmp(cmd, "remove") == 0){
            scanf("%s", sx);
            cx = sx[0];
            int new_len = 0;
            for(int i = 0; i < len; i++){
                while(data[i] == cx)
                    i++;
                if(i < len)
                    data[new_len++] = data[i];
            }
            data[new_len] = '\0';
            len = new_len;
        }
        else if(strcmp(cmd, "addhead") == 0){
            scanf("%s", sx);
            cx = sx[0];
            for(int i = len; i > 0; i--)
                data[i] = data[i - 1];
            data[0] = cx;
            data[++len] = '\0';
        }
        else if(strcmp(cmd, "addtail") == 0){
            scanf("%s", sx);
            cx = sx[0];
            data[len++] = cx;
            data[len] = '\0';
        }
        else{
            printf("invalid command %s\n", cmd);
        }

    }

    printf("%s\n", data);


}