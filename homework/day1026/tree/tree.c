#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 1024
typedef char TElemType;
// 二叉链表结点定义
typedef struct node {
    char data;
    struct node *left;
    struct node *right;
} Node, *BiTree, BiTNode;

// 创建新结点
Node *createNode(char value) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 先序扩展序列递归建树
BiTree PreCreateBiTree(BiTree *BT) {
    TElemType ch;
    scanf("%c", &ch);

    if (ch == '#') {
        *BT = NULL;
        return *BT;
    } else {
        *BT = malloc(sizeof(BiTNode));
        (*BT)->data = ch;
        (*BT)->left = PreCreateBiTree(&((*BT)->left));
        (*BT)->right = PreCreateBiTree(&((*BT)->right));
    }
    return *BT;
}

// 先序遍历打印二叉树
void preorderTraversal(Node *root) {
    if (root == NULL) {
        return;
    }
    printf("%c ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}
// 中序遍历打印二叉树
void inorderTraversal(Node *root) {
    if (root == NULL) {
        return;
    }

    inorderTraversal(root->left);
    printf("%c ", root->data);
    inorderTraversal(root->right);
}

// 后序遍历打印二叉树
void postorderTraversal(Node *root) {
    if (root == NULL) {
        return;
    }

    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%c ", root->data);
}

// 非递归先序遍历
void nonRecursivePreorder(Node *root) {
    if (root == NULL) {
        return;
    }

    // 创建一个栈来辅助遍历
    Node *stack[100];  // 假设最多有100个节点
    int top = -1;  // 栈顶指针

    // 将根节点入栈
    stack[++top] = root;

    while (top >= 0) {
        // 弹出栈顶节点
        Node *current = stack[top--];

        // 访问当前节点
        printf("%c ", current->data);

        // 先将右子节点入栈，再将左子节点入栈
        if (current->right != NULL) {
            stack[++top] = current->right;
        }
        if (current->left != NULL) {
            stack[++top] = current->left;
        }
    }
}

// 非递归中序遍历
void nonRecursiveInorder(Node *root) {
    if (root == NULL) {
        return;
    }

    // 创建一个栈来辅助遍历
    Node *stack[100];  // 假设最多有100个节点
    int top = -1;  // 栈顶指针
    Node *current = root;

    while (top >= 0 || current != NULL) {
        // 将当前节点及其所有左子节点入栈
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }

        // 弹出栈顶节点，访问它，然后转向右子树
        current = stack[top--];
        printf("%c ", current->data);
        current = current->right;
    }
}

// 统计叶子节点数量的函数
int countLeaves(Node *root) {
    if (root == NULL) {
        return 0; // 空树没有叶子节点
    } else if (root->left == NULL && root->right == NULL) {
        return 1; // 只有一个节点的树是叶子节点
    } else {
        int leftLeaves = countLeaves(root->left);
        int rightLeaves = countLeaves(root->right);
        return leftLeaves + rightLeaves;
    }
}

int main() {
    BiTree root;
    root = PreCreateBiTree(&root);
    // 统计叶子结点个数
    int num = countLeaves(root);
    printf("\n叶子结点有%d个\n", num);

    // 统计树的高度

    // 三种递归遍历方式
    printf("\n先序递归遍历:\n");
    preorderTraversal(root);
    printf("\n中序递归遍历:\n");
    inorderTraversal(root);
    printf("\n后序递归序遍历:\n");
    postorderTraversal(root);
    // 两种非递归遍历
    printf("\n先序非递归遍历:\n");
    nonRecursivePreorder(root);
    printf("\n中序非递归遍历:\n");
    nonRecursiveInorder(root);

    return 0;
}
