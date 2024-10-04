#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool same(char (*dict)[105], char *input, int dict_num);
bool similar(char (*dict)[105], char *input, int dict_num);

int main(){
    int dict_num;
    scanf("%d", &dict_num);

    char (*dict)[105] = (char(*)[105])malloc(sizeof(char[105]) * dict_num);
    for(int i = 0; i < dict_num; i++)
        scanf("%s", dict[i]);

    int query_num;
    scanf("%d", &query_num);
    for(int i = 0; i < query_num; i++){
        char query[105];
        scanf("%s", query);

        bool compare = same(dict, query, dict_num);
        if(compare)
            printf(">%s", query);
        else
            compare = similar(dict, query, dict_num);

        if(compare)
            printf("\n");
        else
            printf("!%s\n", query);

        
    }



}

bool same(char (*dict)[105], char *input, int dict_num){
    bool ans = false;
    for(int i = 0; i < dict_num && !ans; i++)
        ans = (strcmp(input, dict[i]) == 0);
            
    return ans;
}

bool similar(char (*dict)[105], char *input, int dict_num){
    bool first = true;

    bool replace = true, add = true, remove = true;

    int input_len = strlen(input);
    for(int i = 0; i < dict_num; i++){
        int len = strlen(dict[i]);

        replace = (input_len == len);        
        add = (input_len == len + 1);
        remove = (input_len == len - 1);

        //開始檢查
        bool diff = false;
        for(int j = 0; j < len && (replace || add || remove); j++){
            //replace 在第一不同的下次開始再比較
            //add remove只要一有不同的就要比了
            replace &= (!diff || dict[i][j] == input[j]);

            diff |= (dict[i][j] != input[j]);

            add &= (!diff || dict[i][j] == input[j + 1]);
            remove &= (!diff || dict[i][j + 1] == input[j]);
        }

        if(replace || add || remove){
            printf("%c%s", " ?"[first], dict[i]);
            first = false;
        }
    }

    return !first;
}