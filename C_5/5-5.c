#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd1, fd2;
    off_t offset1, offset2;
    const char *filename = "testfile.txt";
    char buffer[100];

    // 创建一个文件并写入一些数据
    fd1 = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd1 < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // 写入数据
    write(fd1, "Hello, World!", 13);

    // 复制文件描述符
    fd2 = dup(fd1);
    if (fd2 < 0) {
        perror("dup");
        close(fd1);
        exit(EXIT_FAILURE);
    }

    // 获取并打印偏移量
    offset1 = lseek(fd1, 0, SEEK_CUR);
    offset2 = lseek(fd2, 0, SEEK_CUR);

    printf("Offset of fd1: %ld\n", (long)offset1);
    printf("Offset of fd2: %ld\n", (long)offset2);

    // 修改文件偏移量
    lseek(fd1, 5, SEEK_SET);

    // 获取并打印偏移量
    offset1 = lseek(fd1, 0, SEEK_CUR);
    offset2 = lseek(fd2, 0, SEEK_CUR);

    printf("After seeking:\n");
    printf("Offset of fd1: %ld\n", (long)offset1);
    printf("Offset of fd2: %ld\n", (long)offset2);

    // 检查文件状态标志
    int flags1 = fcntl(fd1, F_GETFL);
    int flags2 = fcntl(fd2, F_GETFL);

    if (flags1 < 0 || flags2 < 0) {
        perror("fcntl");
        close(fd1);
        close(fd2);
        exit(EXIT_FAILURE);
    }

    printf("Flags of fd1: %d\n", flags1);
    printf("Flags of fd2: %d\n", flags2);

    // 关闭文件描述符
    close(fd1);
    close(fd2);

    // 删除文件
    unlink(filename);

    return 0;
}

/* 
    件偏移量在两个描述符之间是一致的，并且修改一个描述符的偏移量会影响另一个描述符。状态标志在两个描述符之间也应当保持一致
 */