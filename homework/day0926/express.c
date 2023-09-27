#include "stack.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// 声明
void printStack();
char expression[100];

// 初始化
Stack operandStack;
Stack operatorStack;
// 判断运算符的优先级
int precedence(char operator) {
    if (operator== '+' || operator== '-') {
        return 1;
    } else if (operator== '*' || operator== '/') {
        return 2;
    }
    return 0;
}

// 计算
int evaluateExpression(const char *expression) {
    // 初始化
    initStack(&operandStack);
    initStack(&operatorStack);
    // 处理表达式
    int i = 0;
    while (expression[i] != '#' && expression[i] != '\0') {
        sleep(1);
        printStack();
        if (expression[i] == ' ' || expression[i] == '\t') {
            // 忽略空格和制表符
            i++;
            continue;
        } else if (isdigit(expression[i])) {
            // 如果是数字字符,则解析整个数字并入栈
            int num = 0;
            // 数字处理,有可能是几位数
            while (isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            // 进栈
            push(&operandStack, num);
        } else if (expression[i] == '+' || expression[i] == '-' ||
                   expression[i] == '*' || expression[i] == '/') {
            // 如果是运算符

            while (!isEmpty(&operatorStack) &&
                   precedence(expression[i]) <=
                       precedence(top(&operatorStack))) {
                // 如果当前运算符的优先级不高
                // 弹出两个操作数和一个运算符
                char op = pop(&operatorStack);
                int operand2 = pop(&operandStack);
                int operand1 = pop(&operandStack);

                switch (op) {
                case '+':
                    push(&operandStack, operand1 + operand2);
                    break;
                case '-':
                    push(&operandStack, operand1 - operand2);
                    break;
                case '*':
                    push(&operandStack, operand1 * operand2);
                    break;
                case '/':
                    if (operand2 == 0) {
                        // 直接退出
                        printf("除以零错误.\n");
                        exit(1);
                    }
                    push(&operandStack, operand1 / operand2);
                    break;
                }
            }
            // 否则,op 进栈
            push(&operatorStack, expression[i]);
            i++;
        } else if (expression[i] == '(') {
            // 如果是左括号,直接入操作栈
            push(&operatorStack, expression[i]);
            i++;
        } else if (expression[i] == ')') {
            // 如果是右括号,就开始处理,已知 pop,直到遇到最近的左括号
            while (!isEmpty(&operatorStack) && top(&operatorStack) != '(') {
                char op = pop(&operatorStack);
                int operand2 = pop(&operandStack);
                int operand1 = pop(&operandStack);
                switch (op) {
                case '+':
                    push(&operandStack, operand1 + operand2);
                    break;
                case '-':
                    push(&operandStack, operand1 - operand2);
                    break;
                case '*':
                    push(&operandStack, operand1 * operand2);
                    break;
                case '/':
                    if (operand2 == 0) {
                        // 直接退出
                        printf("除以零错误.\n");
                        exit(1);
                    }
                    push(&operandStack, operand1 / operand2);
                    break;
                }
            }
            // 弹出左括号
            if (!isEmpty(&operatorStack) && top(&operatorStack) == '(') {
                pop(&operatorStack);
            } else {
                // 否则错误
                exit(1);
            }
            // 略过右括号
            i++;
        } else {
            printf("输入错误:%c\n", expression[i]);
            exit(1);
        }
    }

    // 处理栈
    while (!isEmpty(&operatorStack)) {
        sleep(1);
        printStack();
        char op = pop(&operatorStack);
        int operand2 = pop(&operandStack);
        int operand1 = pop(&operandStack);
        switch (op) {
        case '+':
            push(&operandStack, operand1 + operand2);
            break;
        case '-':
            push(&operandStack, operand1 - operand2);
            break;
        case '*':
            push(&operandStack, operand1 * operand2);
            break;
        case '/':
            if (operand2 == 0) {
                printf("除以0错误.\n");
                exit(1);
            }
            push(&operandStack, operand1 / operand2);
            break;
        }
    }

    return top(&operandStack);
}
// 打印栈的内容
void printStack() {
    // 操作数栈
    printf("操作数栈:");
    for (int i = 0; i <= operandStack.top; i++) {
        printf("%d ", operandStack.items[i]);
    }
    printf("\n");
    // 操作符栈
    printf("操作符栈:");
    for (int i = 0; i <= operatorStack.top; i++) {
        printf("%c ", operatorStack.items[i]);
    }
    printf("\n");
}
int main() {
    printf("请输入表达式（以#号结束）:\n");
    if (fgets(expression, sizeof(expression), stdin) != NULL) {
        // 调用表达式求值函数,并打印结果
        int result = evaluateExpression(expression);
        printf("结果: %d\n", result);
    } else {
        printf("无法读取输入.\n");
    }
    return 0;
}