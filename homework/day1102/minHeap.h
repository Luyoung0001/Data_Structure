#ifndef MINHEAP_H
#define MINHEAP_H
#include <stdio.h>
#include <stdlib.h>
// #include "tree.h"

#define ElemType int
// 定义一个堆
typedef struct {
    ElemType *data;
    int size;
    int capacity;
} minHeap;
// 交换
void swap(ElemType *a, ElemType *b) {
    ElemType temp = *a;
    *a = *b;
    *b = temp;
}
// 初始化一个堆
void initHeap(minHeap *heap, int capacity) {
    heap->capacity = capacity;
    heap->size = 0;
    ElemType *data = (ElemType *)malloc(sizeof(ElemType) * capacity);
    heap->data = data;
}

// 插入元素

void insert(minHeap *heap, int *size, ElemType value) {
    int i = *size;
    *size = *size + 1;
    heap->data[i] = value;
    // 上浮
    while (i > 0 && heap->data[(i - 1) / 2] > heap->data[i]) {
        swap(&heap->data[(i - 1) / 2], &heap->data[i]);
        i = (i - 1) / 2;
    }
}

// 删除元素

ElemType *delete(minHeap *heap, int *size) {
    if (*size <= 0) {
        printf("堆已空,无法删除元素!\n");
        return NULL;
    }
    int i = *size;
    *size = *size - 1;
    // 拿到值
    ElemType *minRet = (ElemType*)malloc(sizeof(ElemType));
    *minRet = heap->data[0];
    // 用最后一个元素替代第一个
    heap->data[0] = heap->data[*size];
    // 下浮
    int k = 0;
    while (1) {

        int left = 2 * k + 1;
        int right = 2 * k + 2;
        int smallest = k;

        if (heap->data[left] < heap->data[smallest]) {
            k = left;
        }

        if (heap->data[right] < heap->data[smallest]) {
            k = right;
        }
        // 如果 smallest 被更新,就交换
        if (smallest != k) {
            swap(&heap->data[k], &heap->data[smallest]);
            k = smallest;
        } else {
            break;
        }
    }
    return minRet;
}

#endif
