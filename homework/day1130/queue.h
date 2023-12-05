#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include "net.h"

#define ELEMTYPE int
// 定义队列结构
#define MAX_SIZE 100

typedef struct {
    ELEMTYPE items[MAX_SIZE];
    int front;
    int rear;
} Queue;

// 初始化队列
void initQueue(Queue* queue) {
    queue->front = -1;
    queue->rear = -1;
}

// 检查队列是否为空
int isQEmpty(Queue* queue) {
    return (queue->front == -1 && queue->rear == -1);
}

// 检查队列是否已满
int isQFull(Queue* queue) {
    return (queue->rear == MAX_SIZE - 1);
}

// 入队操作
void enqueue(Queue* queue, int value) {
    if (isQFull(queue)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    if (isQEmpty(queue)) {
        queue->front = queue->rear = 0;
    } else {
        queue->rear++;
    }
    queue->items[queue->rear] = value;
}

// 出队操作
ELEMTYPE dequeue(Queue* queue) {
    if (isQEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    }
    ELEMTYPE value = queue->items[queue->front];
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front++;
    }
    return value;
}
#endif
