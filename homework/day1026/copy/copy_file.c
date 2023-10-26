#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *sourceFile = fopen(argv[1], "rb");
    FILE *destinationFile = fopen(argv[2], "wb");
    if (sourceFile == NULL || destinationFile == NULL) {
        printf("无法打开源文件或目标文件.\n");
        return 1;
    }

    char buffer[1] = {0};
    while (fread(buffer, 1, 1, sourceFile) > 0) {
        fwrite(buffer, 1, 1, destinationFile);
    }

    printf("文件复制成功.\n");

    // 关闭文件
    fclose(sourceFile);
    fclose(destinationFile);
    return 0;
}
