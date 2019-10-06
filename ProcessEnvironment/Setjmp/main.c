//
//  main.c
//  Setjmp
//
//  Created by 杨俊艺 on 2019/9/15.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

static void f1(int i, int j, int k, int l);
static void f2(void);

static jmp_buf jmpbuffer;
static int globval;

int main(int argc, const char * argv[]) {
    
    int autoval;
    register int regival;
    volatile int volaval;
    static int statval;
    
    globval = 1;
    autoval = 2;
    regival = 3;
    volaval = 4;
    statval = 5;
    
    if (setjmp(jmpbuffer) != 0) {
        printf("after longjmp:\n");
        printf("globval = %d, autoval = %d, regival = %d, volaval = %d, statval = %d\n", globval, autoval, regival, volaval, statval);
        exit(0);
    }
    
    globval = 95;
    autoval = 96;
    regival = 97;
    volaval = 98;
    statval = 99;
    
    f1(autoval, regival, volaval, statval);
    
    return 0;
}

static void f1(int i, int j, int k, int l)
{
    printf("in f1():\n");
    printf("globval = %d, autoval = %d, regival = %d, volaval = %d, statval = %d\n", globval, i, j, k, l);
    f2();
}

static void f2(void)
{
    longjmp(jmpbuffer, 1);
}

//带优化编译和不带优化编译运行结果不一致,该项目在Xcode中是开启优化的
//in f1():
//globval = 95, autoval = 96, regival = 97, volaval = 98, statval = 99
//after longjmp:
//globval = 95, autoval = 2, regival = 3, volaval = 98, statval = 99
//未优化版本
//in f1():
//globval = 95, autoval = 96, regival = 97, volaval = 98, statval = 99
//after longjmp:
//globval = 95, autoval = 96, regival = 97, volaval = 98, statval = 99
//全局变量/静态变量/易失变量不受优化的影响,在longjmp之后,它们的值是最近呈现的值
//在某个系统的setjmp(3)手册上说明存放在存储器上的变量将具有时的值,而在CPU和浮点寄存器中的变量则恢复为调用setjmp时的值
//不进行优化时,则五个值都存放在存储器中,忽略对register存储类说明
//进行优化后,autoval以及regival都将存放在寄存器中,即使autoval并未说明为register,而volatile变量依然存放在存储器中
//可以知道,如果要编写可移植性程序,则必须使用volatile属性
