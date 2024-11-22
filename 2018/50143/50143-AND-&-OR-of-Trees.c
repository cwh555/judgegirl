#include "tree.h"
#include <stdlib.h>

Node *newNode(int data){
    Node *new = (Node *)malloc(sizeof(Node));

    new->left = NULL;
    new->right = NULL;
    new->val = data;

    return new;
}

Node *treeAND(Node *root1, Node *root2){
    if(root1 == NULL || root2 == NULL)
        return NULL;

    Node *new = newNode(root1->val * root2->val);

    new->left = treeAND(root1->left, root2->left);
    new->right = treeAND(root1->right, root2->right);

    return new;
}

Node *treeOR(Node *root1, Node *root2){
    if(root1 == NULL && root2 == NULL)
        return NULL;
    else if(root1 == NULL){
        Node *new = newNode(root2->val);
        new->left = treeOR(NULL, root2->left);
        new->right = treeOR(NULL, root2->right);

        return new;
    }
    else if(root2 == NULL){
        Node *new = newNode(root1->val);
        new->left = treeOR(root1->left, NULL);
        new->right = treeOR(root1->right, NULL);

        return new;
    }

    Node *new = newNode(root1->val + root2->val);

    new->left = treeOR(root1->left, root2->left);
    new->right = treeOR(root1->right, root2->right);

    return new;
}
