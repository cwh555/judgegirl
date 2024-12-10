#include "calArea.h"

int calArea(NODE* head){
    NODE *first = head;
    NODE *second = head;
    
    int area = 0;
    int height = 0;

    while(first != second || first == head){
        while(first->rightPtr != NULL){
            height++;
            first = first->rightPtr;
        }

        while(first->downPtr != NULL && second->downPtr != NULL){
            area += height;
            first = first->downPtr;
            second = second->downPtr;
        }

        while(second->rightPtr != NULL){
            height--;
            second = second->rightPtr;
        }

    }

    return area;

}
