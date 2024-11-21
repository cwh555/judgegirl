#include "merge.h"
#include <stdlib.h>

Node *merge(Node *list[], int K){
    int rest = K;
    //caculate rest
    for(int i = 0; i < K; i++)
        if(list[i] == NULL)
            rest--;

    Node *first = NULL;
    Node *before = NULL;

    while(rest > 0){

        //forward
        for(int i = 0; i < K; i++){
            if(list[i] == NULL)
                continue;

            if(before != NULL)
                before->next = list[i];
            else
                first = list[i];
            
            before = list[i];

            list[i] = list[i]->next;
            if(list[i] == NULL)
                rest--;
        }

        //backward
        for(int i = K - 1; i >= 0; i--){
            if(list[i] == NULL)
                continue;

            before->next = list[i];
            before = list[i];

            list[i] = list[i]->next;
            if(list[i] == NULL)
                rest--;
        }
    }    

    return first;
}
