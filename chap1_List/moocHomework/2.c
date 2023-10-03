#include <stdio.h>
#define N 10
#define NULLL 0
// 最大的数值
void findValues(int *A) {
    int max = 0, mid = 0;
    for (int i = 1; i <= N; i++) {
        if (A[i] > max) {
            mid = max;
            max = A[i];
        } else if (A[i] > mid) {
            mid = A[i];
        }
    }
    printf("最大值为:%d\n次大值为:%d\n",max,mid);
}
int main() {
    int a[11] = {NULLL, 1, 3, 2, 4, 5, 3, 4, 5, 6, 7}; // 第一个值为空值
    findValues(a);

    return 0;
}