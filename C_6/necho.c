/*
 * @Author: sassy chenyinlin0429@gmail.com
 * @Date: 2024-08-09 16:46:33
 * @LastEditors: sassy chenyinlin0429@gmail.com
 * @LastEditTime: 2024-08-09 16:48:58
 * @FilePath: /chen/TLPI_Excercise/C_6/necho.c
 * @Description: 回显命令行参数
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    for (int j = 0; j < argc; j++)
    {
        printf("argv[%d] = %s\n", j, argv[j]);
    }
    exit(EXIT_SUCCESS);
    
}