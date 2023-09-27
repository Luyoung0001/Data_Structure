#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int element;
    struct Node *next;
} Node, *Stack;

void initStack(Stack head) { head->next = NULL; }

int isEmpty(Stack head) { return head->next == NULL; }
char Compare(char a, char b) {
    if (a == '+') {
        if (b == '*' || b == '/' || b == '(')
            return '<';
        else
            return '>';
    } else if (a == '-') {
        if (b == '*' || b == '/' || b == '(')
            return '<';
        else
            return '>';
    } else if (a == '*') {
        if (b == '(')
            return '<';
        else
            return '>';
    } else if (a == '/') {
        if (b == '(')
            return '<';
        else
            return '>';
    } else if (a == '(') {
        if (b == ')')
            return '=';
        else if (b == '#')
            return '!';
        else
            return '<';
    } else if (a == ')') {
        if (b == '(')
            return '!';
        else
            return '>';

    } else if (a == '#') {
        if (b == ')')
            return '!';
        if (b == '#')
            return '=';
        else
            return '<';
    }
    return '0';
}

void pushNumStack(Stack head, int element) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    newNode->element = element;
    newNode->next = head->next;
    head->next = newNode;
    printf("数字栈压栈%d\n", element);
}
void pushCharStack(Stack head, int element) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    newNode->element = element;
    newNode->next = head->next;
    head->next = newNode;
    printf("操作符压栈%c\n", element);
}
int pop(Stack head) {
    if (isEmpty(head)) {
        printf("栈已空\n");
        exit(1);
    }
    Node *topNode = head->next;
    int element = topNode->element;
    head->next = topNode->next;
    free(topNode);
    // printf("出栈%d\n", element);
    return element;
}

int precedence(char operator) {
    if (operator== '+' || operator== '-') {
        return 1;
    } else if (operator== '*' || operator== '/') {
        return 2;
    }
    return 0; // 没有操作符
}

int performOperation(int operand1, char operator, int operand2) {
    switch (operator) {
    case '+':
        printf("%d + %d = %d\n", operand1, operand2, operand1 + operand2);
        return operand1 + operand2;
    case '-':
        printf("%d - %d = %d\n", operand1, operand2, operand1 - operand2);
        return operand1 - operand2;
    case '*':
        printf("%d * %d = %d\n", operand1, operand2, operand1 * operand2);
        return operand1 * operand2;
    case '/':
        if (operand2 != 0) {
            printf("%d / %d = %d\n", operand1, operand2, operand1 / operand2);
            return operand1 / operand2;
        } else {
            printf("除数不能为零\n");
            exit(1);
        }
    default:
        printf("无效的运算符\n");
        exit(1);
    }
}

void Exp(void) {
    Node numStack;
    Node opStack;
    char optr;

    initStack(&numStack);
    initStack(&opStack);

    pushCharStack(&opStack, '#');

    printf("请输入表达式（以#结尾）: ");
    char ch;
    ch = getchar();
    while (ch != '#' || opStack.next->element != '#') {
        printf("读入%c\n", ch);
        if (ch >= '0' && ch <= '9') {
            int x = ch - '0';
            ch = getchar();
            while (ch >= '0' && ch <= '9') {
                x = x * 10 + ch - '0';
                ch = getchar();
            }
            pushNumStack(&numStack, x);
        } else {
            switch (Compare(opStack.next->element, ch)) {
            case '<':
                pushCharStack(&opStack, ch);
                ch = getchar();
                break;
            case '=':
                pop(&opStack);
                ch = getchar();
                break;

            case '>':
                optr = pop(&opStack);
                int right = pop(&numStack);
                int left = pop(&numStack);
                pushNumStack(
                    &numStack,
                    performOperation(
                        left, optr,
                        right)); // 从num栈弹出两个运算数字，利用运算符栈顶元素进行计算
                break;

            default:
                break;
            }
        }
    }

    if (numStack.next != NULL) {
        printf("结果为：%d\n", numStack.next->element);
    } else {
        printf("表达式无效\n");
    }
}

int main(int argc, const char *argv[]) {
    Exp();
    return 0;
}
