#include "sub.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void substring(Node* text, Node* pattern){
    bool find = false;

    int text_index = 0;
    for(; !find; text_index++, text = text->next){
        if(text->c == pattern->c){
            Node *copy_text = text;
            Node *copy_pattern = pattern;

            int sum = 0;
            int index = text_index;
            while(copy_text->c == copy_pattern->c){
                copy_pattern = copy_pattern->next;
                copy_text = copy_text->next;                
                sum += index++;

                if(copy_pattern == NULL){
                    printf("%d\n", sum);
                    return;
                }
            }
        }
    }

    return;
}

void subsequence(Node* text, Node* pattern){
    int sum = 0;
    int text_index = 0;
    while(pattern != NULL){
        if(text->c == pattern->c){
            sum += text_index;
            pattern = pattern->next;
        }

        text = text->next;
        text_index++;
    }

    printf("%d\n", sum);
    return;
}