#include "merge.h"
#include <stdlib.h>
#include <stdio.h>

enum {
    ZIG, TOP = 1, BOTTOM = -1
};

Node *dir_merge(Node *list[], int K, int type, Node **before){
    *before = NULL;
    Node *first = NULL;

    int dir = (type == TOP ? 1 : -1);
    int start = (type == TOP ? 0 : K - 1);
    int end = (type == TOP ? K : -1);
    
    for(int i = start; i != end; i += dir){
        if(list[i] == NULL)
            continue;
        
        if(first == NULL)
            first = list[i];
        else
            (*before)->next = list[i];
        
        (*before) = list[i];
        list[i] = list[i]->next;
    }

    return first;
}


Node *merge(Node *list[], int K){
    int dir = BOTTOM;
    #ifdef TOPDOWN
        dir = TOP;
    #endif

    //find the first one
    Node *first = NULL;
    Node *before = NULL;
    do{
        #ifdef ZIGZAG
            dir = (dir == TOP ? BOTTOM : TOP);
        #endif

        Node *last = NULL;
        Node *head = dir_merge(list, K, dir, &last);
        if(first == NULL)
            first = head;
        else
            before->next = head;
        
        before = last;
    }while(before != NULL);

    return first;
}
