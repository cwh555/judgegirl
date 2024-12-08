#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void twoDimension(int index, int size, int *row, int *col){
    *row = index / size;
    *col = index % size;
    return;
}

int turn(bool **map, int size, int press){
    int row, col;
    twoDimension(press, size, &row, &col);
    int dx[5] = {0, 1, 0, -1, 0};
    int dy[5] = {-1, 0, 1, 0, 0};
    int count = 0;
    for(int dir = 0; dir < 5; dir++){
        int nr = row + dx[dir];
        int nc = col + dy[dir];
        if(nr >= 0 && nr < size && nc >= 0 && nc < size){
            if(map[nr][nc])
                count++;
            else
                count--;
            map[nr][nc] = !map[nr][nc];
        }
    }

    return count;
}

void solve(int index_now, bool **map, int size, int rest_num, int *solution, int step_num,
                int *best, int *best_step){
    if(rest_num == 0){
        bool update = false;
        if(step_num < *best_step)
            update = true;
        else if(step_num == *best_step){
            for(int i = 0; i < step_num; i++){
                if(solution[i] < best[i]){
                    update = true;
                    break;
                }else if(solution[i] > best[i]){
                    update = false;
                    break;
                }
            }
        }

        if(update){
            *best_step = step_num;
            for(int i = 0; i < step_num; i++)
                best[i] = solution[i];
        }
        return;
    }
    else if(index_now == size * size)
        return;
    else if(rest_num / 5 + step_num > *best_step)
        return;
    else{
        int row, col;
        twoDimension(index_now, size, &row, &col);
        row--;
        col--;
        if(row >= 0 && row < size && col >= 0 && col < size && map[row][col])
            return;
    }

    //press or not press
    solution[step_num] = index_now;
    int change_num = turn(map, size, index_now);
    solve(index_now + 1, map, size, rest_num - change_num, solution, step_num + 1,
            best, best_step);

    turn(map, size, index_now);
    solve(index_now + 1, map, size, rest_num, solution, step_num, best, best_step);

    return;
}

int main(){
    int size;
    scanf("%d", &size);

    bool **map = (bool **)malloc(sizeof(bool*) * size);
    for(int i = 0; i < size; i++)
        map[i] = (bool *)calloc(size, sizeof(bool));

    int on;
    int on_num = 0;
    while(scanf("%d", &on) != EOF){
        int row, col;
        twoDimension(on, size, &row, &col);
        map[row][col] = true;
        on_num++;
    }

    int best_step = size * size;
    int *best = (int *)malloc(sizeof(int) * size * size);
    int *solution = (int *)malloc(sizeof(int) * size * size);
    int step_now = 0;
    solve(0, map, size, on_num, solution, step_now, best, &best_step);

    for(int i = 0; i < best_step; i++)
        printf("%d%c", best[i], " \n"[i == best_step - 1]);
    
    free(best);
    free(solution);

    return 0;
}