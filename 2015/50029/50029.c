#include "tree.h"
#include <stdlib.h>
 
Node *tree(int array[], int n, int now){
    if(now >= n)
        return NULL;
 
    Node *node = (Node*)malloc(sizeof(Node));
    node->label = array[now];
    node->left = tree(array, n, now * 2 + 1);
    node->right = tree(array, n, now * 2 + 2);
 
    return node;
 
}
 
Node *construct(int array[], int n){
    return tree(array, n, 0);
}