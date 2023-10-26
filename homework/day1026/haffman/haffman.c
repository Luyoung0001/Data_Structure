#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 1024

// 字符类型的种类
int count = 0;
// 结点结构
typedef struct Node {
    char data;          // 字符
    int freq;           // 频率
    struct Node *left;  // 左子节点
    struct Node *right; // 右子节点
} Node;

// 创建新结点
Node *createNode(char data, int freq) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->freq = freq;
    newNode->left = newNode->right = NULL;
    return newNode;
}
// 字节频度数组
int Array[256] = {0};
// 获取字节频度数组,返回字节种类的数目
int getArray(char *fileName) {
    FILE *file = fopen(fileName, "rb"); // "rb" 表示以二进制读取模式打开文件

    if (file == NULL) {
        // 打开失败
        perror("File open error");
        return -1;
    }

    unsigned char byte;
    while (fread(&byte, 1, 1, file) > 0) {
        // byte 变量中包含了读取的字节数据
        Array[byte]++;
    }
    // 关闭文件
    fclose(file);
    for (int i = 0; i < 256; i++) {
        if (Array[i] != 0) {
            count++;
        }
    }
    return count;
}
// Node 数组
Node **priorityQueue;

// 拿到结点数组
void getPriorityQueue() {
    int k = -1;
    priorityQueue = (Node **)malloc(count * sizeof(Node *));
    for (int i = 0; i <= 255; i++) {
        if (Array[i] != 0) {
            k++;
            priorityQueue[k] = createNode(i, Array[i]);
        }
    }
    printf("字节值---字节出现的频率\n");
    for (int i = 0; i < 256; i++) {
        printf("%d: %d\n", i, Array[i]);
    }
}

// 对priorityQueue[]进行排序,用冒泡法吧,简单一点
void sortPriorityQueue() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            // 如果相邻元素顺序不正确，交换它们
            if (priorityQueue[j]->freq > priorityQueue[j + 1]->freq) {
                Node *temp = priorityQueue[j];
                priorityQueue[j] = priorityQueue[j + 1];
                priorityQueue[j + 1] = temp;
            }
        }
    }
    // 测试打印
    for (int i = 0; i < count; i++) {
        printf("%d: %d\n", priorityQueue[i]->data, priorityQueue[i]->freq);
    }
}

// 优先队列结构
typedef struct PriorityQueue {
    Node **nodes;
    int size;
} PriorityQueue;

// 创建空的优先队列
PriorityQueue *createPriorityQueue(int capacity) {
    PriorityQueue *queue = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    queue->nodes = (Node **)malloc(sizeof(Node *) * capacity);
    queue->size = 0;
    return queue;
}

// 插入结点到优先队列
void insert(PriorityQueue *queue, Node *node) {
    int i = queue->size;
    while (i > 0 && node->freq < queue->nodes[(i - 1) / 2]->freq) {
        queue->nodes[i] = queue->nodes[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    queue->nodes[i] = node;
    queue->size++;
}

// 弹出队列中最小频率的结点
Node *pop(PriorityQueue *queue) {
    if (queue->size <= 0) {
        return NULL;
    }
    Node *minNode = queue->nodes[0];
    queue->size--;

    Node *lastNode = queue->nodes[queue->size];
    int i = 0;
    while (i * 2 + 1 < queue->size) {
        int child = i * 2 + 1;
        if (child + 1 < queue->size &&
            queue->nodes[child + 1]->freq < queue->nodes[child]->freq) {
            child++;
        }
        if (lastNode->freq <= queue->nodes[child]->freq) {
            break;
        }
        queue->nodes[i] = queue->nodes[child];
        i = child;
    }
    queue->nodes[i] = lastNode;

    return minNode;
}

// 构建哈夫曼树
Node *buildHuffmanTree(Node **nodes, int size) {
    if (size <= 0) {
        return NULL;
    }

    // 创建优先队列，并将初始节点插入队列
    PriorityQueue *queue = createPriorityQueue(size);
    for (int i = 0; i < size; i++) {
        insert(queue, nodes[i]);
    }

    // 构建哈夫曼树
    while (queue->size > 1) {
        Node *left = pop(queue);
        Node *right = pop(queue);
        Node *parent = createNode('$', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        insert(queue, parent);
    }

    Node *root = pop(queue);
    free(queue->nodes);
    free(queue);

    return root;
}
// 递归打印哈夫曼树
void printHuffmanTree(Node *root) {
    if (root == NULL) {
        return;
    }
    printf("%d - %d\n", root->data, root->freq);
    printHuffmanTree(root->left);
    printHuffmanTree(root->right);
}

// 构建哈夫曼编码

// 结构定义：用于存储叶子节点的哈夫曼编码
typedef struct {
    char data;      // 叶子节点的字符
    char code[256]; // 哈夫曼编码，假定不超过256位
} LeafNodeCode;

// 递归函数，生成每个叶子节点的哈夫曼编码并存储在 leafNodeCodes 数组中
void generateLeafNodeCodes(Node *node, char *currentCode,
                           LeafNodeCode *leafNodeCodes, int *index) {
    if (node == NULL) {
        return;
    }
    // 向左走，编码加0
    char leftCode[256];
    strcpy(leftCode, currentCode);
    strcat(leftCode, "0");
    generateLeafNodeCodes(node->left, leftCode, leafNodeCodes, index);

    // 向右走，编码加1
    char rightCode[256];
    strcpy(rightCode, currentCode);
    strcat(rightCode, "1");
    generateLeafNodeCodes(node->right, rightCode, leafNodeCodes, index);

    if (node->left == NULL && node->right == NULL) {
        // 找到叶子节点，记录编码
        leafNodeCodes[*index].data = node->data;
        strcpy(leafNodeCodes[*index].code, currentCode);
        (*index)++;
    }
}

// 获取每个叶子节点的哈夫曼编码
int numLeafNodes;
LeafNodeCode *getLeafNodeCodes(Node *root) {
    numLeafNodes = count;

    // 计算叶子节点数目
    // 在这里，你需要提前知道哈夫曼树的叶子节点数量

    // 分配 LeafNodeCode 数组
    LeafNodeCode *leafNodeCodes =
        (LeafNodeCode *)malloc(numLeafNodes * sizeof(LeafNodeCode));

    int index = 0;              // 用于跟踪叶子节点编码的索引
    char currentCode[256] = ""; // 初始编码为空

    // 生成叶子节点编码
    generateLeafNodeCodes(root, currentCode, leafNodeCodes, &index);

    return leafNodeCodes;
}
// 搜索编码
char *searchCode(LeafNodeCode *leafNodeCodes, char data) {
    for (int i = 0; i < count; i++) {
        if (leafNodeCodes[i].data == data) {
            return leafNodeCodes[i].code;
        }
    }
    return 0;
}
// 压缩
int targetFile(LeafNodeCode *leafNodeCodes, char *fileSourceName,
               char *fileTargetName) {
    FILE *fileSource = fopen(fileSourceName, "rb");
    FILE *fileTarget = fopen(fileTargetName, "w");
    if (fileSource == NULL || fileTarget == NULL) {
        // 打开失败
        perror("文件打开失败!");
        return -1;
    }

    int byte;
    while ((byte = fgetc(fileSource)) != EOF) {
        // byte 变量中包含了读取的字节数据
        fprintf(fileTarget, "%s", searchCode(leafNodeCodes, byte));
    }
    fclose(fileSource); // 关闭文件
    fclose(fileTarget); // 关闭文件
    return 0;
}
// 根据前缀码获取字符
char *searchPrecode(char *preCode, LeafNodeCode *LeafNodeCodes) {
    for (int i = 0; i < count; i++) {
        if (strcmp(preCode, LeafNodeCodes[i].code) == 0) {
            return &LeafNodeCodes[i].data;
        }
    }
    return NULL;
}
// 解密
void deCode(char *codeFileName, char *decodeFileName,
            LeafNodeCode *LeafNodeCodes) {
    // 打开加密文件
    FILE *inFile = fopen(codeFileName, "rb");
    FILE *outFile = fopen(decodeFileName, "wb");
    if (inFile == NULL || outFile == NULL) {
        // 打开失败
        perror("File open error");
        return;
    }
    // 存放临时 准前缀码
    char preCode[257];
    int byte;
    int tag = -1;
    char value;
    while (1) {
        memset(preCode, '\0', 257);
        int i = -1;
        while ((searchPrecode(preCode, LeafNodeCodes)) == NULL) {
            byte = fgetc(inFile);
            if (byte == EOF) {
                tag = 0;
                break;
            }
            preCode[++i] = byte;
            printf("准前缀码:%s\n", preCode);
        }
        if (tag == 0) {
            break;
        }
        value = *searchPrecode(preCode, LeafNodeCodes);
        printf("%c\n", value);
        // 将这个解密的数据写入文件

        if (fwrite(&value, 1, 1, outFile) <= 0) {
            printf("写入失败!\n");
        }
    }
    fclose(inFile);
    fclose(outFile);
}

int main(int argc, char *argv[]) {

    // bus error?
    // char argv1[MAXSIZE] = {0};
    // char argv2[MAXSIZE] = {0};
    // char argv3[MAXSIZE] = {0};
    // strcpy(argv1,argv[1]);
    // strcpy(argv2,argv[2]);
    // strcpy(argv3,argv[3]);
    if (argc < 4) {
        printf("use method: "
               "命令_被压缩文件_存放哈夫曼编码后的文本文件名_解码后的文件名\n");
        return -1;
    }

    if (getArray(argv[1]) == -1) {
        printf("文件不存在,打开失败!\n");
        return -1;
    }
    /**************对字节频率构建哈夫曼树***************/
    // 拿到队列
    getPriorityQueue();
    // 排序
    sortPriorityQueue();
    // 构建哈夫曼树
    Node *root = buildHuffmanTree(priorityQueue, count);
    // // 打印哈夫曼树
    // printHuffmanTree(root);
    // 获取每个叶子节点的哈夫曼编码
    LeafNodeCode *leafNodeCodes = getLeafNodeCodes(root);

    // 输出每个叶子节点的字符和编码
    for (int i = 0; i < count; i++) {
        printf("Character: %d, Huffman Code: %s\n", leafNodeCodes[i].data,
               leafNodeCodes[i].code);
    }
    // 构建压缩文件
    if (targetFile(leafNodeCodes, argv[1], argv[2]) == -1) {
        printf("压缩出错!\n");
        return -1;
    }
    // 解码
    deCode(argv[2], argv[3], leafNodeCodes);

    free(leafNodeCodes);
    free(root);
    return 0;
}
