#include <stdio.h>
#include <stdlib.h>

// 定义栈结构
#define MAX_SIZE 100

typedef struct {
    int items[MAX_SIZE];
    int top;
} Stack;

// 初始化栈
void initStack(Stack* stack) {
    stack->top = -1;
}

// 检查栈是否为空
int isEmpty(Stack* stack) {
    return (stack->top == -1);
}

// 检查栈是否已满
int isFull(Stack* stack) {
    return (stack->top == MAX_SIZE - 1);
}

// 入栈操作
void push(Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Stack is full. Cannot push.\n");
        return;
    }
    stack->top++;
    stack->items[stack->top] = value;
}

// 出栈操作
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty. Cannot pop.\n");
        return -1; // 返回一个特殊值表示出错
    }
    int value = stack->items[stack->top];
    stack->top--;
    return value;
}

// 获取栈顶元素
int top(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty. Cannot get top element.\n");
        return -1; // 返回一个特殊值表示出错
    }
    return stack->items[stack->top];
}

