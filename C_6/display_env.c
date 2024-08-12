/*
 * @Author: sassy chenyinlin0429@gmail.com
 * @Date: 2024-08-09 17:24:19
 * @LastEditors: sassy chenyinlin0429@gmail.com
 * @LastEditTime: 2024-08-09 17:25:51
 * @FilePath: /chen/TLPI_Excercise/C_6/display_env.c
 * @Description: 显示进程环境
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */
#include "tlpi_hdr.h"
extern char **environ;
int main(int argc, char *argv[])
{
    char **ep;

    for (ep = environ;ep != NULL;ep++)
    {
        puts(*ep);
    }

    exit(EXIT_SUCCESS);
    
}