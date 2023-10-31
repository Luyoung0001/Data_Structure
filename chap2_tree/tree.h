#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdlib.h>

// #define ElemType int
#define ElemType TreeNode
// 定义二叉树节点结构
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;
// 创建二叉树结点
TreeNode *createNode(int data) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
// 插入节点,并保持一个有序二叉树

TreeNode *insert(TreeNode *root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data <= root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}
#endif // TREE_H