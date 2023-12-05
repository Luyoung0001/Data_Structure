#include <stdio.h>
#include "net.h"
// #include "queue.h"
// #include "stack.h"
// 栈和队列
#define MAX_QUEUE_SIZE 100

typedef struct {
    int items[MAX_QUEUE_SIZE];
    int front, rear;
} Queue;

void initQueue(Queue *queue) {
    queue->front = -1;
    queue->rear = -1;
}

int isQEmpty(Queue *queue) {
    return (queue->front == -1 && queue->rear == -1);
}

void enqueue(Queue *queue, int value) {
    if ((queue->rear + 1) % MAX_QUEUE_SIZE == queue->front) {
        printf("Queue is full.\n");
        return;
    } else if (isQEmpty(queue)) {
        queue->front = 0;
        queue->rear = 0;
    } else {
        queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
    }
    queue->items[queue->rear] = value;
}

int dequeue(Queue *queue) {
    int value;

    if (isQEmpty(queue)) {
        printf("Queue is empty.\n");
        return -1;
    } else if (queue->front == queue->rear) {
        value = queue->items[queue->front];
        queue->front = -1;
        queue->rear = -1;
    } else {
        value = queue->items[queue->front];
        queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
    }

    return value;
}
//--------------------------------------------------------------------//
#define MAX_STACK_SIZE 100

typedef struct {
    int items[MAX_STACK_SIZE];
    int top;
} Stack;

void initStack(Stack *stack) {
    stack->top = -1;
}

int isSEmpty(Stack *stack) {
    return (stack->top == -1);
}

int isFull(Stack *stack) {
    return (stack->top == MAX_STACK_SIZE - 1);
}

void push(Stack *stack, int value) {
    if (isFull(stack)) {
        printf("Stack overflow.\n");
        return;
    }
    stack->items[++(stack->top)] = value;
}

int pop(Stack *stack) {
    if (isSEmpty(stack)) {
        printf("Stack underflow.\n");
        return -1;
    }
    return stack->items[(stack->top)--];
}

int peek(Stack *stack) {
    if (isSEmpty(stack)) {
        printf("Stack is empty.\n");
        return -1;
    }
    return stack->items[stack->top];
}

#define VERTICE_SIZE 5
HeadNode Graph[VERTICE_SIZE+1] = {0};
// 图初始化 添加图的值
void graphInit() {
    printf("请输入结点信息:\n");
    for (int i = 1; i <= VERTICE_SIZE; i++) {
        scanf(" %c", &Graph[i].value);
    }
}
// 图创建 添加图的拓扑信息(这个函数不专一,干的事情有点多了...)
void graphFinish() {
    printf("请输入结点拓扑信息:\n");
    for (int i = 1; i <= VERTICE_SIZE; i++) {
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
    for (int i = 1; i <= VERTICE_SIZE; i++) {
        // 打印节点
        printf("%c: ", Graph[i].value);
        // 打印后面的值
        traverseList(Graph[i].listHead);
        printf("\n");
    }
}

// 遍历图: 从哪一个结点开始遍历
// bfs
// Breadth-First Search (BFS) using adjacency list
void bfs(int start) {
    int visited[VERTICE_SIZE+1] = {0};
    Queue queue;
    initQueue(&queue);

    printf("%c ", Graph[start].value);
    visited[start] = 1;
    enqueue(&queue, start);

    while (!isQEmpty(&queue)) {
        int current = dequeue(&queue);
        Node *temp = Graph[current].listHead;
        while (temp != NULL) {
            int index = temp->index;
            if (!visited[index]) {
                printf("%c ", Graph[index].value);
                visited[index] = 1;
                enqueue(&queue, index);
            }
            temp = temp->next;
        }
    }
}


// dfs
// Depth-First Search (DFS) using adjacency list
void dfs(int start) {
    static int visited[VERTICE_SIZE] = {0};
    printf("%c ", Graph[start].value);
    visited[start] = 1;

    Node *current = Graph[start].listHead;
    while (current != NULL) {
        int index = current->index;
        if (!visited[index]) {
            dfs(index);
        }
        current = current->next;
    }
}

// 计算入度和出度
void calculateDegrees(HeadNode Graph[], int inDegree[], int outDegree[]) {
    // 初始化入度和出度数组
    for (int i = 1; i <= VERTICE_SIZE; i++) {
        inDegree[i] = 0;
        outDegree[i] = 0;
    }

    // 遍历每个结点
    for (int i = 1; i <= VERTICE_SIZE; i++) {
        Node *current = Graph[i].listHead;

        // 计算出度
        while (current != NULL) {
            outDegree[i]++;
            current = current->next;
        }

        // 计算入度
        for (int j = 1; j <= VERTICE_SIZE; j++) {
            current = Graph[j].listHead;
            while (current != NULL) {
                if (current->index == i) {
                    inDegree[i]++;
                    break;
                }
                current = current->next;
            }
        }
    }
}
int main() {
    graphInit();
    graphFinish();
    printGraph();
    printf("dfs:\n");

    dfs(1);
    printf("\nbfs:\n");
    bfs(1);
    // 初始化入度和出度数组
    int inDegree[VERTICE_SIZE+1], outDegree[VERTICE_SIZE+1];
    calculateDegrees(Graph, inDegree, outDegree);

    // 打印入度和出度
    printf("\n节点   入度   出度   度\n");
    for (int i = 1; i <= VERTICE_SIZE; i++) {
        printf("%c      %d      %d      %d\n", Graph[i].value, inDegree[i], outDegree[i],inDegree[i]+outDegree[i]);
    }
    // free 堆区
    return 0;
}