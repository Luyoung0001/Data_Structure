#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 二叉树结点定义
typedef struct Node {
    char data;
    struct Node* left;
    struct Node* right;
} Node;

// 在中序序列中找到根节点的位置
int findRootIndex(char inorder[], int start, int end, char value) {
    for (int i = start; i <= end; i++) {
        if (inorder[i] == value) {
            return i;
        }
    }
    return -1;
}

// 根据先序序列和中序序列构建二叉树
Node* buildTree(char preorder[], char inorder[], int preStart, int preEnd, int inStart, int inEnd) {
    if (preStart > preEnd || inStart > inEnd) {
        return NULL;  // 递归结束条件
    }

    char rootValue = preorder[preStart];
    Node* root = malloc(sizeof(Node));
    root->data = rootValue;

    // 在中序序列中找到根节点的位置
    int rootIndex = findRootIndex(inorder, inStart, inEnd, rootValue);

    // 递归构建左子树和右子树
    root->left = buildTree(preorder, inorder, preStart + 1, preStart + (rootIndex - inStart), inStart, rootIndex - 1);
    root->right = buildTree(preorder, inorder, preStart + (rootIndex - inStart) + 1, preEnd, rootIndex + 1, inEnd);

    return root;
}

// 先序遍历打印二叉树
void postOrderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }

    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    printf("%c ", root->data);
}

int main() {
    char preorder[] = "ABCDEGF"; // 先序序列
    char inorder[] = "CBEGDFA";  // 中序序列

    int preLength = strlen(preorder);
    int inLength = strlen(inorder);

    if (preLength != inLength) {
        printf("无法构建二叉树，先序和中序序列长度不一致。\n");
        return 1;
    }

    Node* root = buildTree(preorder, inorder, 0, preLength - 1, 0, inLength - 1);

    printf("\n构建的二叉树的后序遍历结果: ");
    postOrderTraversal(root);
    printf("\n");

    return 0;
}
