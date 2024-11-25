#define MAXROW 20
#define MAXNUMBER 5

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct seat{
    int car, row, number;
}Seat;

void set_Seat(Seat *seat, int car, int row, int number){
    seat->car = car;
    seat->row = row;
    seat->number = number;

    return;
}

void assign(const int num, const int car_num, bool (*seat)[MAXROW][MAXNUMBER], Seat *place,
            Seat *single_last, Seat *double_last){
    if(num == 1){
        for(int car = single_last->car; car < car_num; car++)
            for(int row = 0; row < MAXROW; row++)
                for(int number = 0; number < MAXNUMBER; number++)
                    if(!seat[car][row][number]){
                        set_Seat(place, car + 1, row + 1, number + 1);
                        seat[car][row][number] = true;
                        single_last->car = car;
                        return;
                    }
        fprintf(stderr, "not found seat\n");
        exit(-1);
    }
    else if(num == 2){
        for(int car = double_last->car; car < car_num; car++)
            for(int row = 0; row < MAXROW; row++){
                if(!seat[car][row][0] && !seat[car][row][1]){
                    set_Seat(place, car + 1, row + 1, 1);
                    set_Seat(place + 1, car + 1, row + 1, 2);
                    seat[car][row][0] = true, seat[car][row][1] = true;
                    double_last->car = car;
                    return;
                }
                else if(!seat[car][row][1] && !seat[car][row][2]){
                    set_Seat(place, car + 1, row + 1, 2);
                    set_Seat(place + 1, car + 1, row + 1, 3);
                    seat[car][row][1] = true, seat[car][row][2] = true;
                    double_last->car = car;
                    return;
                }
                else if(!seat[car][row][3] && !seat[car][row][4]){
                    set_Seat(place, car + 1, row + 1, 4);
                    set_Seat(place + 1, car + 1, row + 1, 5);
                    seat[car][row][3] = true, seat[car][row][4] = true;
                    double_last->car = car;
                    return;
                }
            
            }

        //not found then assign separate
        assign(1, car_num, seat, place, single_last, double_last);
        assign(1, car_num, seat, place + 1, single_last, double_last);
        return;
    }


    fprintf(stderr, "wrong num to assign\n");
    exit(-1);
}

int main(){
    int car_num;
    scanf("%d", &car_num);

    bool (*seat)[MAXROW][MAXNUMBER] = (bool (*)[MAXROW][MAXNUMBER])calloc(car_num, sizeof(bool [MAXROW][MAXNUMBER]));

    int request;
    Seat place[2];
    Seat last[2] = {0};
    while(scanf("%d", &request) != EOF){
        assert(request == 1 || request == 2);

        assign(request, car_num, seat, place, last, last + 1);
        for(int i = 0; i < request; i++)
            printf("%d %d %d%c", place[i].car, place[i].row, place[i].number, " \n"[i == request - 1]);
    }


    return 0;
}