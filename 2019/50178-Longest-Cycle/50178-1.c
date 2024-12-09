#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void traverse(bool first, const bool **road, const int num, int cityNow, int lenNow, int *path,
                bool *visited, int *max, int *maxAns){

    if(cityNow == 0 && !first){
        bool update = false;
        if(lenNow > *max)
            update = true;
        else if(lenNow == *max){
            for(int i = 0; i < lenNow; i++){
                if(path[i] < maxAns[i]){
                    update = true;
                    break;
                }
                else if(path[i] > maxAns[i]){
                    update = false;
                    break;
                }
            }
        }

        if(update){
            *max = lenNow;
            for(int i = 0; i < lenNow; i++)
                maxAns[i] = path[i];
        }

        return;
    }
    
    for(int i = 0; i < num; i++){
        if(!visited[i] && road[cityNow][i]){
            visited[i] = true;
            path[lenNow] = i;
            traverse(false, road, num, i, lenNow + 1, path, visited, max, maxAns);
            visited[i] = false;
        }
    }

    return;
}

int main(){
    int city_num;
    scanf("%d", &city_num);
    bool **road = (bool **)malloc(sizeof(bool*) * city_num);
    for(int i = 0; i < city_num; i++){
        road[i] = (bool *)malloc(sizeof(bool) * city_num);
        for(int j = 0; j < city_num; j++){
            int temp;
            scanf("%d", &temp);
            road[i][j] = (temp == 1);
        }
    }

    bool *visited = (bool *)calloc(city_num, sizeof(bool));
    int *path = (int *)malloc(sizeof(int) * city_num);
    int *maxAns = (int *)malloc(sizeof(int) * city_num);
    int max = 0;
    traverse(true, road, city_num, 0, 0, path, visited, &max, maxAns);
    for(int i = 0; i < max - 1; i++)
        printf("%d%c", maxAns[i], " \n"[i == max - 2]);
    
    free(visited);
    free(path);
    free(maxAns);
    for(int i = 0; i < city_num; i++)
        free(road[i]);


}