#include <ctype.h> // toascii(): 把一个字符转换为ASCII
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // 用于构造随机数
#define NAME_LEN 31
#define P 31

uint32_t len = 0;

char *map[NAME_LEN];
const char *names[NAME_LEN] = {
    "侯晨阳", "唐甲超", "滕悦",   "马晰",   "徐楠",   "南佳怡", "薛宇涵",
    "杜龙飞", "祝贺琴", "张浩",   "赵晓春", "路亮",   "王晨",   "许宇泉",
    "李依桐", "张欣悦", "周琛琳", "韩晓梅", "任浩浩", "刘子璐", "李超凡",
    "常程子", "张长坤", "李珂",   "李白",   "韩信",   "阿珂",   "孙策",
    "孙尚香", "孙悟空", "猪八戒"};

// // 取前两个字节
// uint32_t Bytes2[NAME_LEN] = {0};

// void hash() {
//     uint32_t temp;
//     for (int i = 0; i < NAME_LEN; i++) {
//         temp = 0;
//         for (int j = 0; j < 4; j++) {
//             temp += toascii((char)(*(names[i] + j)));
//         }
//         Bytes2[i] = temp;
//     }
// }

// // 检查一下
// void print1() {
//     for (int i = 0; i < NAME_LEN; i++) {
//         printf("%d\n", Bytes2[i]);
//     }
// }

// 哈希函数 除留余数法
uint32_t HASH(const char *name) {
    uint32_t temp = 0;
    for (int j = 0; j < 4; j++) {
        temp += toascii((char)(*(name + j)));
    }
    // 除留余数法
    return temp % P;
}

// 测试
// void print2(){
//     for(int i = 0; i < NAME_LEN; i++){
//         printf("%s  %d\n",names[i],HASH(names[i]));
//     }
// }

// 哈希表, 冲突处理:随机探测再散列
void HashMap() {
    int randPos = 0;
    srand(time(NULL)); // 用当前时间作为种子
    // randNum = rand()%31; // 0~30 之间的随机数

    // 构造
    for (int i = 0; i < NAME_LEN; i++) {
        uint32_t pos = HASH(names[i]);
        if (map[pos] == NULL) {
            map[pos] = (char *)names[i];
        } else {
            // 随机再散列
            randPos = rand() % 31;
            pos = (pos + randPos) % P;
            while (map[pos] != NULL) {
                randPos = rand() % 31;
                pos = (pos + randPos) % P;
            }
            map[pos] = (char *)names[i];
        }
    }
}

// 查表
uint32_t search(const char *name) {
    len = 0;
    int randPos;
    uint32_t pos = HASH(name);

    if (strcmp(name,map[pos]) == 0) {
        len = 1;
        return pos;
    } else {
        // 随机再散列
        len = 1;
        randPos = rand() % 31;
        pos = (pos + randPos) % P;
        while (strcmp(name,map[pos]) != 0) {
            len++;
            randPos = rand() % 31;
            pos = (pos + randPos) % P;
        }
    }
    return pos;
}
// 打印
void print3() {
    for (int i = 0; i < NAME_LEN; i++) {
        search(names[i]);
        printf("本次查找次数为:%d   %d  %d  %s\n", len, i, search(names[i]),
               names[i]);
    }
}

// 平均查找长度
double averlen() {
    double tal = 0;
    for (int i = 0; i < NAME_LEN; i++) {
        search(names[i]);
        tal += len;
    }
    return (double)(tal / NAME_LEN);
}

int main() {
    // 初始化
    for (int i = 0; i < NAME_LEN; i++) {
        map[i] = NULL;
    }
    HashMap();
    print3();
    int pos = search("孙尚香");
    printf("%d\n", pos);
    printf("次数:%d\n", len);
    printf("%.5f\n", averlen());

    return 0;
}