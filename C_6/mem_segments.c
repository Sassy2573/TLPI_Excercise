/*
 * @Author: sassy chenyinlin0429@gmail.com
 * @Date: 2024-08-09 16:29:03
 * @LastEditors: sassy chenyinlin0429@gmail.com
 * @LastEditTime: 2024-08-16 14:20:45
 * @FilePath: /chen/TLPI_Excercise/C_6/mem_segments.c
 * @Description: 程序变量在进程中内存各段中的位置
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */
#include <stdio.h>
#include <stdlib.h>

char globBuf[65536];    // 未初始化的数据段
int primes[] = {2, 3, 5, 7};    // 初始化的数据段

static int square(int x)
{
    int result;

    result = x * x;
    
    return result;  // 通过寄存器将返回值传回去
}

static void doCalc(int val)
{
    printf("The square of %d is %d\n", val, square(val));

    if (val < 1000)
    {
        int t;

        t = val * val * val;
        printf("The cube of %d is %d\n", val, t);
    }
}

int main(int argc, char *argv[])
{
    static int key = 9973;
    /* 未显式初始化的全局变量和静态变量称为BSS段，磁盘只存储这写数据段位置和所需大小 */
    static char mbuf[10240000];
    char *p;

    p = malloc(1024);

    doCalc(key);
    exit(EXIT_SUCCESS);

}
