/*
 * @Author: Sassy2573 chenyinlin0429@gmail.com
 * @Date: 2024-08-11 23:16:45
 * @LastEditors: Sassy2573 chenyinlin0429@gmail.com
 * @LastEditTime: 2024-08-11 23:46:20
 * @FilePath: /TLPI/C_6/setjmp_vars.c
 * @Description: 编译器的优化和 longimp（函数相互作用的示例
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

static jmp_buf env;

static void doJump(int nvar, int rvar, int vvar)
{
    printf("Inside doJump():nvar=%d rvar=%d vvar=%d\n", nvar, rvar, vvar);
    longjmp(env, 1);
}

int main(int argc, char *argv[])
{
    int nvar;
    register int rvar;
    volatile int vvar;

    nvar = 111;
    rvar = 222;
    vvar = 333;

    if (setjmp(env) == 0)
    {
        nvar = 777;
        rvar = 888;
        vvar = 999;
        doJump(nvar, rvar, vvar);
    }
    else
    {
        printf("After longjmp(): nvar=%d rvar=%d vvar=%d", nvar, rvar, vvar);
    }

    exit(EXIT_SUCCESS);
}