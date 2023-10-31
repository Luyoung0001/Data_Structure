#ifndef STACK_H
#define STACK_H
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

// 定义顺序栈结构
typedef struct {
    ElemType *data[MAX_SIZE];
    int top;
} Stack;

// 初始化栈
void initStack(Stack *stack) { stack->top = -1; }

// 判空
int isStackEmpty(Stack *stack) { return stack->top == -1; }

// 判满
int isStackFull(Stack *stack) { return stack->top == MAX_SIZE - 1; }

// 入栈
void push(Stack *stack, ElemType *item) {
    if (isStackFull(stack)) {
        printf("栈已满!\n");
    } else {
        stack->data[++stack->top] = item;
    }
}

// 出栈
ElemType *pop(Stack *stack) {
    if (isStackEmpty(stack)) {
        printf("栈为空!\n");
        return NULL;
    } else {
        return stack->data[stack->top--];
    }
}

// 获得栈顶元素
ElemType *peek(Stack *stack) {
    if (isStackEmpty(stack)) {
        printf("栈为空,无法获取栈顶元素!\n");
        return NULL;
    } else {
        return stack->data[stack->top];
    }
}

#endif // STACK_H