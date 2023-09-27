#include <stdio.h>
#include <stdlib.h>

// 定义节点
typedef struct node {
    int value;         // data
    struct node *next; // where the next node is
} Node, *LinkList;

// 初始化链表,带一个头结点
LinkList initList() {
    // 加一个头结点
    Node *head = malloc(sizeof(Node));
    if (head == NULL) {
        // 开辟失败
        fprintf(stderr, "initList() malloc fail\n");
        return NULL;
    }
    // 头结点初始化
    head->next = NULL;
    head->value = -1;
    return head;
}
// 采用尾插法添加值
int insert(int val, LinkList list) {
    if (list == NULL) {
        return -1;
    }
    // 找到链表的尾部
    LinkList p = list;
    while (p->next != NULL) {
        p = p->next;
    }
    // 创造新结点
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        // 开辟失败
        fprintf(stderr, "insert() malloc fail\n");
        return -1;
    }
    // 赋值
    newNode->value = val;
    newNode->next = NULL;

    p->next = newNode;
    return 0;
}
// 在 list 中删除值为 val 的结点
int delete (int val, LinkList list) {
    if (list == NULL) {
        return -1;
    }
    // 头结点
    LinkList p = list;

    while (p->next != NULL) {
        if (p->next->value == val) {
            LinkList del = p->next;
            // 删除
            p->next = p->next->next;
            // 内存回收
            free(del);
            // 继续删除
            p = list;
        } else {
            p = p->next;
        }
    }
    return 0;
}

// 反转链表,递归
LinkList reverseList(LinkList list) {
    if (list == NULL || list->next == NULL) {
        return list;
    }
    LinkList newHead = reverseList(list->next);
    list->next->next = list;
    list->next = NULL;
    return newHead;
}
// 打印链表,打印头结点
int printList(LinkList list) {
    if (list == NULL) {
        fprintf(stderr, "printList() fail\n");
        return -1;
    }
    LinkList p = list;
    while (p != NULL) {
        printf("%d ", p->value);
        p = p->next;
    }
    printf("\n");
    return 0;
}

// 测试:以下函数不能同时测试
int main() {

    LinkList testList = initList();
    int val[10] = {1, 1, 1, 2, 2, 3, 4, 5, 6, 4};
    for (int i = 0; i < 10; i++) {
        insert(val[i], testList);
    }
    // 打印
    printf("打印链表全部:");
    printList(testList);
    // 翻转链表
    // printf("翻转链表:");
    // testList = reverseList(testList);
    // printList(testList);

    // 删除 1
    delete (1, testList);
    printf("删除 1 后,打印链表全部:");
    printList(testList);

    // 删除 4
    delete (4, testList);
    printf("删除 4 后,打印链表全部:");
    printList(testList);

    return 0;
}