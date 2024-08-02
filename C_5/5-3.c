/* $ atomic_append filename num-bytes［x］ */
/* 该程序应打开所指定的文件（如有必要，则创建之），
然后以每次调用write0写入一个字节的方式，向文件尾部追加 num-bytes 个字节。 */
/*  */
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    int fd;
    if ((argc != 4 && argc != 3) || strcmp(argv[1], "--help") == 0)
    {
        usageErr("%s filename\n", argv[0]);
    }

    if(argc == 3)
    {
        fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
        for(int i = 0; i < atoi(argv[2]); ++i)
        {
            if (write(fd, "a", 1) != 1)
            {
                usageErr("write error\n");
            }
        }
    }
}