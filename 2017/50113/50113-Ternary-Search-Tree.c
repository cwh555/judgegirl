#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#include "construct.h"
#include <stdlib.h>

Node *newNode(int data){
    Node *new = (Node *)malloc(sizeof(Node));
    new->large = data;
    new->small = -1;
    new->left = NULL;
    new->right = NULL;
    new->mid = NULL;

    return new;
}

Node *insertNode(int data, Node *node){
    if(node == NULL){
        //insert a node with one data
        return newNode(data);
    }

    //if go to a node with only one data
    if(node->small == -1){
        int ori_data = node->large;
        node->large = MAX(data, ori_data);
        node->small = MIN(data, ori_data);

        return node;
    }
    
    //other case: insert the node with recurision
    if(node->small > data)
        node->left = insertNode(data, node->left);
    else if(node->large < data)
        node->right = insertNode(data, node->right);
    else
        node->mid = insertNode(data, node->mid);

    return node;
}

Node *ConstructTree(int sequence[],int N){
    Node *root = NULL;
    for(int i = 0; i < N; i++)
        root = insertNode(sequence[i], root);

    return root;
}