#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

struct iovec
{
    void *iov_base; // 指向缓冲区的指针
    size_t iov_len; // 缓冲区长度
};

ssize_t my_readv(int fd, const struct iovec *iov, int iovcnt);
ssize_t my_writev(int fd, const struct iovec *iov, int iovcnt);
int main(void)
{
    int fd;
    struct iovec iov[3];
    ssize_t nwritten, nread;

    char *buf1 = "Hello,  ";
    char *buf2 = "world!";
    char *buf3 = "\n";

    iov[0].iov_base = buf1;
    iov[0].iov_len = strlen(buf1);
    
    iov[1].iov_base = buf2;
    iov[1].iov_len = strlen(buf2);

    iov[2].iov_base = buf3;
    iov[2].iov_len = strlen(buf3);

    fd = open("testfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    nwritten = my_writev(fd, iov, 3);
    if (nwritten < 0)   
    {
        perror("my_writev");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Written %zd bytes\n", nwritten);

    char buf4[8], buf5[8], buf6[8];

    iov[0].iov_base = buf4;
    iov[0].iov_len = sizeof(buf4) - 1; // 保留一个字节以便于添加 null 终止符
    iov[1].iov_base = buf5;
    iov[1].iov_len = sizeof(buf5) - 1; // 保留一个字节以便于添加 null 终止符
    iov[2].iov_base = buf6;
    iov[2].iov_len = sizeof(buf6) - 1; // 保留一个字节以便于添加 null 终止符

    fd = open("testfile.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    nread = my_readv(fd, iov, 3);
    if (nread < 0) {
        perror("my_readv");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // 添加 null 终止符
    buf4[iov[0].iov_len] = '\0';
    buf5[iov[1].iov_len] = '\0';
    buf6[iov[2].iov_len] = '\0';

    printf("Read %zd bytes\n", nread);
    printf("Buffer 1: %s\n", buf4);
    printf("Buffer 2: %s\n", buf5);
    printf("Buffer 3: %s\n", buf6);

    close(fd);

    return 0;
}

ssize_t my_readv(int fd, const struct iovec *iov, int iovcnt) {
    ssize_t total_bytes_read = 0;

    for (int i = 0; i < iovcnt; ++i) {
        ssize_t bytes_read = read(fd, iov[i].iov_base, iov[i].iov_len);
        if (bytes_read < 0) {
            return -1; // 读取错误
        }
        total_bytes_read += bytes_read;
        if (bytes_read < iov[i].iov_len) {
            // 读取到文件末尾
            break;
        }
    }

    return total_bytes_read;
}

ssize_t my_writev(int fd, const struct iovec *iov, int iovcnt) {
    ssize_t total_bytes_written = 0;

    for (int i = 0; i < iovcnt; ++i) {
        ssize_t bytes_written = write(fd, iov[i].iov_base, iov[i].iov_len);
        if (bytes_written < 0) {
            return -1; // 写入错误
        }
        total_bytes_written += bytes_written;
    }

    return total_bytes_written;
}
    




    


    


