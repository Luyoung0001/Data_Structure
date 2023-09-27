#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;

typedef struct node {
    ElemType num;
    char name[10];
    ElemType password;
    struct node *next;
} LNode;
typedef struct node *Linklist;

Linklist ListInit() {
    Linklist list;
    list = (Linklist)malloc(sizeof(LNode));
    return list;
}

void InsertList(int n, Linklist list) {
    printf("请在下面输入人的编号,姓名和密码,输入格式为:1 张三 4:\n");
    int i;
    Linklist p = list;
    for (i = 0; i < n; i++) {
        scanf("%d %s %d", &p->num, p->name, &p->password);
        p->next = (Linklist)malloc(sizeof(LNode));
        if (i == n - 1)
            p->next = list;
        else
            p = p->next;
    }
}

void PassGroup(Linklist list, int m, int n) {
    Linklist p = list;
    Linklist q;
    int i;
    // 指向第 m 个
    while (n != 0) {
        for (i = 1; i < m; i++) {
            q = p;
            p = p->next;
        }
        // 获取密码
        m = p->password;
        if (n > 1)
            printf("%d  %s\n", p->num, p->name);
        else if (n == 1)
            printf("%d  %s\n", p->num, p->name);
        q->next = p->next;
        p = p->next;
        n--;
    }
}

int main() {
    int n, m;
    printf("请输入人数:\n");
    scanf("%d", &n);
    if (n <= 0)
        return 0;
    Linklist list;
    list = ListInit();
    InsertList(n, list);
    printf("从第几个人开始报数:");
    scanf("%d", &m);
    if (m <= 0) {
        return 0;
    }
    printf("他们的出列顺序为:\n");
    printf("编号  姓名\n");
    PassGroup(list, m, n);
    return 0;
}