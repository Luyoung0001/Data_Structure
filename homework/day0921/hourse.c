#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ROWS 8
#define COLS 8
#define BOARD_SIZE 8

// 树结点的定义
typedef struct treeNode {
    int Board[ROWS][COLS];
    struct treeNode *children[8];
    struct treeNode *father;
    int steps;
    int px, py; // 方便查找,直接标记格局中最后的落点
} TreeNode;

// 格局树
TreeNode *TREE = NULL;
// 初始化树
void initTree(int x, int y) {
    TREE = malloc(sizeof(TreeNode));
    if (TREE == NULL) {
        perror("无法分配内存");
        exit(EXIT_FAILURE);
    }
    // 格局初始化
    memset(TREE->Board, 0, sizeof(TREE->Board));
    TREE->Board[x][y] = 1;
    TREE->px = x;
    TREE->py = y;
    TREE->steps = 1;
}
// 从父节点继承格局
void copyBoard(int p[ROWS][COLS], int s[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            s[i][j] = p[i][j];
        }
    }
}

// 设置移动方向
int dx[] = {1, 1, -1, -1, 2, 2, -2, -2};
int dy[] = {2, -2, 2, -2, 1, -1, 1, -1};

// 打印棋盘
void printBoard(TreeNode *node) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%2d ", node->Board[i][j]);
        }
        printf("\n");
    }
    printf("******************************\n");
}
// 判断是否在棋盘内部
int isInBoard(int x, int y) {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE ? 1 : 0;
}

// dfs
void buildSons(TreeNode *tree) {
    if (tree->steps == 64) {
        return;
    }
    sleep(1);
    // 创建 8 个子树
    for (int i = 0; i < 8; i++) {
        // 当前节点
        int px = tree->px + dx[i];
        int py = tree->py + dy[i];
        // 如果在界内且空白
        if (isInBoard(px, py) && tree->Board[px][py] == 0) {
            // 创建节点
            tree->children[i] = malloc(sizeof(TreeNode));
            memset(tree->children[i]->Board,0,sizeof(tree->children[i]->Board));
            // 赋值
            copyBoard(tree->Board, tree->children[i]->Board);
            tree->children[i]->steps = tree->steps + 1;
            tree->children[i]->Board[px][py] = tree->steps + 1;
            tree->children[i]->px = px;
            tree->children[i]->py = py;
            tree->children[i]->father = tree;
            printBoard(tree->children[i]);
            // 递归创建
            buildSons(tree->children[i]);
        } else {
            tree->children[i] = NULL;
        }
    }
}
int main() {
    initTree(4, 4);
    buildSons(TREE);
    return 0;
}