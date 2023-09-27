#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 设置移动方向
const int dx[8] = {-2, 2, -2, -1, -1, 1, 1, 2};
const int dy[8] = {-1, 1, 1, -2, 2, -2, 2, -1};

const int p[8][8] = {{2, 3, 4, 4, 4, 4, 3, 2},
                     {3, 4, 6, 6, 6, 6, 4, 3},
                     {4, 6, 8, 8, 8, 8, 6, 4},
                     {4, 6, 8, 8, 8, 8, 6, 4},
                     {4, 6, 8, 8, 8, 8, 6, 4},
                     {4, 6, 8, 8, 8, 8, 6, 4},
                     {3, 4, 6, 6, 6, 6, 4, 3},
                     {2, 3, 4, 4, 4, 4, 3, 2}};

int w[8][8];
// 初始化 w
void initW() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            w[i][j] = p[i][j];
        }
    }
}
// 存放答案
int ans[8][8];

int legal(int a) {
    if (a >= 0 && a < 8)
        return 1;
    return 0;
}

void hourse(int a0, int b0) {
    int i, j, min, a, b, a_min, b_min;
    // 贪心
    for (i = 1; i <= 64; i++) {
        ans[a0][b0] = i;
        min = 8;
        // 找下一步落点, 且这一步周围的所有可移动点的权值减一
        for (j = 0; j < 8; j++) {
            a = a0 + dx[j], b = b0 + dy[j];
            if (legal(a) && legal(b) && !ans[a][b] && --w[a][b] < min) { // 减一
                min = w[a][b];
                a_min = a, b_min = b;
            }
        }
        a0 = a_min, b0 = b_min;
    }
    // 打印答案
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++)
            printf("%3d", ans[i][j]);
        printf("\n");
    }
    printf("**************下一个情况**************\n");
}
// 验证一个 ans
int validate() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (ans[i][j] == 0) {
                return 1;
            }
        }
    }
    return 0;
}
// 贪心验证所有的初始点
int validateAll() {
    int tag = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // 初始化
            memset(ans, 0, sizeof(ans));
            initW();
            hourse(i, j);
            // 验证ans
            if (validate()) {
                tag = 1;
            }
        }
    }
    return tag;
}
int main() {
    // 计时器
    time_t time_start, time_end;

    time_start = clock();
    int tag = validateAll();
    time_end = clock();
    double execution_time = (double)(time_end - time_start);

    // 打印执行时间
    printf("程序执行时间: %.6f 微秒\n", execution_time);
    if (tag == 0) {
        printf("所有起始点坐标都可以不用回溯得到解!\n");
    } else {
        printf("部分起始点坐标都必须用回溯得到解!\n");
    }
    return 0;
}