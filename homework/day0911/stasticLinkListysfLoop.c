#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef int ElemType;

typedef struct {
    ElemType num;
    char name[10];
    ElemType password;
    int next;
} LNode;

void ListInit(LNode list[], int n) {
    for (int i = 0; i < n - 1; i++) {
        list[i].next = i + 1;
    }
    list[n - 1].next = 0;
}

void InsertList(int n, LNode list[]) {
    printf("请在下面输入人的编号,姓名和密码,输入格式为: 1 张三 4:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %s %d", &list[i].num, list[i].name, &list[i].password);
    }
}

void PassGroup(LNode list[], int m, int n) {
    int current = 0;
    printf("出列的顺序为:\n");

    while (n != 0) {
        for (int i = 1; i < m-1; i++) {
            current = list[current].next;
        }

        int next = list[current].next;
        printf("%d %s\n", list[next].num, list[next].name);
        m = list[next].password;

        // 删除当前节点
        list[current].next = list[next].next;
        current = list[current].next;
        n--;
    }
}

int main() {
    int n, m;
    printf("请输入人数:\n");
    scanf("%d", &n);
    if (n <= 0 || n > MAXSIZE) {
        printf("人数不合法\n");
        return 0;
    }

    LNode list[MAXSIZE];
    ListInit(list, n);
    InsertList(n, list);

    printf("从第几个人开始报数:");
    scanf("%d", &m);

    if (m <= 0) {
        printf("报数起始位置不合法\n");
        return 0;
    }

    PassGroup(list, m, n);
    return 0;
}
