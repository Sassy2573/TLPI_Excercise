#include "tlpi_hdr.h"
#include <sys/stat.h>
#include <fcntl.h>

int fcn_dup(int);
int fcn_dup2(int, int);

int main() {
    
}

int fcn_dup(int oldfd) {
    return fcntl(oldfd, F_DUPFD, 0);
}

int fcn_dup2(int oldfd, int newfd) {
    // 1. 如果oldfd无效,失败并返回错误EBADF
    int flags = fcntl(oldfd, F_GETFL);
    if (flags == -1) {
        errno = EBADF;
        return -1;
    }

    // 2. 如果oldfd有效,且与newfd值相等,则什么都不做
    if (oldfd == newfd) {
        return oldfd;
    }

    // 3. 否则关闭newfd(忽视可能出现的错误),创建副本
    return fcntl(oldfd, F_DUPFD, newfd);
}