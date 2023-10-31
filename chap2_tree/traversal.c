#include "queue.h"
#include "stack.h"
// 访问
void visit(TreeNode *node) { printf("%d ", node->data); }
/********************************递归遍历**********************************/
// 先序遍历
void preOrder(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    visit(root);
    preOrder(root->left);
    preOrder(root->right);
}

// 中序遍历
void inOrder(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    inOrder(root->left);
    visit(root);
    inOrder(root->right);
}
// 后序遍历
void postOrder(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    visit(root);
}
/********************************非递归遍历**********************************/
// 这里就需要一些特殊的数据结构了,比如非递归的dfs等,就需要用到栈
// 层次遍历比如 bfs,就需要用到队列

// 利用队列的 bfs
void bfs(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    // 借助队列进行 bfs
    Queue q;
    initQueue(&q);
    // 将根节点入队
    enQueue(&q, root);
    while (!isQueueEmpty(&q)) {
        TreeNode *currentNode = deQueue(&q);
        visit(currentNode);
        if (currentNode->left != NULL) {
            enQueue(&q, currentNode->left);
        }
        if (currentNode->right != NULL) {
            enQueue(&q, currentNode->right);
        }
    }
}
// 利用栈的 dfs

// 非递归先序遍历二叉树
void dfsPreOrder(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    Stack stack;
    initStack(&stack);
    push(&stack, root); // 根节点进栈

    while (!isStackEmpty(&stack)) {
        TreeNode *current = pop(&stack);
        visit(current);
        if (current->right != NULL) {
            push(&stack, current->right);
        }
        if (current->left != NULL) {
            push(&stack, current->left);
        }
    }
}

// 非递归中序遍历
void dfsInOrder(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    Stack stack;
    initStack(&stack);

    TreeNode *current = root;

    while (!isStackEmpty(&stack) || current != NULL) {
        // 退出条件为栈空,或者 current 为空
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }
        // 左孩子为空,父节点退出栈
        current = pop(&stack);
        visit(current);
        // 遍历右子树
        current = current->right;
    }
}
// 非递归后序遍历
void dfsPostOrder(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    Stack stack;
    initStack(&stack);
    TreeNode *current = root;
    TreeNode *lastVisited = NULL;
    while (current != NULL || !isStackEmpty(&stack)) {
        if (current != NULL) {
            push(&stack, current);
            current = current->left;
        } else {
            TreeNode *peekNode = peek(&stack);
            if (peekNode->right && lastVisited != peekNode->right) {
                current = peekNode->right;
            } else {
                visit(peekNode);
                lastVisited = pop(&stack);
            }
        }
    }
}

int main() {
    // 构建二叉树
    TreeNode *root = NULL;
    root = insert(root, 5);
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 2);
    root = insert(root, 4);
    root = insert(root, 6);
    root = insert(root, 8);
    root = insert(root, 9);
    root = insert(root, 1);
    root = insert(root, 10);
    root = insert(root, 12);
    root = insert(root, 14);
    root = insert(root, 16);
    root = insert(root, 18);
    root = insert(root, 19);
    root = insert(root, 11);
    root = insert(root, 13);
    root = insert(root, 17);
    root = insert(root, 15);
    printf("递归先序遍历:\n");
    preOrder(root);
    printf("\n递归中序遍历:\n");
    inOrder(root);
    printf("\n递归后序遍历:\n");
    postOrder(root);
    printf("\n非递归层次遍历:\n");
    bfs(root);
    printf("\n非递归先序遍历:\n");
    dfsPreOrder(root);
    printf("\n非递归中序遍历:\n");
    dfsInOrder(root);
    printf("\n非递归后序遍历:\n");
    dfsPostOrder(root);

    return 0;
}