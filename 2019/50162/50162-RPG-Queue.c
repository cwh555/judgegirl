#define MAXSIZE 5000

#include <stdio.h>
#include <stdlib.h>

typedef struct queue{
    int front, rear;
    int data[MAXSIZE];
}Queue;

void init(Queue *queue){
    queue->front = 0;
    queue->rear = 0;

    return;
}

void enqueue(Queue *queue, int data){
    queue->data[queue->front] = data;
    queue->front = (queue->front + 1) % MAXSIZE;

    return;
}

int dequeue(Queue *queue){
    int data = queue->data[queue->rear];
    queue->rear = (queue->rear + 1 + MAXSIZE) % MAXSIZE;

    return data; 
}

int getSize(const Queue *queue){
    return (queue->front - queue->rear + MAXSIZE) % MAXSIZE;
}

int main(){
    int data;
    Queue dps, healer, tank;
    init(&dps);
    init(&healer);
    init(&tank);

    while(scanf("%d", &data) != EOF){
        switch(data % 3){
            case 0:
                enqueue(&dps, data);
                break;
            case 1:
                enqueue(&healer, data);
                break;
            case 2:
                enqueue(&tank, data);
                break;
            default:
                fprintf(stderr, "impossible case\n");
                exit(-1);
        }

        if(getSize(&dps) >= 3 && getSize(&healer) >= 1 && getSize(&tank) >= 1){
            int member;
            for(int i = 0; i < 3; i++){
                member = dequeue(&dps);
                printf("%d ", member);
            }

            member = dequeue(&healer);
            printf("%d ", member);
            member = dequeue(&tank);
            printf("%d\n", member);
        }
    }
    return 0;
}