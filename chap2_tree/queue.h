#ifndef QUEUE_H
#define QUEUE_H
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

// 队列定义
typedef struct {
    ElemType *items[MAX_QUEUE_SIZE]; // 队列
    int front;                       // 头指针
    int rear;                        // 尾指针
} Queue;

// 一些对应于队列的基本操作

// 初始化队列
void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}
// 判断队列是否为空
int isQueueEmpty(Queue *q) { return q->front == -1; }

// 判断队列是否满
int isQueueFull(Queue *q) { return (q->rear + 1) % MAX_QUEUE_SIZE == q->front; }
// 入队
void enQueue(Queue *q, ElemType *item) {
    if (isQueueFull(q)) {
        printf("队列已满!\n");
        return;
    } else if (isQueueEmpty(q)) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->items[q->rear] = item;
}

// 出队
ElemType *deQueue(Queue *q) {
    // 这里得注意,这个item是局部变量,返回它的地址有一定的风险,可能返回后,内存被回收
    // 当函数返回时，局部变量 item
    // 所占用的栈空间将被释放，但返回了指向这个局部变量的指针。 这意味着，尽管
    // item 本身的生存期已经结束，但指向它的指针可能仍然有效。 这通常称为
    // "悬挂指针"（dangling pointer）问题,因此影响不大.但是尽量应该避免这种问题
    ElemType *item = NULL;
    if (isQueueEmpty(q)) {
        printf("队列为空!\n");
    } else {
        item = q->items[q->front];
        if (q->front == q->rear) {
            // 队列中只有一个元素,出去就变成了空队
            q->front = -1;
            q->rear = -1;
        } else {
            q->front = (q->front + 1) % MAX_QUEUE_SIZE;
        }
    }
    return item;
}
#endif // QUEUE_H