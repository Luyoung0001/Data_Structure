#ifndef NET_H
#define NET_H
#include <stdio.h>
#include <stdlib.h>
// 邻接表
// 结点结构
typedef struct node {
    int index;
    struct node *next;
} Node;

// 图的头结点结构
typedef struct headNode {
    char value;
    Node *listHead;
} HeadNode;

// 创建结点
Node *createNode(int index) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->index = index;
    newNode->next = NULL;
    return newNode;
}
#endif
