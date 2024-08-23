/*
 * @Author: sassy chenyinlin0429@gmail.com
 * @Date: 2024-08-23 10:26:41
 * @LastEditors: sassy chenyinlin0429@gmail.com
 * @LastEditTime: 2024-08-23 10:26:41
 * @FilePath: /chen/TLPI_Excercise/C_6/longjmp.c
 * @Description: 展示函数 setjmp（和 longimp（）的用法
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */
#include <setjmp.h>   // 用于 setjmp 和 longjmp 函数
#include "tlpi_hdr.h" // 包含自定义头文件，包含了标准库和其他辅助函数

static jmp_buf env; // 定义一个 jmp_buf 类型的变量，用于保存环境信息

// 定义函数 f2
static void f2(void)
{
    // 从此处进行非局部跳转，跳转回 setjmp 所保存的环境，并传递 2 作为返回值
    longjmp(env, 2);
}

// 定义函数 f1
static void f1(int argc)
{
    // 如果命令行参数个数为 1，则进行非局部跳转，跳转回 setjmp 所保存的环境，并传递 1 作为返回值
    if (argc == 1)
    {
        longjmp(env, 1);
    }
    // 否则，调用 f2 函数
    f2();
}

// 主函数
int main(int argc, char *argv[])
{
    // 设置一个跳转点，保存当前环境，返回 0；当通过 longjmp 跳转回来时，返回 longjmp 传递的值
    switch (setjmp(env))
    {
    case 0: // 第一次调用 setjmp，返回 0
        printf("Calling f1() after initial setjmp()\n"); // 输出提示信息
        f1(argc); // 调用 f1 函数，传递命令行参数个数
        break;
    
    case 1: // 当从 f1 中跳回时，setjmp 返回 1
        printf("We jumped back from f1()\n"); // 输出提示信息
        break;

    case 2: // 当从 f2 中跳回时，setjmp 返回 2
        printf("We jumped back from f2()\n"); // 输出提示信息
        break;
    }

    exit(EXIT_SUCCESS); // 正常退出程序
}

