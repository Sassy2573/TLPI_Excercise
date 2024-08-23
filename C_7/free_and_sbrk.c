/*
 * @Author: sassy chenyinlin0429@gmail.com
 * @Date: 2024-08-23 14:20:03
 * @LastEditors: sassy chenyinlin0429@gmail.com
 * @LastEditTime: 2024-08-23 14:41:55
 * @FilePath: /TLPI_Excercise/C_7/free_and_sbrk.c
 * @Description: 输入参数 ["1000", "10240", "2"]
 * 总结：使用free后program break的位置仍然与分配后的内存块相当
 *
 * Copyright (c) 2024 by ${chen}, All Rights Reserved. 
 */

#include "tlpi_hdr.h" // 包含错误处理和实用函数的头文件

#define MAX_ALLOCS 1000000 // 定义最大分配内存块数

int main(int argc, char *argv[])
{
    // 定义指针数组用于存储分配的内存块指针
    char *ptr[MAX_ALLOCS];
    int freeStep, freeMin, freeMax, blockSize, numAllocs, j;

    printf("\n");

    // 检查命令行参数个数是否正确，或用户请求帮助
    if (argc < 3 || strcmp(argv[1], "--help") == 0)
    {
        // 显示用法提示
        usageErr("%s num-allocs block-size [setp [min[max]]]\n", argv[0]);
    }

    // 获取用户输入的内存分配次数，并检查是否大于0(将输入的字符串转换成int类型)
    numAllocs = getInt(argv[1], GN_GT_0, "num-allocs");

    // 检查内存分配次数是否超过预设的最大值
    if (numAllocs > MAX_ALLOCS)
    {
        cmdLineErr("num-allocs > %d\n", MAX_ALLOCS);
    }

    // 获取用户输入的每块内存大小
    blockSize = getInt(argv[2], GN_GT_0 | GN_ANY_BASE, "block-size");

    // 设置释放步长、最小和最大释放块数，如果没有输入则使用默认值(1)
    freeStep = (argc > 3) ? getInt(argv[3], GN_GT_0, "step") : 1;
    freeMin = (argc > 4) ? getInt(argv[4], GN_GT_0, "min") : 1;
    freeMax = (argc > 5) ? getInt(argv[5], GN_GT_0, "max") : numAllocs;

    // 检查最大释放块数是否超过总分配块数
    if (freeMax > numAllocs)
    {
        cmdLineErr("free-max > num-allocs\n");
    }

    // 打印初始程序断点（堆顶）地址
    printf("Initial program break:      %10p\n", sbrk(0));

    // 打印将要分配的总字节数
    printf("Allocating %d*%d bytes\n", numAllocs, blockSize);
    for (j = 0; j < numAllocs; j++)
    {
        // 为每块分配内存
        ptr[j] = malloc(blockSize);
        if (ptr[j] == NULL)
        {
            // 如果分配失败则退出并显示错误
            errExit("malloc");
        }
    }

    // 打印当前程序断点（堆顶）地址
    printf("Program break is now:      %10p\n", sbrk(0));

    // 打印将要释放的内存块范围和步长
    printf("Freeing blocks from %d to %d in steps of %d\n", freeMin, freeMax, freeStep);
    for (j = freeMin - 1; j < freeMax; j += freeStep)
    {
        // 按照指定的步长释放内存块
        free(ptr[j]);
    }

    // 打印释放后程序断点（堆顶）地址
    printf("After free(), program break is: %10p\n", sbrk(0));

    // 正常退出程序
    exit(EXIT_SUCCESS);
}
