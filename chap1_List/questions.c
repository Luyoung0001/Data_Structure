#include <stdio.h>
#include <stdlib.h>
#define INITNUM 999

// 定义节点
typedef struct node {
    int value;         // data
    struct node *next; // where the next node is
} Node, *LinkList;

// 声明
int lenOfList(LinkList list);

// 初始化循环单链表,带一个结点
LinkList initList() {
    // 加一个头结点
    Node *head = malloc(sizeof(Node));
    if (head == NULL) {
        // 开辟失败
        fprintf(stderr, "initList() malloc fail\n");
        return NULL;
    }
    // 头结点初始化
    head->next = head;
    head->value = INITNUM;
    return head;
}

// 采用添加值
int insert(int val, LinkList list) {
    // 如果长度为 1,则直接赋值
    int len = lenOfList(list);
    if (list->value == INITNUM) {
        list->value = val;
        return 1;
    }
    if(len == 1){
      return 1;
    }

    // 找到链表的尾部
    int index = 1;
    LinkList p = list;
    while (index != len-1) {
        index++;
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
    newNode->next = list;
    p->next = newNode;
    return 0;
}

int lenOfList(LinkList list) {
    LinkList p = list->next;
    int len = 1;
    while (p != list) {
        len++;
        p = p->next;
    }
    return len;
}
// 删除 s 所指的前驱结点
int deleteP(LinkList s) {
    int len = lenOfList(s);
    // 如果长度为 2
    if (len == 2) {
        LinkList del = s->next;
        s->next = s;
        free(del);
    }
    // 找到前驱结点的前驱结点
    int index = 0;
    LinkList p = s;
    while (index != len - 2) {
        index++;
        p = p->next;
    }
    LinkList del = p->next;
    p->next = p->next->next;
    free(del);
    return 0;
}
// 打印节点
int printList(LinkList list) {
    int len = lenOfList(list);
    if (list == NULL) {
        fprintf(stderr, "printList() fail\n");
        return -1;
    }
    int index = 0;
    while (index != len) {
        printf("%d ", list->value);
        list = list->next;
        index++;
    }
    printf("\n");
    return 0;
}
int main() {
    LinkList listHead = initList();
    int val[10] = {1, 1, 1, 2, 2, 3, 4, 5, 6, 4};
    for (int i = 0; i < 10; i++) {
      printList(listHead);
        insert(val[i], listHead);
    }
    printList(listHead);
    deleteP(listHead);
    printList(listHead);

    return 0;
}