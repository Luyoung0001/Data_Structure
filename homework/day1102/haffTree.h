#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdlib.h>

#define ElemType HaffTree
// 定义二叉树节点结构
typedef struct HaffTree {
    char data;
    int fre;
    struct HaffTree *left;
    struct HaffTree *right;
} HaffTree;
// 创建二叉树结点
ElemType *createNode(int data, int fre) {
    ElemType *newNode = (ElemType *)malloc(sizeof(ElemType));
    newNode->data = data;
    newNode->fre = fre;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
// 插入节点,并保持一个有序二叉树
// 这里将在 heap.h 中实现
// TreeNode *insert(TreeNode *root, int data) {
//     if (root == NULL) {
//         return createNode(data);
//     }
//     if (data <= root->data) {
//         root->left = insert(root->left, data);
//     } else {
//         root->right = insert(root->right, data);
//     }
//     return root;
// }
#endif // TREE_H