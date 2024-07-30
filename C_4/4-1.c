/*
 * @Author: Sassy chenyinlin0429@gmail.com
 * @Date: 2024-07-29 19:15:06
 * @LastEditors: Sassy chenyinlin0429@gmail.com
 * @LastEditTime: 2024-07-29 19:50:50
 * @FilePath: /chen/linux/code/App_Code/TLPI/C_4/4-1.c
 * @Description: tee 命令用于读取标准输入（stdin）并将其内容输出到标准输出（stdout）和一个或多个文件中
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE 1024

/**
 * @description: 读取标准输入，将读到的内容输出到标准输出和文件，同时将内容输出到标准输出
 * @param {char} *filename
 * @return {*}
 */
void tee(const char *filename)
{
    int fd =  open(filename, O_RDWR | O_CREAT | O_TRUNC); // 打开文件，如果文件不存在则创建
    if(fd < 0)
    {
        perror("failed to open");
        exit(EXIT_FAILURE);
    }

    char buffer[BUF_SIZE]; // 缓冲区
    ssize_t bytesRead; // 读取的字节数

    // 读取标准输入，将内容输出到标准输出和文件
    while ((bytesRead = read(STDIN_FILENO, buffer, BUF_SIZE)) > 0)
    {
        // 输出到标准输出
        if (write(STDOUT_FILENO, buffer, bytesRead) != bytesRead)
        {
            perror("failed to write");
            close(fd);
            exit(EXIT_FAILURE);
        }

        // 输出到文件
        if (write(fd, buffer, bytesRead) != bytesRead)
        {
            perror("failed to write");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }

    // 关闭文件
    if (bytesRead == -1)
    {
        perror("failed to read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    tee(argv[1]);

    return EXIT_SUCCESS;
}