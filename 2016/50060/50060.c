#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAXLEN 10000
 
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
 
void walk(const int vertex_num, const int **edge, const int start, int rest_vertex, int distance, int index_now, bool *before, int *min);
 
 
int main(){
    int vertex_num;
    scanf("%d", &vertex_num);
 
    int **edge = (int**)malloc(sizeof(int*) * vertex_num);
    for(int i = 0; i < vertex_num; i++){
        edge[i] =  (int*)malloc(sizeof(int) * vertex_num);
 
        for(int j = 0; j < vertex_num; j++)
            scanf("%d", &edge[i][j]);
    }
 
    bool *before = (bool*)calloc(vertex_num, sizeof(bool));
    int min = MAXLEN;
 
    //choose a start vertex
    before[0] = true;
    walk(vertex_num, edge, 0, vertex_num - 1, 0, 0, before, &min);    
 
    free(before);
    for(int i = 0; i < vertex_num; i++)
        free(edge[i]);
    free(edge);
 
    printf("%d\n", min);
 
}
 
void walk(const int vertex_num, const int **edge, const int start, int rest_vertex, int distance, int index_now, bool *before, int *min){
    if(rest_vertex == 0){
        *min = MIN((*min), distance + edge[index_now][start]);
        return;
    }
    else if(distance >= *min)
        return;
 
    //walk to each vertex
    for(int i = 0; i < vertex_num; i++){
        if(before[i])
            continue;
 
        //walk to this vertex
        before[i] = true;
        walk(vertex_num, edge, start, rest_vertex - 1, distance + edge[index_now][i], i, before, min);
 
        //backtracking
        before[i] = false;
    }
 
    return;
}