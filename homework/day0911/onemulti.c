#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    float coef; //系数
    int expn;   //指数
    struct node *next;
} Node;

// 加减法
Node *NodeAdd_Sub(Node *LA, Node *LB, char method) {
    // LA作为输出链
    Node *r, *s, *p, *q;
    int cmp;
    p = LA->next; //用于比较
    q = LB->next; //用于比较
    s = LA;       //用于记录p的前置
    r = LB;       //用于记录q的后置

    while (p != NULL && q != NULL) {
        if (p->expn < q->expn)
            cmp = -1; //当p指数小于q指数，p后移
        else if (p->expn > q->expn)
            cmp = 1; //当p指数大于q指数，q为p的前置，q后移
        else
            cmp = 0; // pq指数相同，进行加/减运算
        switch (cmp) {
        case -1: {
            s = p;
            p = p->next;
        }; break;

        case 0: {
            float x;
            if (method == '+') {
                x = p->coef + q->coef;

            } else if (method == '-') {
                x = p->coef - q->coef;
            }

            if ((int)x != 0) {
                p->coef = x;
                s = p;
                p = p->next;

                r->next = q->next;
                free(q);
                q = r->next;

            } else {
                //删除LA节点
                s->next = p->next;
                free(p);
                p = s->next;
                //删除LB节点
                r->next = q->next;
                free(q);
                q = r->next;
            }
        }; break;
        case 1: {
            r->next = q->next;
            q->next = s->next;
            s->next = q;
            s = q;
            q = r->next;
        }; break;
        }
    }
    //因为 前面的结束条件 p = null 所以 p的前置s位于链表的尾部，s连接q
    if (q != NULL) {

        s->next = q;
    }
    free(LB);
    return LA;
}
// 创建
void creatList(Node *LA, Node *LB) {
    LA->next = NULL;
    LB->next = NULL;
    Node *node;
    int choice;
    int i = 1;
    while (1) {
        printf("输入LA序列的第%d元素的系数+指数（格式：系数 指数）", i);
        node = (Node *)malloc(sizeof(Node));
        if (node == NULL) {
            exit(0);
        }

        scanf("%f %d", &node->coef, &node->expn);

        //不合法分析：1、系数为零 （√）2、指数重复（未解决）
        if (node->coef == 0) {
            continue;
        }

        node->next = LA->next;
        LA->next = node;

        i++;

        printf("继续?(1,0):");
        scanf("%d", &choice);
        if (choice == 0) {
            break;
        }
    }
    while (1) {
        printf("输入LB序列的第%d元素的系数+指数（格式：系数 指数）", i);
        node = (Node *)malloc(sizeof(Node));
        scanf("%f %d", &node->coef, &node->expn);
        node->next = LB->next;
        LB->next = node;

        i++;

        printf("继续?(1,0)");
        scanf("%d", &choice);
        if (choice == 0) {
            break;
        }
    }
}
void printList(Node *LA, Node *LB) {
    Node *circleLA, *circleLB;
    circleLA = LA;
    circleLB = LB;
    if (circleLB == NULL) {
        // 如果 B 为空,只打印A
        printf("LA:\n");
        while (circleLA->next != NULL) {
            circleLA = circleLA->next;
            printf("%.2f %d\n", circleLA->coef, circleLA->expn);
        }
    } else {
        // 否则打印 A,B
        printf("LA:\n");
        while (circleLA->next != NULL) {
            circleLA = circleLA->next;
            printf("%.2f %d\n", circleLA->coef, circleLA->expn);
        }
        printf("LB:\n");
        while (circleLB->next != NULL) {
            circleLB = circleLB->next;
            printf("%.2f %d\n", circleLB->coef, circleLB->expn);
        }
    }
}
// 按照指数升序排序
void Increasing(Node *LA, Node *LB) {
    Node *head, *end, *pre, *cur, *next, *temp;
    head = LA;
    end = NULL;

    //冒泡排序：将 最小/最大 的节点后移至当前的最后一位。
    while (head->next != end) {
        for (pre = head, cur = head->next, next = cur->next; next != end;
             pre = pre->next, cur = cur->next, next = next->next) {
            if (cur->expn > next->expn) {
                cur->next = next->next;
                pre->next = next;
                next->next = cur;
                temp = next;
                next = cur;
                cur = temp;
            }
        }
        end = cur;
    }
    head = LB;
    end = NULL;

    while (head->next != end) {
        for (pre = head, cur = head->next, next = cur->next; next != end;
             pre = pre->next, cur = cur->next, next = next->next) {
            if (cur->expn > next->expn) {
                cur->next = next->next;
                pre->next = next;
                next->next = cur;
                temp = next;
                next = cur;
                cur = temp;
            }
        }
        end = cur;
    }
}

// 求导
void Derivation(Node *LA, Node *LB) {

    Node *headLA, *headLB;
    headLA = LA;
    headLB = LB;

    while (headLA->next != NULL) {
        headLA = headLA->next;
        headLA->coef = headLA->coef * headLA->expn;
        if (headLA->expn != 0) {
            headLA->expn -= 1;
        } else {
            headLA->expn = 0;
        }
    }
    while (headLB->next != NULL) {
        headLB = headLB->next;
        headLB->coef = headLB->coef * headLB->expn;
        if (headLB->expn != 0) {
            headLB->expn -= 1;
        } else {
            headLB->expn = 0;
        }
    }
}

int main() {
    int choice;
    //创建附带头结点的链表
    Node *LA, *LB;
    LA = (Node *)malloc(sizeof(Node));
    LB = (Node *)malloc(sizeof(Node));
    creatList(LA, LB);

    // 按照指数升序
    Increasing(LA, LB);
    printf("升幂后的结果为:\n");
    printList(LA, LB);
    printf("输入选择(1:求导 2:运算):");
    scanf("%d", &choice);

    if (choice == 1) {
        //求导：将系数与指数相乘 然后指数减1
        Derivation(LA, LB);
        printf("求导后的结果为:\n");
        printList(LA, LB);

    } else if (choice == 2) {
        //运算(加减运算)
        char x;
        printf("运算:");
        scanf("\n");
        scanf("%c", &x);
        NodeAdd_Sub(LA, LB, x);
        printf("运算后\n");
        printList(LA, NULL);
    }
    return 0;
}
