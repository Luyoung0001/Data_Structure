#include "net.h"
#include <stdio.h>
#define VERTICE_SIZE 5
HeadNode Graph[VERTICE_SIZE] = {0};
// 图初始化 添加图的值
void graphInit() {
    printf("请输入结点信息:\n");
    for (int i = 0; i < VERTICE_SIZE; i++) {
        scanf(" %c", &Graph[i].value);
    }
}
// 图创建 添加图的拓扑信息(这个函数不专一,干的事情有点多了...)
void graphFinish() {
    printf("请输入结点拓扑信息:\n");
    for (int i = 0; i < VERTICE_SIZE; i++) {
        // 建立链表,尾插法(带头结点)并初始化
        Node *head = malloc(sizeof(Node));
        head->index = 0;
        head->next = NULL;

        // 创建第一个结点
        int index = 0;
        printf("请输入该结点的第一个邻接结点的索引,如果该结点没有邻接结点,请输入 666:");
        scanf(" %d", &index);
        if (index == 666) {
            Graph[i].listHead = head->next;
            continue;
        }

        Node *newNode = createNode(index);
        Node *p = newNode;
        head->next = newNode; // 插上
        // 尾插
        while (1) {
            printf("请继续输入该结点的下一个邻接结点的索引,如果该结点没有更多邻接结点,请输入 666:");
            scanf(" %d", &index);
            if (index == 666) {
                // 跳出,进入大循环
                break;
            }
            Node *nextNode = createNode(index);
            p->next = nextNode;
            p = p->next;
        }
        // 将该链表插入图中
        Graph[i].listHead = head->next;
    }
}
// 链表遍历
void traverseList(Node *list) {
    Node *p = list;
    while (p != NULL) {
        printf("%d  ", p->index);
        p = p->next;
    }
}

// 验证打印,查看邻接表建立情况
void printGraph() {
    for (int i = 0; i < VERTICE_SIZE; i++) {
        // 打印节点
        printf("%c: ", Graph[i].value);
        // 打印后面的值
        traverseList(Graph[i].listHead);
        printf("\n");
    }
}
// 根据一个结点找出它的索引
int findIndex(HeadNode *headnode){
    for(int i = 0; i < VERTICE_SIZE; i++){
        if(Graph[i].value == headnode->value){
            return i;
        }
    }
}
// 遍历数组
int visited[VERTICE_SIZE] = {0};
// 根据索引,来标记它已经被访问过
void visit(int index){
    visited[findIndex(index)] = 1;
}

// 遍历图: 从哪一个结点开始遍历
// bfs
void bfs(char s_vertex){
    // 找到访问索引
    int startIndex = findIndex(s_vertex);
    // 根据索引进行 bfs
    // ...

}

// dfs
void dfs(char s_vertex){
    // 找到访问索引
    int startIndex = findIndex(s_vertex);
    // 根据索引进行 dfs
    // ...

}
// 结点的下一个邻接结点
// int nextIndexOfVertex(char vertex) {}















int main() {
    graphInit();
    graphFinish();
    printGraph();
    return 0;
}