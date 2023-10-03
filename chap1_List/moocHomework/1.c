#include <stdio.h>
#define N 10
#define NULLL 0

int findElem(int *A,int K) {
    for(int i = 1; i <= N; i++){
        if(A[i] == K){
            return i;
        }
    }
    return 0;

}
int main() {
    int a[11] = {NULLL, 1, 3, 2, 4, 5, 3, 4, 5, 6, 7}; // 第一个值为空值
    int val = findElem(a,6);
    printf("查找的值的下标为:%d",val);
    return 0;
}