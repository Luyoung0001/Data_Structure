#include <stdio.h>
typedef struct p {
    int px, py;
} Point;

// 定义队列结构
#define MAX_SIZE 100

typedef struct {
    Point items[MAX_SIZE];
    int front;
    int rear;
} Queue;

// 初始化队列
void initQueue(Queue* queue) {
    queue->front = -1;
    queue->rear = -1;
}

// 检查队列是否为空
int isEmpty(Queue* queue) {
    return (queue->front == -1 && queue->rear == -1);
}

// 检查队列是否已满
int isFull(Queue* queue) {
    return (queue->rear == MAX_SIZE - 1);
}

// 入队操作
void enqueue(Queue* queue, Point value) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    if (isEmpty(queue)) {
        queue->front = queue->rear = 0;
    } else {
        queue->rear++;
    }
    queue->items[queue->rear] = value;
}

// 出队操作
Point dequeue(Queue* queue) {
    Point emptyPoint = { -1, -1 }; // 表示出错的特殊值
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return emptyPoint;
    }
    Point value = queue->items[queue->front];
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front++;
    }
    return value;
}
