/* $ atomic_append filename num-bytes［x］ */
/* 该程序应打开所指定的文件（如有必要，则创建之），
然后以每次调用write0写入一个字节的方式，向文件尾部追加 num-bytes 个字节。 */
/*  */
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    if (argc < 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file num-bytes [x]\n"
                 "        'x' means use lseek() instead of O_APPEND\n",
                 argv[0]);

    bool useLseek = argc > 3;
    int flags = useLseek ? 0 : O_APPEND;
    int numBytes = getInt(argv[2], 0, "num-bytes");

    int fd = open(argv[1], O_RDWR | O_CREAT | flags, S_IRUSR | S_IWUSR);
    if (fd == -1)
        errExit("open");

    for (int j = 0; j < numBytes; j++)
    {
        if (useLseek)
            if (lseek(fd, 0, SEEK_END) == -1)
                errExit("lseek");
        if (write(fd, "x", 1) != 1)
            fatal("write() failed");
    }

    printf("%ld done\n", (long)getpid());
    exit(EXIT_SUCCESS);
}

/*
    O_APPEND:确保在多个进程中或线程中同时写入同一个文件时，每个写操作都是原子的，每次写操作都会被完整的写入文件的末尾
    原子性:操作要么成功，要么失败，不会出现部分完成的情况
 */