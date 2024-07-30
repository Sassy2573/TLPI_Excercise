/*
 * @Author: Sassy chenyinlin0429@gmail.com
 * @Date: 2024-07-29 19:59:00
 * @LastEditors: Sassy chenyinlin0429@gmail.com
 * @LastEditTime: 2024-07-29 20:07:18
 * @FilePath: /chen/linux/code/App_Code/TLPI/C_4/4_2.c
 * @Description: 似于cp命令的程序，以复制文件并保持其中的空洞
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    const char *source_path = argv[1];
    const char *dest_path = argv[2];

    int src_fd = open(source_path, O_RDONLY);
    if (src_fd == -1) {
        perror("open");
        return 1;
    }

    int dest_fd = creat(dest_path, S_IRUSR | S_IWUSR);
    if (dest_fd == -1) {
        perror("creat");
        return 1;
    }
    
    char buf[BUF_SIZE];
    ssize_t bytes_read;
    off_t current_offset = 0;

    while ((bytes_read = read(src_fd, buf, BUF_SIZE)) > 0) {
        if (lseek(dest_fd, current_offset, SEEK_SET) == -1) {
            perror("lseek");
            close(src_fd);
            close(dest_fd);
            return 1;
        }
        
        // Write the data to the destination file descriptor 
        if (write(dest_fd, buf, bytes_read) != bytes_read) {
            perror("write");
            close(src_fd);
            close(dest_fd);
            return 1;
        }

        current_offset += bytes_read; // Update the offset 
        
    }

    close(src_fd);
    close(dest_fd);

    return 0;
    
    
    
}