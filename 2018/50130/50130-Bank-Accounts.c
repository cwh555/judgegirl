#define MAXLEN 40

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct bank{
    int money;
    char name[MAXLEN];
}Bank;

typedef enum{
    INVALID, EARNS, SPENDS, GIVES, BECOMES
}Instruction;


int get_index(Bank *data, int num, char *name){
    int find = -1;

    for(int i = 0; i < num && find == -1; i++){
        if(strcmp(data[i].name, name) == 0)
            find = i;
    }
    
    return find;
}


int main(){
    int user_num;
    scanf("%d", &user_num);

    Bank *data = (Bank*)malloc(sizeof(Bank) * user_num);
    for(int i = 0; i < user_num; i++)
        scanf("%s %d", data[i].name, &data[i].money);

    //刪除換行符號
    char c;
    while((c = getchar()), c != '\n');

    char input[MAXLEN * 5];
    while(fgets(input, MAXLEN * 5, stdin) != NULL){
        char *name1;
        char *instruction;

        name1 = strtok(input, " ");
        instruction = strtok(NULL, " ");

        if(strstr(instruction, "earns") != NULL){
            int amount = atoi(strtok(NULL, " "));

            int index = get_index(data, user_num, name1);
            if(index == -1)
                continue;
            else
                data[index].money += amount;
        }
        else if(strstr(instruction, "spends") != NULL){
            int amount = atoi(strtok(NULL, " "));

            int index = get_index(data, user_num, name1);
            if(index == -1 || data[index].money < amount)
                continue;
            else
                data[index].money -= amount;
        }
        else if(strstr(instruction, "gives") != NULL){
            char *name2 = strtok(NULL, " ");
            int amount = atoi(strtok(NULL, " "));

            int index1 = get_index(data, user_num, name1);
            int index2 = get_index(data, user_num, name2);
            if(index1 == -1 || index2 == -1 || data[index1].money < amount)
                continue;
            else{
                data[index1].money -= amount;
                data[index2].money += amount;
            }
        }
        else if(strstr(instruction, "becomes") != NULL){
            int amount = atoi(strtok(NULL, " "));

            int index = get_index(data, user_num, name1);
            if(index == -1)
                continue;
            else
                data[index].money = amount;
        }
    }

    for(int i = 0; i < user_num; i++)
        printf("%s %d\n", data[i].name, data[i].money);
    
    free(data);
}