//
//  main.c
//  BuiltinFrameAddress
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

void func(void)
{
    int *p;
    p = __builtin_frame_address(0);
    printf("func frame: %p\n", p);
    p = __builtin_frame_address(1);
    printf("main frame: %p\n", p);
}

int main(int argc, const char * argv[]) {
    
    int *p;
    p = __builtin_frame_address(0);
    printf("main frame: %p\n", p);
    printf("\n");
    func();
    
    ////其他内建函数////
    char a[100];
    __builtin_memcpy(a, "hello world!", 20);
    __builtin_puts(a);
    
    return 0;
}

//在函数调用过程中还有一个栈帧的概念,函数每调用一次,都会将当前函数的现场保存在栈中,每一层函数调用都会将各自的现场信息都保存在各自的栈中
//这个栈也就是当前函数的栈帧,每一个栈帧有起始地址和结束地址,表示当前函数的堆栈信息,多层函数调用就会有多个栈帧,每个栈帧里会保存上一层栈帧的起始地址
//这样各个栈帧就形成了一个调用链,很多调试器/GDB/包括我们的这个内建函数,其实都是通过回溯函数栈帧调用链来获取函数底层的各种信息的
//比如返回地址i/调用关系等,在ARM系统中使用FP和SP这两个寄存器分别指向当前函数栈帧的起始地址和结束地址,当函数继续调用或者返回
//这两个寄存器的值也会发生变化,总是指向当前函数栈帧的起始地址和结束地址
//我们可以通过内建函数__builtinframeaddress(LEVEL),查看函数的栈帧地址
//    0:查看当前函数的栈帧地址
//    1:查看当前函数调用者的栈帧地址
//    ……
//写一个程序打印当前函数的栈帧地址
//运行结果
//
//main frame: 0x7ffde8402f60
//
//func frame: 0x7ffde8402f40
//main frame: 0x7ffde8402f60
//
//在GNU C编译器内部实现了一些和C标准库函数类似的内建函数,这些函数跟C标准库函数功能相似,函数名也相同,只是在前面加了一个__builtin
//如果你不想使用C库函数,也可以直接使用对应的内建函数
//常见的标准库函数如下:
//    内存相关的函数:    memcpy/memset/memcmp
//    数学函数:log/cos/abs/exp
//    字符串处理函数:strcat/strcmp/strcpy/strlen
//    打印函数:printf/scanf/putchar/puts
