#include <stdio.h>
#include <stdlib.h>
#define N 3
// 函数用于交换两个行
void swapRows(int matrix[N][N], int row1, int row2) {
    for (int i = 0; i < N; i++) {
        int temp = matrix[row1][i];
        matrix[row1][i] = matrix[row2][i];
        matrix[row2][i] = temp;
    }
}

// 函数用于将矩阵变为单位矩阵
void makeIdentity(int matrix[N][N], int identity[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            identity[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
}

// 函数用于执行高斯-约当消元法求逆
int inverseMatrix(int matrix[N][N], int inverse[N][N]) {
    int i, j, k;
    int temp;

    // 创建单位矩阵
    int identity[N][N];
    makeIdentity(matrix, identity);

    for (i = 0; i < N; i++) {
        // 如果对角线元素为0，则交换行
        if (matrix[i][i] == 0.0) {
            int found = 0;
            for (j = i + 1; j < N; j++) {
                if (matrix[j][i] != 0.0) {
                    swapRows(matrix, i, j);
                    swapRows(identity, i, j);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                // 矩阵没有逆
                return 0;
            }
        }

        // 将对角线元素缩放为1
        temp = matrix[i][i];
        for (j = 0; j < N; j++) {
            matrix[i][j] /= temp;
            identity[i][j] /= temp;
        }

        // 将其他行的元素变为0
        for (j = 0; j < N; j++) {
            if (j != i) {
                temp = matrix[j][i];
                for (k = 0; k < N; k++) {
                    matrix[j][k] -= temp * matrix[i][k];
                    identity[j][k] -= temp * identity[i][k];
                }
            }
        }
    }

    // 将结果存储在逆矩阵中
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            inverse[i][j] = identity[i][j];
        }
    }

    return 1;
}
int main() {
    int matrix[N][N] = {
        {1, 2, 3},
        {0, 1, 4},
        {5, 6, 0}
    };

    int inverse[N][N];

    if (inverseMatrix(matrix, inverse)) {
        printf("Original Matrix:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }

        printf("\nInverse Matrix:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", inverse[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("Matrix is singular, no inverse exists.\n");
    }

    return 0;
}
