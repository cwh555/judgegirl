#include "stationDistance.h"

#include <stdlib.h>

enum Station{
    R, G, B
};

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

int DistanceSameStation(int distance[], int start, int end){
    if(start == end)
        return 0;
    
    if(start > end)
        swap(&start, &end);

    int dist = 0;
    for(int i = start; i < end; i++)
        dist += distance[i - 1];

    return dist;
}


int stationDistance(int R_distance[],int G_distance[],int B_distance[],
                    int G_origin,int G_destination,int startStation[],
                    int endStation[]){
    //cnt the station num of G
    int G_cnt = 0;
    while(G_distance[G_cnt++] != 0)
        ;
    
    int *distanceArray[3] = {R_distance, G_distance, B_distance};
    int intersection[3] = {G_origin, 0, G_destination};

    if(startStation[0] == endStation[0]){
        int stationType = startStation[0];
        return DistanceSameStation(distanceArray[stationType], startStation[1], endStation[1]);
    }
    else if(startStation[0] == G || endStation[0] == G){
        if(endStation[0] == G){
            swap(&endStation[0], &startStation[0]);
            swap(&endStation[1], &startStation[1]);
        }

        int endType = endStation[0];
        int sum = DistanceSameStation(distanceArray[G], startStation[1],
                    (endType == R ? 1 : G_cnt));
        sum += DistanceSameStation(distanceArray[endType], intersection[endType], endStation[1]);
        return sum;
    }
    else{
        if(startStation[0] == B){
            swap(&startStation[0], &endStation[0]);
            swap(&startStation[1], &endStation[1]);
        }
        //form R to B
        int sum = DistanceSameStation(R_distance, startStation[1], G_origin);
        sum += DistanceSameStation(G_distance, 1, G_cnt);
        sum += DistanceSameStation(B_distance, G_destination, endStation[1]);
        return sum;
    }


}