#include "tree.h"
#include <stdlib.h>
 
Node *construct(int array[], int n){
    Node** pointer = (Node**)malloc(sizeof(Node*) * n);
    for(int i = 0; i < n; i++){
        Node *now = (Node*)malloc(sizeof(Node));
        now->label = array[i];
        now->left = NULL;
        now->right = NULL;
        if(i % 2 == 0 && (i - 2) / 2 >= 0) 
            pointer[(i - 2) / 2]->right = now;
        else if((i - 1) / 2 >= 0)
            pointer[(i - 1) / 2]->left = now;
 
        pointer[i] = now;
    }
 
    Node *root = pointer[0];
    free(pointer);
 
    return root;
}