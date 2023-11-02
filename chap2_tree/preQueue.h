#ifndef PREQUEUE_H
#define PREQUEUE_H
#include <stdio.h>
#include <stdlib.h>

// 定义优先队列的元素
typedef struct {
    int data;
    int priority;
} QueueElement;

// 定义队列的结构
typedef struct {
    QueueElement *array;
    int capacity;
    int size;
} PriorityQueue;

// 创建一个队列,这里在堆区分配一个内存区域
PriorityQueue *createPriorityQueue(int capacity) {
    PriorityQueue *queue = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    queue->capacity = capacity;
    queue->size = 0;
    queue->array = (QueueElement *)malloc(sizeof(QueueElement) * capacity);
    return queue;
}

// 辅助函数,交换两个 QueueElement
void swap(QueueElement *a, QueueElement *b) {
    QueueElement temp = *a;
    *a = *b;
    *b = temp;
}

// 使得堆保持最小堆
void heapify(PriorityQueue *queue, int index) {
    // 这是利用数组存储一个堆
    
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < queue->size &&
        queue->array[left].priority < queue->array[smallest].priority) {
        smallest = left;
    }

    if (right < queue->size &&
        queue->array[right].priority < queue->array[smallest].priority) {
        smallest = right;
    }

    if (smallest != index) {
        swap(&queue->array[index], &queue->array[smallest]);
        heapify(queue, smallest);
    }
}

// 进队
void enqueue(PriorityQueue *queue, int data, int priority) {
    if (queue->size == queue->capacity) {
        printf("队列已满\n");
        return;
    }

    int i = queue->size;
    queue->size++;
    queue->array[i].data = data;
    queue->array[i].priority = priority;

    // 保持最小堆性质,上滤法
    while (i > 0 &&
           queue->array[(i - 1) / 2].priority > queue->array[i].priority) {
        swap(&queue->array[i], &queue->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// 出队操作：返回具有最高优先级的元素
QueueElement *dequeue(PriorityQueue *queue) {
    if (queue->size == 0) {
        printf("队列为空\n");
        return NULL;
    }

    if (queue->size == 1) {
        queue->size--;
        return &queue->array[0];
    }

    // 交换队列的第一个元素（最小优先级）和最后一个元素
    QueueElement *root = &queue->array[0];
    queue->array[0] = queue->array[queue->size - 1];
    // 删除最后一个元素
    queue->size--;

    // 保持最小堆性质
    heapify(queue, 0);
    return root;
}
#endif