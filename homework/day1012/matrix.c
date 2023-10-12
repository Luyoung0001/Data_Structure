#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 20

// 三元组结构体
typedef struct {
    int i, j, value;
} Triad;

int rowA, rowB; // 行数
int colA, colB; // 列数
// 创建全局三元组矩阵 A,B,并初始化
Triad A[MAXSIZE * MAXSIZE] = {0};
Triad B[MAXSIZE * MAXSIZE] = {0};

// 矩阵具体形式
int **MA, **MB;
// 将三元组表示成矩阵,为了打印方便
int **transMatrix(Triad *A, int sizeA) {
    int **matrixA = (int **)malloc(rowA * sizeof(int *));
    for (int i = 0; i < rowA; i++) {
        matrixA[i] = (int *)malloc(colA * sizeof(int));
    }
    // 初始化
    for (int i = 0; i < rowA; i++) {
        for (int j = 0; j < colA; j++) {
            matrixA[i][j] = 0;
        }
    }
    // 转化
    for (int index = 0; index < sizeA; index++) {
        matrixA[A[index].i][A[index].j] = A[index].value;
    }
    return matrixA;
}
// 创建矩阵,返回非零元素的个数
int makeMatrix(Triad *A) {
    char tag = '0';
    int index = 0;
    printf("请按照这个格式输入三元组:'行 列 值',输入's'表示矩阵输入完成\n");
    Triad temp;
    while (scanf("%c", &tag) != 0 && tag != 's') {
        scanf("%d %d %d", &A[index].i, &A[index].j, &A[index].value);
        scanf("\n");
        index++;
    }
    return index;
}
// 运算,每次运算完都在函数内部实现操作结果的打印!
// 加法
void addMatrix(Triad *A, int sizeA, Triad *B, int sizeB) {
    // 转化
    MA = transMatrix(A, sizeA);
    MB = transMatrix(B, sizeB);
    // 计算,放到 A 里
    for (int p = 0; p < rowA; p++) {
        for (int q = 0; q < colA; q++) {
            MA[p][q] = MA[p][q] + MB[p][q];
        }
    }
    // 打印
    printf("两个矩阵加法的结果为:\n");
    for (int p = 0; p < rowA; p++) {
        for (int q = 0; q < colA; q++) {
            printf("%d ", MA[p][q]);
        }
        printf("\n");
    }
}

// 减法
void subMatrix(Triad *A, int sizeA, Triad *B, int sizeB) {
    // 转化
    MA = transMatrix(A, sizeA);
    MB = transMatrix(B, sizeB);
    // 计算,放到 A 里
    for (int p = 0; p < rowA; p++) {
        for (int q = 0; q < colA; q++) {
            MA[p][q] = MA[p][q] - MB[p][q];
        }
    }
    // 打印
    printf("两个矩阵减法的结果为:\n");
    for (int p = 0; p < rowA; p++) {
        for (int q = 0; q < colA; q++) {
            printf("%d ", MA[p][q]);
        }
        printf("\n");
    }
}
// 乘法,乘法必须有三元组实现
void multiMatrix(Triad *A, int sizeA, Triad *B, int sizeB) {}
// 求逆,求逆如果用三元组来表示将会非常复杂,因此这里依然使用矩阵来计算
void reverseMatrix(Triad *A, int sizeA) {}

int main() {
    char calClass; // 计算的类型
    printf("你是否要求逆运算?,如果是请输入'r',否则请输入其它:\n");
    scanf("%c", &calClass);
    if (calClass == 'r') {
        int sizeA = makeMatrix(A);
        reverseMatrix(A, sizeA);
        return 0;
    }
    // 输入列数和行数
    // scanf("\n");
    printf("请输入矩阵A的行数和列数:\n");
    scanf("%d %d", &rowA, &colA);
    printf("请输入矩阵B的行数和列数:\n");
    scanf("%d %d", &rowB, &colB);
    // 大小是否合法
    if (rowA > MAXSIZE || rowB > MAXSIZE || colA > MAXSIZE || colB > MAXSIZE) {
        printf("你输入的矩阵太大,程序退出!\n");
        return 0;
    }

    // 输入运算类型
    printf("请输入你要进行计算的类型:");
    printf("加法请输入'+',减法输入'-',乘法输入'*':");
    scanf("\n");
    scanf("%c", &calClass);
    // 查看是否能计算
    switch (calClass) {
    case '+':
        if (rowA != rowB || colA != colB) {
            printf("加法类型不匹配,程序将退出!\n");
            return 0;
        }
        // 构造三元组
        printf("请输入矩阵 A 的三元组:\n");
        int sizeOfA = makeMatrix(A);
        printf("请输入矩阵 B 的三元组:\n");
        int sizeOfB = makeMatrix(B);

        // 进入计算流程
        addMatrix(A, sizeOfA, B, sizeOfB);
        break;
    case '-':
        if (rowA != rowB || colA != colB) {
            printf("加法类型不匹配,程序将退出!\n");
            return 0;
        }
        // 构造三元组
        printf("请输入矩阵 A 的三元组:\n");
        sizeOfA = makeMatrix(A);
        printf("请输入矩阵 B 的三元组:\n");
        sizeOfB = makeMatrix(B);

        // 进入计算流程
        subMatrix(A, sizeOfA, B, sizeOfB);
        break;
    case '*':
        if (rowA != colB || rowB != colB) {
            printf("加法类型不匹配,程序将退出!\n");
            return 0;
        }
        // 构造三元组
        // 进入计算流程
        break;

    default:
        printf("你的输入有误,请你输入正确的运算符,程序将退出,请你重新输入!\n");
        break;
    }

    return 0;
}