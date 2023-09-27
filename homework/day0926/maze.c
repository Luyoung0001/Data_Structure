#include "queue.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
// 创建迷宫
int size;   // 迷宫大小
int **maze; // 迷宫
// 方向
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

// 定义始末点
Point start = {1, 1}, end;

int **make_array(int rows, int cols) {
    // 堆区
    int **array = (int **)malloc(sizeof(int *) * rows);
    for (int i = 0; i < rows; i++) {
        array[i] = (int *)malloc(sizeof(int) * cols);
    }
    return array;
}
// 创建一个地图
void create_map() {
    printf("请输入迷宫大小:");
    scanf("%d", &size);
    maze = make_array(size + 2, size + 2);
    // 周围搞一圈数字“1”的墙
    for (int i = 0; i <= size + 1; i++) {
        maze[0][i] = maze[size + 1][i] = 1;
        maze[i][0] = maze[i][size + 1] = 1;
    }
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            if (1 == i && 1 == j)
                maze[i][j] = 0;
            else {
                switch (rand() % 8) {
                case 0:
                case 1:
                    maze[i][j] = 1;
                    break;
                default:
                    maze[i][j] = 0;
                    break;
                }
            }
        }
    }
}
// 打印迷宫
void printMaze() {
    printf("***************走迷宫**************\n");
    for (int i = 0; i < size + 2; i++) {
        for (int j = 0; j < size + 2; j++) {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }
}
// bfs走迷宫
bool breakMaze(Point start, Point end) {
    Queue que;
    initQueue(&que);
    // 进队
    enqueue(&que, start);
    // 当队列不为空的时候
    while (!isEmpty(&que)) {
        sleep(1);
        Point current = dequeue(&que);
        if (current.px == end.px && current.py == end.py) {
            return true; // 找到路径,直接结束
        }
        // 尝试四个方向
        for (int i = 0; i < 4; i++) {
            int newX = current.px + dx[i];
            int newY = current.py + dy[i];

            // 检查是否在迷宫范围内且未访问过
            if (newX >= 1 && newX < size + 2 && newY >= 1 && newY < size + 2 &&
                maze[newX][newY] == 0) {
                Point nextPoint = {newX, newY};
                enqueue(&que, nextPoint);
                maze[newX][newY] = 7; // 标记已访问过
                printMaze();
            }
        }
    }
    // 无解
    return false;
}

int main() {
    create_map();
    printMaze();
    end.px = size;
    end.py = size;
    if (breakMaze(start, end)) {
        printf("可达!\n");
    } else {
        printf("不可达!\n");
    }
    return 0;
}
