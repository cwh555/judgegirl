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
        if(compare){
            printf(">%s", query);
        }
        else{
            compare = similar(dict, query, dict_num);
        }
        
        if(compare){
            printf("\n");
        }
        else
            printf("!%s\n", query);
        
    }



}

bool same(char (*dict)[105], char *input, int dict_num){
    bool ans = false;
    for(int i = 0; i < dict_num && !ans; i++)
        if(strcmp(input, dict[i]) == 0)
            ans = true;

    return ans;
}

#define debug
bool similar(char (*dict)[105], char *input, int dict_num){
    bool first = true;

    bool replace = true;
    bool add = true;
    bool remove = true;

    int input_len = strlen(input);
    for(int i = 0; i < dict_num; i++){
        int len = strlen(dict[i]);

        replace = true;
        if(input_len != len)
            replace = false;
        
        add = true;
        if(input_len != len + 1)
            add = false;

        remove = true;
        if(input_len != len - 1)
            remove = false;

        //開始檢查
        bool diff_replace = false;
        bool diff_add = false;
        bool diff_remove = false;
        for(int j = 0; j < len && (replace || add || remove); j++){
            if(replace && dict[i][j] != input[j]){
                if(!diff_replace)
                    diff_replace = true;
                else
                    replace = false;
            }
            if(add && dict[i][j] != input[j + diff_add]){
                if(dict[i][j] != input[j + 1])
                    add = false;
                else if(!diff_add)
                    diff_add = true;
                else
                    add = false;
            }
            if(remove && dict[i][j + diff_remove] != input[j]){
                if(dict[i][j + 1] != input[j])
                    remove = false;
                else if(!diff_remove)
                    diff_remove = true;
                else
                    remove = false;
            }
        }


        if(replace | add | remove){
            if(first)
                printf("?%s", dict[i]);
            else
                printf(" %s", dict[i]);
            first = false;
        }
    }

    return !first;
}