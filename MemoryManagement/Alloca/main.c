//
//  main.c
//  Alloca
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void compute(int size);

int main(int argc, const char * argv[]) {
    
    
    
    
    return 0;
}

void compute(int size)
{
    //char  *buffer[size];
}

//alloca函数和变长数组
//alloca函数(微软为malloca)在函数的栈帧上分配内存,函数返回后会自动释放内存,若底层的运行时系统不基于栈,alloca函数会很难实现
//所以这个函数是不标准的,如果应用程序需要可移值就尽量避免使用它
//C99引入了变长数组VLA,允许函数内部声明和创建其长度由变量决定的数组
//这意味着内存分配在运行时完成,且将内存作为栈帧的一部分来分配,另外,如果数组用到sizeof操作符,也是在运行时而不是编译时执行
//这么做只会有一点点运行时开销,而且一旦函数退出立即释放内存
//因为我们没有使用malloc这类函数来创建数组,所以不应用free来释放它
//alloca函数也不应该指向数组所在内存的指针
//需要注意的是,VLA的长度不能改变,一经分配其长度就固定了,如果需要一个长度能够实际变化的数组,那么需要使用类似realloc的函数
