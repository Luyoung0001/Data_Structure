#include <stdio.h>

typedef struct A {
    int a;
    int b;
    char *c;
} A;

int main() {
    A a;
    a.a = 1;
    a.b = 4;
    a.c = "h";

    A b = a;
    printf("%p %p\n", &a, &b);
    printf("%p %p\n", &a.b, &b.b);
    printf("%p %p\n", a.c, b.c);
    printf("%s %s", a.c, b.c);
    return 0;
    // 可见,都是浅拷贝
    // 当然,对于 非结构体成员,浅拷贝看起来尽管很像深拷贝,但也算是浅拷贝!
}