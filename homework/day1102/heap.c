#include "minHeap.h"
#define HEAP_SIZE 10
int main() {
    minHeap *heap = (minHeap *)malloc(sizeof(minHeap));
    initHeap(heap, HEAP_SIZE);

    // 初始化第一个根节点
    heap->data[0] = 5;
    heap->size = 1;
    insert(heap, &(heap->size), 1);
    insert(heap, &(heap->size), 2);
    insert(heap, &(heap->size), 6);
    insert(heap, &(heap->size), 7);
    insert(heap, &(heap->size), 4);
    insert(heap, &(heap->size), 3);
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n删除元素:\n");
    int num = heap->size;
    // 从堆区中删除
    for (int i = 0; i < num; i++) {
        ElemType *ret = delete(heap, &(heap->size));
        if (ret == NULL) {
            printf("无法删除元素\n");
        } else {
            printf("%d ", *ret);
            free(ret); // 释放删除元素的内存
        }
    }

    return 0;
}