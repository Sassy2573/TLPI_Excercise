/*
 * @Author: sassy chenyinlin0429@gmail.com
 * @Date: 2024-08-16 14:34:19
 * @LastEditors: sassy chenyinlin0429@gmail.com
 * @LastEditTime: 2024-08-16 14:38:09
 * @FilePath: /chen/TLPI_Excercise/C_6/6-2.c
 * @Description: 演示错误使用longjmp()跳转到一个已经返回的函数，由于这个错误使用，程序会应为收到SIGSEG信号而终止
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */
#include <setjmp.h>
#include "tlpi_hdr.h"

static jmp_buf env; /* 环境变量全局缓存  */

static void doJump(void)
{
    printf("Entered doJump\n");
    longjmp(env, 2);
    printf("Exiting doJump\n");
}

static void setJump2(void)
{
    printf("Entered setJump2\n");
    setjmp(env);
    printf("Exiting setJump2\n");
}

static void setJump(void)
{
    printf("Entered setJump\n");
    setJump2();
    printf("Exiting setJump\n");
}

int main(int argc, char *argv[])
{
    setJump();
    doJump();
    printf("Back at main\n");

    exit(EXIT_SUCCESS);
}